import QtQuick 2.12
import QtQuick.Controls 2.12
import org.arig.robotmodel 1.0
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.1

Page {
    id: page
    width: 800
    height: 430

    title: qsTr("Calibration balise (Sauron)")

    property var currentMode: ""
    property var posEcueil: []
    property var posBouees: []
    property var couleurEcueil: []
    property var couleurBouees: []
    property var nbBoueeCalibration: 6

    function getPrimaryColor(n) {
        var colors = [];
        for (var i = 0; i < n; i++) {
            colors.push(Material.primary);
        }
        return colors;
    }

    function btnValiderEnabled() {
        return currentMode == "" && posEcueil.length == 2;
    }

    Component.onCompleted: {
        RobotModel.updatePhoto = true

        posEcueil = RobotModel.getPosEcueilForQML()
        posBouees = RobotModel.getPosBoueesForQML()
        couleurEcueil = RobotModel.couleurEcueil
        couleurBouees = RobotModel.couleurBouees

        if (couleurEcueil.length === 0) {
            couleurEcueil = getPrimaryColor(2)
        }
        if (couleurBouees.length === 0) {
            couleurBouees = getPrimaryColor(nbBoueeCalibration)
        }
    }

    RowLayout {
        id: buttons
        spacing: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        Button {
            text: qsTr("Refresh photo")
            enabled: !RobotModel.updatePhoto
            onClicked: {
                RobotModel.updatePhoto = true
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: currentMode == "ecueil" ? qsTr("Annuler") : qsTr("Selection écueil")
            checkable: false
            enabled: !RobotModel.updatePhoto
            highlighted: currentMode == "ecueil"
            onClicked: {
                posEcueil = []
                couleurEcueil = getPrimaryColor(2)
                currentMode = currentMode == "ecueil" ? "" : "ecueil"
            }
        }

        Button {
            text: currentMode == "bouees" ? qsTr("Annuler") : qsTr("Selection bouées")
            checkable: false
            enabled: !RobotModel.updatePhoto
            highlighted: currentMode == "bouees"
            onClicked: {
                posBouees = []
                couleurBouees = getPrimaryColor(nbBoueeCalibration)
                currentMode = currentMode == "bouees" ? "" : "bouees"
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: qsTr("Valider")
            checkable: false
            onClicked: {
                RobotModel.setPosEcueilForQML(posEcueil)
                RobotModel.setPosBoueesForQML(posBouees)
                RobotModel.etalonnageBalise = true
            }
            enabled: btnValiderEnabled()
        }
    }

    Flickable {
        id: imgContainer

        anchors.top: buttons.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        boundsMovement: Flickable.StopAtBounds
        flickDeceleration: 0

        // FIXME ça devrait dépendre de imgBalise mais le Flickable se bloque quand on change à la volée
        contentWidth: 1280;
        contentHeight: 960
        contentX: 1280 / 2 - this.width / 2
        contentY: 960 / 2 - this.height / 2

        Image {
            id: imgBalise
            cache: false
            source: "data:image/jpeg;base64," + RobotModel.photo

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (currentMode == "ecueil") {
                        // la référence doit changer pour que le Repeater se mette à jout
                        posEcueil = posEcueil.concat(Qt.point(this.mouseX, this.mouseY))
                        if (posEcueil.length === 2) {
                            currentMode = ""
                        }
                    } else if (currentMode == "bouees") {
                        posBouees = posBouees.concat(Qt.point(this.mouseX, this.mouseY))
                        if (posBouees.length === nbBoueeCalibration) {
                            currentMode = ""
                        }
                    }
                }
            }
        }

        Connections {
            target: RobotModel
            onPhotoChanged: {
                imgBalise.source = "data:image/jpeg;base64," + RobotModel.photo
            }
            onCouleurEcueilChanged: {
                couleurEcueil = RobotModel.couleurEcueil
            }
            onCouleurBoueesChanged: {
                couleurBouees = RobotModel.couleurBouees
            }
        }

        Repeater {
            model: posEcueil
            delegate: Rectangle {
                color: couleurEcueil[index]
                opacity: 0.7
                width: 30
                height: 30
                radius: 15
                x: modelData.x - 15
                y: modelData.y - 15

                Text {
                    anchors.fill: parent
                    text: index == 0 ? "L" : "R"
                    color: "white"
                    font.pointSize: 15
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Repeater {
            model: posBouees
            delegate: Rectangle {
                color: couleurBouees[index]
                opacity: 0.7
                width: 30
                height: 30
                radius: 15
                x: modelData.x - 15
                y: modelData.y - 15

                Text {
                    anchors.fill: parent
                    text: index + 1
                    color: "white"
                    font.pointSize: 15
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    BusyIndicator {
        anchors.top: buttons.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 100
        height: 100
        running: RobotModel.updatePhoto
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:32}D{i:2;anchors_x:42;anchors_y:5}D{i:3;anchors_x:42;anchors_y:5}
}
##^##*/

