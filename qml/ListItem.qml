import QtQuick 1.1

Item {
    property alias title: header.text
    property string content

    Text {
        id: header
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        width: parent.width
        color: "white"
    }

    Flickable {
        id: flickableContent
        anchors {
            top: header.bottom; topMargin: 5
            left: parent.left
            right: parent.right //scrollBar.visible ? scrollBar.left : parent.right
            bottom: parent.bottom
        }
        boundsBehavior: Flickable.StopAtBounds
        contentWidth: width
        contentHeight: contentText.paintedHeight
        clip: true

        Text {
            id: contentText
            text: "<style>dd { margin-top:5px; }</style>" + content
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            color: "white"
            width: parent.width-30
            font.pixelSize: 12
            anchors {
                top: parent.top
                left: parent.left
            }
        }
    }

    /*Components.ScrollBar {
        id: scrollBar
        flickableItem: flickableContent
        anchors {
            right: parent.right
            top: flickableItem.top
            bottom: flickableItem.bottom
        }
    }*/
}
