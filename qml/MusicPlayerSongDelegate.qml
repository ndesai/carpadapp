import QtQuick 2.7
import app.st 1.0

import QtGraphicalEffects 1.0 as QGE

Container {
    id: root

    property string name: "Song Name"
    property string artistName: "Artist Name"
    property string albumName: "Album Name"
    property alias albumArt: _imageAlbumArt
    property string duration: Math.ceil(Math.random()*5) + ":" + Math.floor(Math.random()*60)

    property var albumArtwork


    readonly property bool isPlaying: ListView.view.currentIndex === index

    width: ListView.view.width
    height: dp(80)

    backgroundColor: index%2===0 ? "#252f32" : "#17272b"

    onClicked: {
        root.ListView.view.currentIndex = index;
    }

    Container {
        id: _containerAlbumArt

        width: dp(60)
        height: width

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: dp(14)

        Image {
            id: _imageAlbumArt

            function getSizedImage(w, h) {
                if (root.albumArtwork) {
                    return root.albumArtwork.replace("{w}", w).replace("{h}", h);
                }
                console.warn("root.albumArtwork not defined");
                return "";
            }

            anchors.fill: parent
            sourceSize.width: width
            sourceSize.height: height

            source: getSizedImage(width, height)

            layer.enabled: true
            layer.effect: QGE.OpacityMask {
                maskSource: Item {
                    width: _imageAlbumArt.width
                    height: _imageAlbumArt.height

                    Rectangle {
                        width: parent.width
                        height: parent.height
                        radius: root.isPlaying ? width / 2 : 0

                        Behavior on radius {
                            NumberAnimation {
                                duration: 120
                                easing.type: Easing.OutCubic
                            }
                        }
                    }
                }
            }
        }

        Container {
            id: _containerNowPlayingAlbum
            anchors.fill: parent

            visible: root.isPlaying

            layer.enabled: visible
            layer.effect: QGE.OpacityMask {
                maskSource: Item {
                    width: _containerNowPlayingAlbum.width
                    height: _containerNowPlayingAlbum.height

                    Rectangle {
                        width: parent.width
                        height: parent.height

                        radius: width / 2
                    }
                }
            }

            QGE.FastBlur {
                width: _containerNowPlayingAlbum.width
                height: _containerNowPlayingAlbum.height
                source: visible ? _imageAlbumArt : null
                radius: 60

                anchors.centerIn: parent

                NumberAnimation on rotation {
                    running: true
                    loops: Animation.Infinite

                    from: 0; to: 360;
                    duration: 1200
                }
            }

            Rectangle {
                width: dp(10)
                height: width

                radius: width / 2

                anchors.centerIn: parent
                color: root.backgroundColor
            }

            Rectangle {
                width: parent.width
                height: parent.height

                radius: width / 2
                color: "transparent"
                border.width: 1
                border.color: model.artwork.bgColor
            }
        }
    }

    Column {
        anchors.left: _containerAlbumArt.right
        anchors.leftMargin: dp(14)
        anchors.verticalCenter: parent.verticalCenter

        anchors.right: _containerRight.left

        Label {
            // Track name
            width: parent.width
            color: "white"
            text: root.name
            font.pixelSize: dp(18)
            font.letterSpacing: 1.03
        }

        Label {
            // Artist name
            width: parent.width
            color: "white"
            text: root.artistName
            font.pixelSize: dp(16)
            font.letterSpacing: 0.99
        }
    }

    Container {
        id: _containerRight
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: dp(80)

        Label {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            color: "white"
            font.pixelSize: dp(14)
            text: root.duration
        }
    }
}
