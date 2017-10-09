import QtQuick 2.6
import app.st 1.0

BaseViewport {
    id: root
    width: 1024
    height: 768
    //    scale: 0.5

    focus: true

    keyMapping: {
        "Qt.Key_D" : function() {
            Utility.isDebugAllEnabled ^= 1;
        }
    }

    function resolveAsset(name) {
        var prefix = "../";
        if (Qt.platform.os === "ios") {
            prefix = "qrc:///";
        }
        return prefix + "img/" + name;
    }

    function resolveAnimation(duration) {
        return duration * 2;
    }

    function dp(value) {
        return value;
    }

    AppleMusic {
        id: _appleMusic

        topSongsModel: TopSongsModel {
            id: _topSongsModel
        }

        Component.onCompleted: {
            createRequest("/catalog/us/charts?types=songs&genre=18&limit=25", function(json) {
                var obj = JSON.parse(json);
                console.log(JSON.stringify(obj.results, null, 2));

                _topSongsModel.initializeWithJson(json);
            });
        }
    }

    Image {
        anchors.fill: parent
        source: resolveAsset("asset-bg-sunset.png")

        ArtworkFullscreenBackground {
            source: _musicPlayer.currentlyPlayingAlbumArtwork
//            artworkOverlayColor: "#222222"
        }
    }

    MusicPlayer {
        id: _musicPlayer
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        songModel: _topSongsModel
    }

    Item {
        id: _itemContainer
        anchors.fill: parent
        anchors.topMargin: dp(50)
        anchors.leftMargin: dp(40)
        anchors.rightMargin: dp(40)
        anchors.bottomMargin: dp(50)

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.width: 1
            border.color: "#77CCCCCC"
        }

        Row {
            id: _rowTopLeft
            anchors.top: parent.top
            anchors.left: parent.left

            height: _imageMercedesLogo.height

            spacing: dp(24)

            Image {
                id: _imageMercedesLogo
                anchors.verticalCenter: parent.verticalCenter
                width: dp(40)
                fillMode: Image.PreserveAspectFit
                source: resolveAsset("asset-mercedes-logo.png")
                smooth: true
            }

            Image {
                id: _imageAmgLogo
                anchors.verticalCenter: parent.verticalCenter
                width: dp(175)
                fillMode: Image.PreserveAspectFit
                source: resolveAsset("asset-amg-logo.png")
                smooth: true
            }
        }

        Row {
            id: _rowBottomLeft
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: _imageNdLogo.height

            spacing: dp(-24)

            Image {
                id: _imageNdLogo
                width: dp(50)
                fillMode: Image.PreserveAspectFit
                source: resolveAsset("asset-nd-logo.png")
                smooth: true
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: dp(4)
                source: resolveAsset("c43-trim.png")
                width: dp(200)
                fillMode: Image.PreserveAspectFit
                smooth: true
            }
        }
    }
}
