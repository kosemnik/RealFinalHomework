import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12

Item {
    width: parent.width
    height: parent.height
    anchors.fill: parent

    Text {
        id: title
        text: qsTr("SIGN IN")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        font.pixelSize: 25
    }

    TextField {
        id: login
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 20
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 5
        anchors.top: title.bottom
        placeholderText: "login..."
        font.pixelSize: 20
    }

    TextField {
        id: password
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 20
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 5
        anchors.top: login.bottom
        placeholderText: "password..."
        font.pixelSize: 20
        echoMode: TextInput.Password
    }

    Button {
        id: buttonSignIn
        text: qsTr("Sign in")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: password.bottom
        anchors.topMargin: 5
        font.pixelSize: 15
        enabled: login.length > 5 && password.length > 5
        onClicked: busyIndicator.visible = true
    }

    BusyIndicator {
        id: busyIndicator
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: buttonSignIn.bottom
        anchors.topMargin: 10
    }
}
