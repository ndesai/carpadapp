import QtQuick 2.7
import app.st 1.0

Item {
    id: root
    focus: true

    property var keyMapping: ({})

    QtObject {
        id: internal

        function keyByValue(value) {
            for (var key in keyMapping) {
                if (keyMapping[key] === value) {
                    return key;
                }
            }
            return null;
        }
    }

    Keys.onPressed: {
        for (var key in keyMapping) {
            if (eval(key) == event.key) {
                var fn = keyMapping[key];
                if (fn) {
                    fn();
                }
            }
        }
    }

    Timer {
        interval: 1000
        running: true; repeat: true;
        onTriggered: {
            root.forceActiveFocus();
        }
    }
}
