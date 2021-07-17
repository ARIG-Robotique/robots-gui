import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1

RowLayout {
    Layout.maximumHeight: 35
    Layout.minimumHeight: 35

    property string libelle: libelle
    property string stateColor: "gray"

    Label {
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: libelle
        font.pointSize: 16
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        Layout.fillHeight: true
        width: 35
        color: stateColor
        radius: 10
    }
}
