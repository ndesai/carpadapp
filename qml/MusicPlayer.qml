import QtQuick 2.6
import QtQuick.XmlListModel 2.0

Container {
    id: root

    property var songModel: null

    property alias currentlyPlayingAlbumArtwork: _imageAlbumArtwork

    function dp(x) { return 1.6*x; }

    width: dp(500)
    height: dp(768)
    backgroundColor: "#192225"

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

    //    ListView {
    //        id: _listView

    //        signal imageLoaded(int index, var imageObject)

    //        anchors.fill: parent
    //        model: _topSongsModel
    //        orientation: ListView.Horizontal
    //        highlightRangeMode: ListView.StrictlyEnforceRange
    //        preferredHighlightBegin: 0
    //        preferredHighlightEnd: width - 1

    //        delegate: Item {
    //            id: _itemDelegate
    //            property var modelData: model
    //            property alias image: _imageCenter

    //            width: ListView.view.width
    //            height: ListView.view.height

    //            Item {
    //                id: _imageContainer
    //                anchors.centerIn: parent
    //                width: dp(560); height: width

    //                Image {
    //                    id: _imageCenter
    //                    anchors.fill: parent
    //                    cache: true; asynchronous: true

    //                    source: model.artwork.url.replace("{w}", width).replace("{h}", height)

    //                    onStatusChanged: {
    //                        _itemDelegate.ListView.view.imageLoaded(index, _imageCenter);
    //                    }
    //                }
    //            }

    //            Column {
    //                anchors.top: _imageContainer.bottom
    //                anchors.topMargin: dp(40)
    //                anchors.horizontalCenter: parent.horizontalCenter

    //                width: _itemContainer.width

    //                spacing: dp(14)

    //                Text {
    //                    width: parent.width
    //                    horizontalAlignment: Text.AlignHCenter
    //                    color: "#FFFFFF"
    //                    font.pixelSize: dp(42)
    //                    font.bold: true
    //                    text: model.name
    //                }

    //                Text {
    //                    width: parent.width
    //                    horizontalAlignment: Text.AlignHCenter
    //                    color: "#FEFEFE"
    //                    font.pixelSize: dp(36)
    //                    font.bold: true
    //                    text: model.artistName
    //                }
    //            }
    //        }
    //    }
}
