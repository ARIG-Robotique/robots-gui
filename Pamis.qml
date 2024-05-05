import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15


Page {
    id: page
    anchors.fill: parent

    title: "Etats des PAMIs"

    function getBooleanColor(value) {
        return value ? "green" : "red";
    }

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 15
        anchors.bottomMargin: 15

        RowLayout {
            spacing: 5
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            StateComponent {
                libelle: "Triangle"
                stateColor: getBooleanColor(RobotModel.pamiTriangle)
            }

            Button {
                text: "Run"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Monitoring"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Power OFF"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Shutdown"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }
        }

        RowLayout {
            spacing: 5
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            StateComponent {
                libelle: "Carre"
                stateColor: getBooleanColor(RobotModel.pamiCarre)
            }

            Button {
                text: "Run"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Monitoring"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Power OFF"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Shutdown"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }
        }

        RowLayout {
            spacing: 5
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            StateComponent {
                libelle: "Rond"
                stateColor: getBooleanColor(RobotModel.pamiRond)
            }

            Button {
                text: "Run"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Monitoring"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Power OFF"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }

            Button {
                text: "Shutdown"
                onClicked: {
                    // SEND AN SSH CALL
                }
            }
        }
    }
}
