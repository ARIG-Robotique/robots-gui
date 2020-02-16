import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: element
    height: 35

    property string libelle: libelle
    property string stateColor: "gray"
    width: 300

    Label {
        id: lblTxt
        x: -2
        y: -2
        text: libelle
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        font.pointSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: rectState.left
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Rectangle {
        id: rectState
        x: 331
        y: -2
        width: 35
        color: stateColor
        radius: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:35}D{i:2;anchors_height:35}
}
##^##*/
