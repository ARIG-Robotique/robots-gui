import QtQuick 2.12
import QtQuick.Controls 2.5


ApplicationWindow {
    id: window
    visible: true
    width: 800
    maximumWidth: 800
    minimumWidth: 800
    height: 480
    maximumHeight: 480
    minimumHeight: 480
    title: "ARIG Robot GUI"

    header: ToolBar {
        id: toolBar
        contentHeight: toolButton.implicitHeight
        visible: !RobotModel.inMatch

        ToolButton {
            visible: stackView.depth > 1
            text: "\u25C0"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: stackView.pop()
        }

        ToolButton {
            text: "Calibration"
            anchors.leftMargin: 50
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            visible: (ParamsModel.primary || !RobotModel.otherRobot) && stackView.currentItem.title !== "Calibration balise"
            enabled: RobotModel.balise
            onClicked: stackView.push("CalibrationBaliseForm.qml")
        }

        Label {
            text: stackView.currentItem.title
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.centerIn: parent
        }

        ToolButton {
            id: toolButton
            text: "\u274c"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
            onClicked: exitConfirmation.open()
        }
    }

    StackView {
        id: stackView
        initialItem: "ConfigurationForm.qml"
        anchors.fill: parent
    }

    Popup {
        id: exitConfirmation
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
                text: "Quitter le programme ?"
                font.pointSize: 16
            }

            Row {
                padding: 5
                spacing: 10
                anchors.right: parent.right
                anchors.rightMargin: 5

                Button {
                    text: "Non"
                    onClicked: {
                        RobotModel.exit = false
                        exitConfirmation.close();
                    }
                }

                Button {
                    text: "Oui"
                    onClicked: {
                        RobotModel.exit = true
                    }
                }
            }
        }
    }
}
