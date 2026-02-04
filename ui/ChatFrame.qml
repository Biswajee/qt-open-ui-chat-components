import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: chatFrame
    property alias messages: messagesModel.list
    color: "#18181b"
    radius: 16
    anchors.fill: parent
    border.color: "#27272a"
    border.width: 1
    layer.enabled: true
    layer.effect: DropShadow {
        color: "#00000080"
        radius: 12
        samples: 16
        spread: 0.2
        horizontalOffset: 0
        verticalOffset: 4
    }
    padding: 16

    ListView {
        id: messagesView
        anchors.fill: parent
        model: messagesModel
        spacing: 8
        clip: true

        delegate: Rectangle {
            width: parent.width
            height: implicitHeight
            color: "#27272a"
            radius: 8
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: modelData
                color: "#fafafa"
                font.pixelSize: 16
                wrapMode: Text.Wrap
                anchors.margins: 12
                anchors.fill: parent
            }
        }
    }

    ListModel {
        id: messagesModel
        // Example: ListElement { text: "Hello!" }
    }
}