import QtQuick 2.12
import QtQuick.Controls 2.5
import org.arig.robotmodel 1.0


ApplicationWindow {
    id: window
    visible: true
    width: 800
    maximumWidth: 800
    minimumWidth: 800
    height: 480
    maximumHeight: 480
    minimumHeight: 480
    title: qsTr("Nerell GUI")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            visible: !RobotModel.inMatch
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }

        ToolButton {
            text: "\u274C"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
            visible: !RobotModel.inMatch
            onClicked: exitConfirmation.open()
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.2
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Calibration Balise")
                width: parent.width
                enabled: RobotModel.balise
                onClicked: {
                    stackView.push("CalibrationBaliseForm.qml")
                    drawer.close()
                }
            }
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
        width: 350
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
