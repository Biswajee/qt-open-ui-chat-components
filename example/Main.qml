import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ChatUI 1.0

Rectangle {
    id: root
    width: 480
    height: 800
    color: "#ffffff" // Default light

    property var chatModel: null

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: 0

        // Screen 1: Connect
        Rectangle {
            color: "#f0f0f0"
            
            ColumnLayout {
                anchors.centerIn: parent
                width: parent.width * 0.8
                spacing: 20

                Text {
                    text: "Connect to Server"
                    font.bold: true
                    font.pixelSize: 24
                    color: "#000000"
                    Layout.alignment: Qt.AlignHCenter
                }

                TextField {
                    id: urlField
                    Layout.fillWidth: true
                    placeholderText: "http://localhost:8080/v1/chat/completions"
                    text: "http://localhost:8080/v1/chat/completions"
                    selectByMouse: true
                }

                Button {
                    text: "Connect"
                    Layout.fillWidth: true
                    highlighted: true
                    onClicked: {
                        if (root.chatModel) {
                            root.chatModel.setRemoteUrl(urlField.text)
                            // Switch to chat view
                            stackLayout.currentIndex = 1
                        }
                    }
                }
            }
        }

        // Screen 2: Chat
        ChatFrame {
            chatModel: root.chatModel
        }
    }
}
