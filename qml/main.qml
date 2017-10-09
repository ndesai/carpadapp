import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: root

    property int actualWidth: 2048
    property int actualHeight: 1536

    visible: true
    width: actualWidth / 2
    height: actualHeight / 2

    Loader {
        id: _loaderViewport

        width: root.actualWidth
        height: root.actualHeight
        focus: true

        transform: Scale {
            xScale: 0.5; yScale: xScale;
        }

        source: "Viewport.qml"

        onLoaded: {
            if (item) {
                item.forceActiveFocus();
            }
        }
    }
}
