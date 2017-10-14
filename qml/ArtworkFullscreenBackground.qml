import QtQuick 2.7

import QtGraphicalEffects 1.0 as QGE

Item {
    id: root
    anchors.fill: parent

    property alias source: _fastBlur.source

    /*! This property holds an overlay color for the artwork */
    property color artworkOverlayColor: "transparent"

    QGE.FastBlur {
        id: _fastBlur
        radius: 150
//        samples: 16
        anchors.centerIn: parent
        width: parent.width * 2
        height: parent.height * 2
        rotation: -90

        Rectangle {
            anchors.fill: parent
            color: root.artworkOverlayColor
            opacity: 0.5
            visible: color !== "transparent"
        }

        SequentialAnimation {
            id: _sequentialAnimationKinetic
            running: true; loops: Animation.Infinite
            ParallelAnimation {
                NumberAnimation {
                    target: _fastBlur
                    property: "rotation"
                    from: -90; to: 90;
                    duration: resolveAnimation(240000)
                }
                NumberAnimation {
                    target: _fastBlur
                    property: "scale"
                    from: 1.0; to: 1.1;
                    duration: resolveAnimation(240000)
                }
                NumberAnimation {
                    target: _fastBlur
                    property: "radius"
                    from: 120; to: 140;
                    duration: resolveAnimation(240000)
                }
            }
            ParallelAnimation {
                NumberAnimation {
                    target: _fastBlur
                    property: "rotation"
                    from: 90; to: -90;
                    duration: resolveAnimation(240000)
                }
                NumberAnimation {
                    target: _fastBlur
                    property: "scale"
                    from: 1.1; to: 1.0;
                    duration: resolveAnimation(240000)
                }
                NumberAnimation {
                    target: _fastBlur
                    property: "radius"
                    from: 140; to: 120;
                    duration: resolveAnimation(240000)
                }
            }
        }
    }
}
