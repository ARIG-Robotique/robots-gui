import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.1


Page {
    id: page
    anchors.fill: parent

    title: "Configuration " + ParamsModel.name

    function getBooleanColor(value, value2) {
        return value ? value2 === false ? "yellow" : "green" : "red";
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

    ColumnLayout {
        id: pageConfig
        anchors.fill: parent
        anchors.margins: 5

        Label {
            Layout.fillWidth: true
            Layout.preferredHeight: 35
            text: RobotModel.message
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 16
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.minimumHeight: 40*4 + 20
            Layout.maximumHeight: 40*4 + 20

            Frame {
                id: statusFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1

                RowLayout {
                    anchors.fill: parent

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredWidth: 1

                        StateComponent {
                            id: i2cState
                            libelle: "Bus i2c"
                            stateColor: getBooleanColor(RobotModel.i2c)
                        }

                        StateComponent {
                            id: lidarState
                            libelle: "Lidar"
                            stateColor: getBooleanColor(RobotModel.lidar)
                        }

                        StateComponent {
                            id: otherRobotState
                            libelle: ParamsModel.primary ? "Odin" : "Nerell"
                            stateColor: getBooleanColor(RobotModel.otherRobot)
                        }

                        StateComponent {
                            id: baliseState
                            visible: ParamsModel.primary || !RobotModel.otherRobot
                            libelle: "Balise"
                            stateColor: getBooleanColor(RobotModel.balise, RobotModel.etalonnageOk)
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.preferredWidth: 1

                        StateComponent {
                            id: auState
                            libelle: "A.U."
                            stateColor: getBooleanColor(RobotModel.au)
                        }

                        StateComponent {
                            id: alimMoteursState
                            libelle: "Moteurs"
                            stateColor: getBooleanColor(RobotModel.alimMoteurs)
                        }

                        StateComponent {
                            id: alimServosState
                            libelle: "Servos"
                            stateColor: getBooleanColor(RobotModel.alimServos)
                        }

                        StateComponent {
                            id: tiretteState
                            visible: ParamsModel.primary || !RobotModel.otherRobot
                            libelle: "Tirette"
                            stateColor: getBooleanColor(RobotModel.tirette)
                        }
                    }
                }
            }

            Frame {
                id: teamFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1

                Label {
                    anchors.fill: parent
                    anchors.bottomMargin: 40
                    text: "Taper ici pour choisir l'équipe"
                    visible: !RobotModel.team && (ParamsModel.primary || !RobotModel.otherRobot)
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 12
                }

                ColumnLayout {
                    anchors.fill: parent

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Repeater {
                            model: ParamsModel.teams

                            delegate: Rectangle {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.preferredWidth: 1
                                color: modelData.color
                                opacity: RobotModel.team === modelData.name ? 1 : 0.2
                                radius: 5

                                MouseArea {
                                    anchors.fill: parent
                                    enabled: !RobotModel.startCalibration && (ParamsModel.primary || !RobotModel.otherRobot)
                                    onClicked: {
                                        RobotModel.team = modelData.name
                                    }
                                }
                            }
                        }
                    }

                    Button {
                        Layout.fillWidth: true
                        topInset: 5
                        bottomInset: 0
                        bottomPadding: 5
                        enabled: RobotModel.au && !!RobotModel.team && !RobotModel.startCalibration && (ParamsModel.primary || !RobotModel.otherRobot)
                        text: "Lancer le calage bordure"
                        hoverEnabled: false
                        highlighted: false
                        onClicked: {
                            if (!RobotModel.startCalibration) {
                                console.log("Start calage bordure")
                                calibConfirmation.open()
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            enabled: !RobotModel.tirette

            Frame {
                id: strategiesFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1

                ColumnLayout {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Repeater {
                        model: ParamsModel.strategies

                        delegate: RadioButton {
                            padding: 1
                            text: modelData
                            font.pointSize: 16
                            checked: RobotModel.strategy === modelData
                            onClicked: RobotModel.strategy = modelData
                        }
                    }
                }
            }

            Frame {
                id: configMatchFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1

                ColumnLayout {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 0

                    Repeater {
                        model: ParamsModel.options

                        delegate: Switch {
                            id: optionItem
                            padding: 5
                            text: modelData
                            checked: RobotModel.options[modelData]
                            onClicked: RobotModel.setOption(modelData, optionItem.checked)
                        }
                    }
                }
            }

            Frame {
                id: configDebugFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1

                ColumnLayout {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 0

                    Switch {
                        id: configTwoRobots
                        padding: 5
                        text: "Deux robots"
                        enabled: !RobotModel.otherRobot
                        checked: RobotModel.twoRobots
                        onClicked: RobotModel.twoRobots = configTwoRobots.checked
                    }

                    Switch {
                        id: configSafeAvoidance
                        padding: 5
                        text: "Safe avoidance"
                        checked: RobotModel.safeAvoidance
                        onClicked: RobotModel.safeAvoidance = configSafeAvoidance.checked
                    }

                    Switch {
                        id: configSkipCalageChoixStrat
                        padding: 5
                        text: qsTr("Skip cal. bord. / strat.")
                        checked: RobotModel.skipCalageBordure
                        onClicked: RobotModel.skipCalageBordure = configSkipCalageChoixStrat.checked
                    }

                    Switch {
                        id: configModeManuel
                        padding: 5
                        text: qsTr("Mode manuel")
                        checked: RobotModel.modeManuel
                        onClicked: RobotModel.modeManuel = configModeManuel.checked
                    }
                }
            }
        }
    }

    Frame {
        id: pageMatch
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
                target: pageConfig
                visible: false
            }

            PropertyChanges {
                target: pageMatch
                visible: true
            }

            PropertyChanges {
                target: page
                title: qsTr("Match")
            }
        }
    ]
}
