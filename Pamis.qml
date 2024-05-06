import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Process 1.0

Page {
    id: page
    anchors.fill: parent

    title: "Etats des PAMIs"

    function getBooleanColor(value) {
        return value ? "green" : "red";
    }

    function sendSSHCmd(hostName, cmd) {
        term.text = "Send to " + hostName + " " + cmd;
        sshCmd.start("ssh", [hostName, "touch", "/tmp/external-dir/" + cmd ]);
    }

    Process {
        id: sshCmd

        property string output: ""

        onReadyReadStandardOutput: {
            output = sshCmd.readAll();
            term.text += output;
        }
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
                onClicked: sendSSHCmd("pami-triangle", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHCmd("pami-triangle", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHCmd("pami-triangle", "poweroff")
            }

            Button {
                text: "Shutdown"
                onClicked: sendSSHCmd("pami-triangle", "shutdown")
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
                onClicked: sendSSHCmd("pami-carre", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHCmd("pami-carre", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHCmd("pami-carre", "poweroff")
            }

            Button {
                text: "Shutdown"
                onClicked: sendSSHCmd("pami-carre", "shutdown")
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
                onClicked: sendSSHCmd("pami-rond", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHCmd("pami-rond", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHCmd("pami-rond", "poweroff")
            }

            Button {
                text: "Shutdown"
                onClicked: sendSSHCmd("pami-rond", "shutdown")
            }
        }

        TextArea {
            id: term
            anchors.left: parent.left
            anchors.right: parent.right
            textFormat: TextArea.RichText
            height: 200
        }
    }
}
