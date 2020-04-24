import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import AuthManager 1.0

Item {
    width: parent.width
    height: parent.height
    anchors.fill: parent

    Authmanager {
        id: authManager
        onRegisterFinished: {
            success.text = "Register completed successfully!"
            success.open()
        }
        onRegisterFailed: {
            success.text = "Register failed!\nError: " + error
            success.open()
         }
    }

    Text {
        id: title
        text: qsTr("SIGN UP")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        font.pixelSize: 25
    }

    TextField {
        id: login
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: title.bottom
        anchors.topMargin: 5
        font.pointSize: 13
        placeholderText: "login"
        font.pixelSize: 20
    }

    TextField {
        id: password
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: login.bottom
        anchors.topMargin: 5
        font.pointSize: 13
        placeholderText: "password"
        font.pixelSize: 20
        echoMode: TextInput.Password
    }

    TextField {
        id: repeatPassword
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: password.bottom
        anchors.topMargin: 5
        font.pointSize: 13
        placeholderText: "repeat password"
        font.pixelSize: 20
        echoMode: TextInput.Password
    }

    TextField {
        id: nickname
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: repeatPassword.bottom
        anchors.topMargin: 5
        font.pointSize: 13
        placeholderText: "nickname"
        font.pixelSize: 20
    }

    Button {
        id: buttonSignUp
        text: qsTr("Sign up")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: nickname.bottom
        anchors.topMargin: 5
        font.pixelSize: 15
        enabled: login.length > 5 && password.length > 5 && repeatPassword.length > 5 && nickname.length > 5
        onClicked: {
            busyIndicator.visible = true
            if (password.text !== repeatPassword.text)
                wrongPassword.visible = true
            else
            {
                wrongPassword.visible = false
                authManager.registering(login.text, password.text)
            }
        }
    }

    Text {
        id: wrongPassword
        text: qsTr("Password values aren't same!")
        font.pixelSize: 20
        color: "Red"
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: buttonSignUp.bottom
        anchors.topMargin: 5
    }

    BusyIndicator {
        id: busyIndicator        
        running: authManager.getindicatorRun()
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: buttonSignUp.bottom
        anchors.topMargin: 10
    }

    MessageDialog{
        id: success
        title: qsTr("Result")
        standardButtons: Dialog.Ok
    }
}
