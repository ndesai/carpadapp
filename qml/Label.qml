import QtQuick 2.7
import app.st 1.0

Text {
    id: root
//    font.bold: true
    font.family: "Work Sans"

    elide: Text.ElideRight

    text: "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

    Rectangle {
        width: root.width
        height: root.height
        color: "transparent"
        border.width: 1
        border.color: visible ? Utility.getRandomColor() : "transparent"
        visible: Utility.isDebugAllEnabled
    }
}
