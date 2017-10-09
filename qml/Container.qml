import QtQuick 2.7
import app.st 1.0

BaseVisualContainer {
    id: root

    signal pressed
    signal clicked

    /*! This property holds true when this container is pressed */
    property bool isPressed: _mouseArea.pressed

    /*! This property holds the background color of this container */
    property color backgroundColor: "transparent"

    debugFlags: Utility.DebugTypeContainer

    Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
    }

    MouseArea {
        id: _mouseArea
        anchors.fill: parent
        onPressed: root.pressed()
        onClicked: root.clicked()
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: visible ? Utility.getRandomColor() : "transparent"
        visible: Utility.isDebugAllEnabled
    }
}
