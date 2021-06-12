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

    property var etalonnageDone: false

    Component.onCompleted: {
        RobotModel.updatePhoto = true
    }

    RowLayout {
        id: buttons
        spacing: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        Button {
            text: qsTr("Photo")
            enabled: !RobotModel.updatePhoto && !RobotModel.etalonnageBalise
            highlighted: RobotModel.updatePhoto
            onClicked: {
                RobotModel.updatePhoto = true
            }
        }

        Label {
            text: RobotModel.photoMessage
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 16
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            text: qsTr("Étalonnage")
            enabled: !RobotModel.updatePhoto && !RobotModel.etalonnageBalise
            highlighted: RobotModel.etalonnageBalise
            onClicked: {
                RobotModel.etalonnageBalise = true
                RobotModel.etalonnageOk = false
                etalonnageDone = true
            }
        }

        Button {
            text: qsTr("Valider")
            enabled: !RobotModel.updatePhoto && !RobotModel.etalonnageBalise && etalonnageDone
            highlighted: RobotModel.etalonnageOk
            onClicked: {
                RobotModel.etalonnageOk = true
            }
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
        contentWidth: 1500
        contentHeight: 1100
        contentX: 1500 / 2 - this.width / 2
        contentY: 1100 / 2 - this.height / 2

        Image {
            id: imgBalise
            cache: false
            source: "data:image/jpeg;base64," + RobotModel.photo
        }

        Connections {
            target: RobotModel
            onPhotoChanged: {
                imgBalise.source = "data:image/jpeg;base64," + RobotModel.photo
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
        running: RobotModel.updatePhoto || RobotModel.etalonnageBalise
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:32}D{i:2;anchors_x:42;anchors_y:5}D{i:3;anchors_x:42;anchors_y:5}
}
##^##*/

