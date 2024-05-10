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

    function sendSSHArigCmd(hostName, cmd) {
        term.text = "Send to " + hostName + " " + cmd;
        sshCmd.start("ssh", [hostName, "touch", "/tmp/external-dir/" + cmd ]);
    }

    function sendSSHSystemCmd(hostName, cmd) {
        term.text = "Send to " + hostName + " " + cmd;
        sshCmd.start("ssh", [hostName, "sudo", cmd ]);
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
                onClicked: sendSSHArigCmd("pami-triangle.local", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHArigCmd("pami-triangle.local", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHSystemCmd("pami-triangle.local", "poweroff")
            }

            Button {
                text: "Reboot"
                onClicked: sendSSHSystemCmd("pami-triangle.local", "reboot")
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
                onClicked: sendSSHArigCmd("pami-carre.local", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHArigCmd("pami-carre.local", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHSystemCmd("pami-carre.local", "poweroff")
            }

            Button {
                text: "Reboot"
                onClicked: sendSSHSystemCmd("pami-carre.local", "reboot")
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
                onClicked: sendSSHArigCmd("pami-rond.local", "run")
            }

            Button {
                text: "Monitoring"
                onClicked: sendSSHArigCmd("pami-rond.local", "monitoring")
            }

            Button {
                text: "Power OFF"
                onClicked: sendSSHSystemCmd("pami-rond.local", "poweroff")
            }

            Button {
                text: "Reboot"
                onClicked: sendSSHSystemCmd("pami-rond.local", "reboot")
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
