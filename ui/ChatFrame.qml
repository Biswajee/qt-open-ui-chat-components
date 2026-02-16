import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root

    readonly property bool isDark: chatModel ? chatModel.isDarkTheme : true
    
    // Colors
    readonly property color bgColor: isDark ? "#212121" : "#ffffff"
    readonly property color textColor: isDark ? "#ececf1" : "#000000"
    readonly property color userBubbleColor: isDark ? "#343541" : "#e0e0e0"
    readonly property color inputBgColor: isDark ? "#40414f" : "#f0f0f0"
    readonly property color borderColor: isDark ? "#303030" : "#d0d0d0"
    
    color: bgColor

    property var chatModel

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Header with Theme Toggle
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: "transparent"
            
            // Bottom border
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: root.borderColor
            }
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                
                Text {
                    text: "Open Web UI Chat"
                    font.bold: true
                    font.pixelSize: 16
                    color: root.textColor
                    Layout.fillWidth: true
                }
                
                Button {
                    text: root.isDark ? "Light Mode" : "Dark Mode"
                    onClicked: {
                        if (root.chatModel) root.chatModel.toggleTheme()
                    }
                    background: Rectangle {
                        color: root.inputBgColor
                        radius: 4
                        border.color: root.borderColor
                    }
                    contentItem: Text {
                        text: parent.text
                        color: root.textColor
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: root.chatModel
            spacing: 20
            displayMarginBeginning: 40
            displayMarginEnd: 40
            bottomMargin: 20

            delegate: RowLayout {
                width: listView.width
                layoutDirection: model.role === "user" ? Qt.RightToLeft : Qt.LeftToRight
                spacing: 10

                // Avatar
                Rectangle {
                    width: 32
                    height: 32
                    radius: 16
                    color: model.role === "user" ? "#ececf1" : "#10a37f"
                    Layout.alignment: Qt.AlignTop
                    Layout.leftMargin: model.role === "assistant" ? 16 : 0
                    Layout.rightMargin: model.role === "user" ? 16 : 0
                    
                    Text {
                        anchors.centerIn: parent
                        text: model.role === "user" ? "U" : "A"
                        font.bold: true
                        color: model.role === "user" ? "#000000" : "#ffffff"
                    }
                }

                // Message
                Rectangle {
                    Layout.maximumWidth: listView.width * 0.7
                    Layout.preferredWidth: messageText.implicitWidth + 24
                    Layout.preferredHeight: messageText.implicitHeight + 24
                    color: "transparent"
                    
                    Rectangle {
                        anchors.fill: parent
                        color: model.role === "user" ? root.userBubbleColor : "transparent"
                        radius: 8
                        visible: model.role === "user"
                    }

                    Text {
                        id: messageText
                        anchors.centerIn: parent
                        width: parent.width - 24
                        text: model.content
                        color: root.textColor
                        wrapMode: Text.Wrap
                        font.pixelSize: 16
                        lineHeight: 1.5
                    }
                }
                
                Item {
                    Layout.fillWidth: true
                }
            }

            onCountChanged: {
                Qt.callLater(function() {
                    listView.positionViewAtEnd()
                })
            }
        }

        // Input Area
        Rectangle {
            Layout.fillWidth: true
            height: inputRow.implicitHeight + 40
            color: "transparent"

            Rectangle {
                anchors.centerIn: parent
                width: Math.min(parent.width - 40, 800)
                height: inputRow.implicitHeight + 24
                color: root.inputBgColor
                radius: 12
                border.color: root.borderColor
                border.width: 1

                RowLayout {
                    id: inputRow
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 12

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.preferredHeight: Math.min(inputArea.implicitHeight, 150)
                        
                        TextArea {
                            id: inputArea
                            placeholderText: "Send a message..."
                            color: root.textColor
                            font.pixelSize: 16
                            wrapMode: Text.Wrap
                            selectByMouse: true
                            enabled: !root.chatModel || !root.chatModel.isProcessing
                            
                            background: null
                            
                            Keys.onReturnPressed: (event) => {
                                if (event.modifiers & Qt.ShiftModifier) {
                                    event.accepted = false
                                } else {
                                    sendButton.clicked()
                                    event.accepted = true
                                }
                            }
                        }
                    }

                    Button {
                        id: sendButton
                        Layout.alignment: Qt.AlignBottom
                        text: (root.chatModel && root.chatModel.isProcessing) ? "..." : "Send"
                        enabled: inputArea.text.trim().length > 0 && root.chatModel && !root.chatModel.isProcessing
                        
                        background: Rectangle {
                            implicitWidth: 60
                            implicitHeight: 36
                            color: parent.enabled ? "#19c37d" : "#505050"
                            radius: 4
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true
                        }

                        onClicked: {
                            if (root.chatModel) {
                                root.chatModel.sendMessage(inputArea.text.trim())
                                inputArea.text = ""
                            }
                        }
                    }
                }
            }
        }
    }
}
