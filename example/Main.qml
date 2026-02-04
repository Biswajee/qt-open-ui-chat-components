import QtQuick 2.15
import QtQuick.Window 2.15
import ChatUI 1.0

Window {
    visible: true
    width: 480
    height: 640
    title: "Chat Example"

    ChatFrame {
        anchors.fill: parent
        messages: [
            "Hello!",
            "Welcome to open-web-ui styled chat.",
            "Resize the window to see responsive layout."
        ]
    }
}