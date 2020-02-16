import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    id: page
    width: 800
    height: 430

    title: qsTr("Paramétrage balise")

    Image {
        id: imgBalise
        x: 5
        y: 5
        fillMode: Image.PreserveAspectFit
        source: "img/20190504150746-source-idle-18.jpg"
        anchors.top: btnBoueeGauche.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Button {
        id: btnBoueeGauche
        text: qsTr("Selection bouée gauche")
        checkable: false
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 5
    }

    Button {
        id: btnBoueeDroite
        x: 42
        y: -6
        text: qsTr("Selection bouée droite")
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.topMargin: 5
        anchors.top: parent.top
        checkable: false
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:32}D{i:2;anchors_x:42;anchors_y:5}D{i:3;anchors_x:42;anchors_y:5}
}
##^##*/

