import QtQuick 1.1

Item {
    id: applet
    width: 470
    height: 200

    property int tickInterval: 5 // in minutes

    function setTickInterval(interval) {
        tickInterval = interval;
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        radius: 5
    }

    XmlListModel {
        id: xmlModel
        source: "friends.xml"
        query: "/friends-quotes/quote"
        
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "content"; query: "content/string()" }

        onStatusChanged: {
            if (status==XmlListModel.Ready && ticker.model==0)
                ticker.model = randomize(count);
        }
    }

    Timer {
        id: tickTimer
        interval: tickInterval*60000; running: true; repeat: true
        onTriggered: ticker.currentIndex = (ticker.currentIndex+1)%xmlModel.count;
    }

    function randomize(count) {
        if (count<0) return [];
        var a = new Array(count);

        for(var i=0; i<count; i++)
            a[i] = i;

        for(i=a.length-1; i>0; i--) {
            var j = Math.floor(Math.random() * (i + 1));

            // Swap the elements at positions i and j.
            var temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        
        return a;
    }

    ListView {
        id: ticker
        anchors {
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 5
            left: parent.left
            right: parent.right
        }
        model: 0
        clip: true
        orientation: ListView.Horizontal
        snapMode: ListView.SnapToItem
        highlightMoveDuration: 500
        interactive: false

        delegate: ListItem {
            title: xmlModel.get(modelData).title
            content: xmlModel.get(modelData).content
            width: ticker.width
            height: ticker.height
        }
        
        Component.onCompleted: currentIndex = 0
    }


    MouseArea {
        anchors.fill: parent
        onClicked: print("click");
    }

    /*ButtonBar {
        id: buttonBar
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 10
        }
        onLeftClicked: moveTicker(-1);
        onRightClicked: moveTicker(1);

        function moveTicker(direction) {
            if (direction>0) ticker.currentIndex = (ticker.currentIndex+1)%xmlModel.count;
            else if (direction<0 && ticker.currentIndex>0) ticker.currentIndex--;
            tickTimer.restart();
        }
    }*/
}
