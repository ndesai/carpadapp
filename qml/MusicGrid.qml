import QtQuick 2.7
import app.st 1.0

GridView {
    anchors.fill: _itemContainer
    cellWidth: width / 5
    cellHeight: height / 4

    delegate: Item {
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight

        Rectangle {
            anchors.fill: parent
            anchors.margins: dp(20)
            color: index%2===0?"blue":"red"
        }
    }
}
