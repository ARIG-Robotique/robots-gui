import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import org.arig.robotmodel 1.0

Page {
    id: page
    anchors.fill: parent

    title: qsTr("Configuration Nerell")

    function getBooleanColor(value, value2) {
        return value ? value2 === false ? "orange" : "green" : "red";
    }

    function getTeamColor(team) {
        if (team === RobotModel.BLEU) {
            return "blue";
        } else if (team === RobotModel.JAUNE) {
            return "yellow";
        }

        return Material.backgroundColor;
    }

    Popup {
        id: calibConfirmation
        modal: true
        focus: true
        width: 400
        height: 150
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.0
                to: 1.0
            }
        }
        exit: Transition {
            NumberAnimation {
                property: "opacity"
                from: 1.0
                to: 0.0
            }
        }

        anchors.centerIn: Overlay.overlay

        contentItem:  Column {
            padding: 5
            spacing: 10

            Label {
                text: "Lancement du calage bordure ?"
                font.pointSize: 16
            }

            Label {
                text: "Pas de retour arrière possible"
                font.pointSize: 10
            }

            Row {
                padding: 5
                spacing: 10
                anchors.right: parent.right
                anchors.rightMargin: 5

                Button {
                    text: "Non"
                    onClicked: {
                        calibConfirmation.close();
                    }
                }

                Button {
                    text: "Oui"
                    onClicked: {
                        RobotModel.startCalibration = true
                        calibConfirmation.close();
                    }
                }
            }
        }
    }

    Label {
        id: lblMessage
        height: 35
        text: RobotModel.message
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        font.pointSize: 16
    }

    Frame {
        id: frameInfos
        width: 395
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 190
        anchors.top: lblMessage.bottom
        anchors.topMargin: 10

        Row {
            id: rowStates
            height: 180
            spacing: 5
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Column {
                width: 185
                spacing: 10

                StateComponent {
                    id: i2cState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Bus i2c")
                    stateColor: getBooleanColor(RobotModel.i2c)
                }

                StateComponent {
                    id: lidarState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Lidar")
                    stateColor: getBooleanColor(RobotModel.lidar)
                }

                StateComponent {
                    id: otherRobotState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Odin")
                    stateColor: getBooleanColor(RobotModel.otherRobot)
                }

                StateComponent {
                    id: baliseState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Balise")
                    stateColor: getBooleanColor(RobotModel.balise, RobotModel.etalonnageOk)
                }
            }

            Column {
                width: 185
                spacing: 10

                StateComponent {
                    id: auState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("A.U.")
                    stateColor: getBooleanColor(RobotModel.au)
                }

                StateComponent {
                    id: alim12vState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Moteurs")
                    stateColor: getBooleanColor(RobotModel.alim12v)
                }

                StateComponent {
                    id: alim5vpState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Servos")
                    stateColor: getBooleanColor(RobotModel.alim5vp)
                }

                StateComponent {
                    id: tiretteState
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    libelle: qsTr("Tirette")
                    stateColor: getBooleanColor(RobotModel.tirette)
                }
            }
        }
    }

    Frame {
        id: frameTeam
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 190
        anchors.top: lblMessage.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: frameInfos.right
        anchors.leftMargin: 5


        Rectangle {
            id: rectColorTeam
            color: getTeamColor(RobotModel.team)
            radius: 5
            border.color: "#00000000"
            border.width: 1
            anchors.bottom: buttonCalibration.top
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        MouseArea {
            property bool checked: true

            enabled: !RobotModel.startCalibration

            id: areaSelectColor
            anchors.bottom: buttonCalibration.top
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            onClicked: {
                areaSelectColor.checked = !areaSelectColor.checked;
                RobotModel.team = areaSelectColor.checked ? RobotModel.BLEU : RobotModel.JAUNE;
            }
        }

        Label {
            id: lblTeam
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenterOffset: -30
            anchors.verticalCenter: parent.verticalCenter
            width: 300
            height: 24
            text: qsTr("Taper ici pour choisir l'équipe")
            visible: RobotModel.team == RobotModel.UNKNOWN
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }

        Button {
            id: buttonCalibration
            y: 277
            enabled: RobotModel.au && RobotModel.team != RobotModel.UNKNOWN && !RobotModel.startCalibration
            text: qsTr("Lancer le calage bordure")
            hoverEnabled: false
            highlighted: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onClicked: {
                if (!RobotModel.startCalibration) {
                    console.log("Start calage bordure")
                    calibConfirmation.open()
                }
            }
        }
    }

    Frame {
        id: frameConfig
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: frameTeam.bottom
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        topPadding: 0
        bottomPadding: 0


        ButtonGroup {
            buttons: strategies.childrens
        }

        Row {
            id: rowConfig
            spacing: 10
            enabled: !RobotModel.tirette
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Column {
                id: strategies
                width: 170
                spacing: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                RadioButton {
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    checked: RobotModel.strategy === RobotModel.BASIC
                    text: qsTr("Basic")
                    font.pointSize: 16
                    onClicked: RobotModel.strategy = RobotModel.BASIC
                }
                RadioButton {
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    checked: RobotModel.strategy === RobotModel.AGGRESSIVE
                    text: qsTr("Aggressive")
                    font.pointSize: 16
                    onClicked: RobotModel.strategy = RobotModel.AGGRESSIVE
                }
                RadioButton {
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    checked: RobotModel.strategy === RobotModel.FINALE
                    text: qsTr("Finale")
                    font.pointSize: 16
                    onClicked: RobotModel.strategy = RobotModel.FINALE
                }
            }

            Column {
                id: configMatch
                width: 235
                spacing: 10

                Switch {
                    id: configDeposePartielle
                    text: qsTr("Dépose partielle gd chenal")
                    checked: RobotModel.deposePartielle && RobotModel.twoRobots
                    enabled: RobotModel.twoRobots
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.deposePartielle = configDeposePartielle.checked
                    onCheckedChanged: RobotModel.deposePartielle = configDeposePartielle.checked
                }

                Switch {
                    id: configEchangeEcueil
                    text: qsTr("Échange ecueil")
                    checked: RobotModel.echangeEcueil
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.echangeEcueil = configEchangeEcueil.checked
                }

                Switch {
                    id: configSafeAvoidance
                    text: qsTr("Safe avoidance")
                    checked: RobotModel.safeAvoidance
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.safeAvoidance = configSafeAvoidance.checked
                }
            }

            Column {
                id: configDebug
                width: 200
                spacing: 10

                Switch {
                    id: configTwoRobots
                    text: qsTr("Deux robots")
                    enabled: !RobotModel.otherRobot
                    checked: RobotModel.twoRobots
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.twoRobots = configTwoRobots.checked
                }

                Switch {
                    id: configSkipCalageChoixStrat
                    text: qsTr("Skip cal. bord. / strat.")
                    checked: RobotModel.skipCalageBordure
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.skipCalageBordure = configSkipCalageChoixStrat.checked
                }

                Switch {
                    id: configModeManuel
                    text: qsTr("Mode manuel")
                    checked: RobotModel.modeManuel
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    onClicked: RobotModel.modeManuel = configModeManuel.checked
                }
           }
        }
    }

    Frame {
        id: matchInfos
        visible: false
        anchors.fill: parent
        background: Image {
            source: "fond-ecran.png"
        }

        FontLoader {
            id: crystalFont
            source: "LiquidCrystal-Normal.otf"
        }

        Label {
            height: 35
            text: RobotModel.message
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 25
            font.pointSize: 16
        }

        Label {
            text: RobotModel.score
            anchors.fill: parent
            anchors.topMargin: 175
            anchors.leftMargin: 15 // la font a problème de centrage
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 150
            font.family: crystalFont.name
            //renderType: Text.NativeRendering
        }

    }

    states: [
        State {
            name: "match"
            when: (RobotModel.inMatch)

            PropertyChanges {
                target: lblMessage
                visible: false
            }

            PropertyChanges {
                target: frameInfos
                visible: false
            }

            PropertyChanges {
                target: frameTeam
                visible: false
            }

            PropertyChanges {
                target: frameConfig
                visible: false
            }

            PropertyChanges {
                target: matchInfos
                visible: true
            }

            PropertyChanges {
                target: page
                title: qsTr("Match")
            }
        }
    ]
}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_width:145;anchors_x:"-9";anchors_y:3}
D{i:3;anchors_width:356;anchors_x:393;anchors_y:"-1"}D{i:4;anchors_width:145;anchors_x:"-9";anchors_y:3}
D{i:5;anchors_width:356;anchors_x:393;anchors_y:"-1"}D{i:6;anchors_width:145;anchors_x:"-9";anchors_y:3}
D{i:7;anchors_width:356;anchors_x:393;anchors_y:"-1"}D{i:8;anchors_width:145;anchors_x:"-9";anchors_y:3}
D{i:10;anchors_width:145;anchors_x:"-9";anchors_y:3}D{i:11;anchors_width:356;anchors_x:393;anchors_y:"-1"}
D{i:9;anchors_width:356;anchors_x:393;anchors_y:"-1"}D{i:1;anchors_height:332;anchors_x:35;anchors_y:34}
D{i:12;anchors_width:356;anchors_x:5;anchors_y:59}D{i:22;anchors_width:180;anchors_x:264}
D{i:23;anchors_width:180;anchors_x:264}D{i:20;anchors_x:16}D{i:27;anchors_height:42}
D{i:28;anchors_height:42;anchors_width:200;anchors_x:0}D{i:31;anchors_width:200;anchors_x:0}
}
##^##*/
