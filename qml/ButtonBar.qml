import QtQuick 1.1

MouseArea {
    width: buttons.width+5
    height: buttons.height+3
    hoverEnabled: true

    signal leftClicked()
    signal rightClicked()

    Rectangle {
        anchors.fill: parent
        color: "white"
        radius: 5
        opacity: parent.containsMouse ? 0.3 : 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }

    Row {
        id: buttons
        spacing: 2
        opacity: parent.containsMouse
        anchors.centerIn: parent
        
        Image {
            source: "images/arrow-left.png"
            MouseArea {
                anchors.fill: parent
                onClicked: leftClicked()
            }
        }
        
        Image {
            source: "images/arrow-right.png"
            MouseArea {
                anchors.fill: parent
                onClicked: rightClicked()
            }
        }
        
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }
}
