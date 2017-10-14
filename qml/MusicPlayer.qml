import QtQuick 2.6
import QtQuick.XmlListModel 2.0

Container {
    id: root

    property bool isOpen: false

    property var songModel: null

    property alias currentlyPlayingAlbumArtwork: _imageAlbumArtwork

    function dp(x) { return 1.6*x; }

    width: dp(500)
    height: dp(768)
    backgroundColor: "#192225"

    Container {
        anchors.top: parent.top
        anchors.topMargin: dp(40)
        anchors.right: parent.left
        backgroundColor: "#192225"

        width: dp(100)
        height: dp(120)

        onClicked: {
            root.isOpen ^= 1;
        }
    }

    //    XmlListModel {
    //        id: _XmlListModel
    //        source: "http://itunes.apple.com/us/rss/topalbums/limit=100/xml"
    //        namespaceDeclarations: "declare namespace im = 'http://itunes.apple.com/rss'; declare default element namespace 'http://www.w3.org/2005/Atom';"
    //        query: "/feed/entry"
    //        XmlRole { name: "identifier"; query: "id/@im:id/string()" }
    //        XmlRole { name: "title"; query: "im:name/string()" }
    //        XmlRole { name: "artist"; query: "im:artist/string()" }
    //        XmlRole { name: "image"; query: "im:image[3]/string()" }
    //        XmlRole { name: "link"; query: "link/@href/string()" }
    //        XmlRole { name: "copyright"; query: "rights/string()" }
    //        XmlRole { name: "releaseDate"; query: "im:releaseDate/@label/string()" }
    //        XmlRole { name: "price"; query: "im:price/string()" }
    //    }

    Container {
        id: _topContainer

        width: parent.width
        height: dp(320)

        Container {
            id: _artworkContainer

            anchors.centerIn: parent
            width: dp(280)
            height: width

            backgroundColor: "#42595f"

            Image {
                id: _imageLoader
                width: 0; height: 0

                onStatusChanged: {
                    if (status === Image.Ready) {
                        _imageAlbumArtwork.source = source;
                    }
                }
            }

            Image {
                id: _imageAlbumArtwork
                property var activeTrackDelegate: _listViewTracks.currentItem ?
                                                      _listViewTracks.currentItem
                                                    : null

                onActiveTrackDelegateChanged: {
                    if (!activeTrackDelegate) return;
                    _imageLoader.source = activeTrackDelegate.albumArt.getSizedImage(width, height)
                }

                anchors.fill: parent
                sourceSize.width: width
                sourceSize.height: height

                // NOTE: source is set by the image loader component
            }
        }
    }

    Container {
        id: _bottomContainer

        anchors.top: _topContainer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ListView {
            id: _listViewTracks
            anchors.fill: parent
            model: root.songModel
            clip: true
            delegate: MusicPlayerSongDelegate {
                name: model.name
                artistName: model.artistName
                albumName: ""
                albumArtwork: model.artwork.url
                duration: model.durationForDisplay
            }
        }
    }

    StateGroup {
        id: _stateGroupVisibility
        state: "hidden"
        states: [
            State {
                name: "hidden"
                when: !isOpen
                PropertyChanges {
                    target: root
                    anchors.rightMargin: -1*root.width
                }
            }
        ]

        transitions: [
            Transition {
                from: "hidden"
                to: ""
                reversible: true
                NumberAnimation {
                    target: root
                    property: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutCubic
                    easing.overshoot: 0.4
                }
            }
        ]
    }
}
