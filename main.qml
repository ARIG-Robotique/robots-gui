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
    title: qsTr("Robots GUI")

    header: ToolBar {
        id: toolBar
        contentHeight: toolButton.implicitHeight
        visible: !RobotModel.inMatch

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        ToolButton {
            id: baliseButton
            text: "Calibration"
            anchors.left: toolButton.left
            anchors.leftMargin: 50
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            enabled: RobotModel.balise && stackView.currentItem.title !== "Calibration balise (Sauron)"
            onClicked: {
                console.log(stackView.currentItem)
                stackView.push("CalibrationBaliseForm.qml")
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }

        ToolButton {
            text: "\u274c"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
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
