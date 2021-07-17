# Interface graphique de controlle

```
robots-gui unix /tmp/ecran.sock [debug]
robots-gui inet 9000 [debug]
```

## Messages JSON

### Paramétrage initial

* Query
```json
{
    "action": "SET_PARAMS",
    "data": {
        "name": "Nerell",
        "primary": true,
        "teams": {
            "BLEU": "#00f",
            "JAUNE": "#0ff"
        },
        "strategies": [
            "BASIC",
            "AGRESSIVE"
        ],
        "options": [
            "option1",
            "option2"
        ]
    }
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "SET_PARAMS",
}
```

### Mettre à jour les informations d'init

* Query
```json
{
    "action": "UPDATE_STATE",
    "data": {
    "au": true,
        "message": "Démarrage",
        "i2c": true,
        "alim12v": true,
        "alim5vp": true,
        "tirette": true,
        "lidar": true,
        "balise": true,
        "otherRobot": true,
        // si non primary
        "team": "JAUNE",
        "strategy": "BASIC",
        "options": {
            "option1": true,
            "option2": false
        }
    }
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "UPDATE_STATE"
}
```

### Récupérer la configuration

* Query
```json
{
    "action": "GET_CONFIG"
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "GET_CONFIG",
    "data": {
        "team": "JAUNE",
        "strategy": "BASIC",
        "exit": false,
        "twoRobots": true,
        "safeAvoidance": true,
        "startCalibration": false,
        "modeManuel": false,
        "skipCalageBordure": false,
        "updatePhoto": false,
        "etalonnageBalise": false,
        "etalonnageOk": false,
        "options": {
            "option1": true,
            "option2": false
        }
    }
}
```

### Mettre à jour les informations de match

* Query
```json
{
    "action": "UPDATE_MATCH",
    "data": {
        "score": 90,
        "message": "Fin de match"
    }
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "UPDATE_MATCH"
}
```

### Mettre à jour la photo de la balise

* Query
```json
{
    "action": "UPDATE_PHOTO",
    "data": {
        "message": null,
        "photo": "jpeg en base64 sans l'en-tete"
    }
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "UPDATE_PHOTO"
}
```
