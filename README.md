# Interface graphique de controlle

```
nerell-gui unix /tmp/ecran.sock [debug]
```

## Messages JSON

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
        "startCalibration": false,
        "strategy": "STRAT1",
        "modeManuel": false,
        "skipCalageBordure": false,
        "updatePhoto": false,
        "etalionnageBalise": false,
        "posEcueil": [
            [500, 500],
            [500, 500]
        ],
        "posBouees": [ ... ] // six positions ou null
    }
}
```

### Mettre à jour les informations d'init

* Query
```json
{
    "action": "UPDATE_STATE",
    "data": {
        "i2c": true,
        "lidar": true,
        "au": true,
        "alim12v": true,
        "alim5vp": true,
        "tirette": true,
        "phare": true,
        "balise": true,
        "message": "Démarrage"
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

### Mettre à jour le résultat d'étalonnage balise

* Query
```json
{
    "action": "UPDATE_ETALONNAGE",
    "data": {
        "ecueil": ["#ff00ff00", "#ffff0000"],
        "bouees": [ ... ] // six couleurs ou null
    }
}
```

* Réponse
```json
{
    "status": "OK",
    "action": "UPDATE_ETALONNAGE"
}
```
