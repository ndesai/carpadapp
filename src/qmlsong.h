#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QDebugStateSaver>

class QmlSong : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString artistName READ artistName WRITE setArtistName NOTIFY artistNameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant playParams READ playParams WRITE setPlayParams NOTIFY playParamsChanged)
    Q_PROPERTY(QVariant artwork READ artwork WRITE setArtwork NOTIFY artworkChanged)
    Q_PROPERTY(QString durationForDisplay READ durationForDisplay WRITE setDurationForDisplay NOTIFY durationForDisplayChanged)

public:
    explicit QmlSong(QObject *parent = nullptr);

    Q_INVOKABLE void initializeWithJsonObject(const QJsonObject &jsonObject);

    QVariant playParams() const;
    QString name() const;
    QString artistName() const;

    void setPlayParams(QVariant playParams);
    void setName(const QString &name);
    void setArtistName(const QString &artistName);

    QVariant artwork() const;

    QString durationForDisplay() const;

public slots:
    void setArtwork(QVariant artwork);

    void setDurationForDisplay(QString durationForDisplay);

signals:
    void playParamsChanged(QVariant playParams);
    void nameChanged(const QString &name);
    void artistNameChanged(const QString &artistName);
    void artworkChanged(QVariant artwork);

    void durationForDisplayChanged(QString durationForDisplay);

private:
    QVariant m_playParams;
    QString m_name;
    QString m_artistName;
    QVariant m_artwork;
    QString m_durationForDisplay;
};

/*
"attributes": {
"previews": [
{
"url": "https://audio-ssl.itunes.apple.com/apple-assets-us-std-000001/AudioPreview118/v4/32/71/06/32710628-e0d5-f876-c6d3-3137a564d0d4/mzaf_5288235235499953369.plus.aac.p.m4a"
}
],
"artwork": {
"width": 1800,
"height": 1800,
"url": "https://is2-ssl.mzstatic.com/image/thumb/Music118/v4/b1/b3/5a/b1b35a74-fa6e-e909-a2dd-61ff21631059/source/{w}x{h}bb.jpg",
"bgColor": "161616",
"textColor1": "e2c862",
"textColor2": "cdae46",
"textColor3": "b9a453",
"textColor4": "a88f3d"
},
"artistName": "Post Malone",
"url": "https://itunes.apple.com/us/album/rockstar-feat-21-savage/id1281165478?i=1281165480",
"discNumber": 1,
"genreNames": [
"Hip-Hop/Rap",
"Music"
],
"durationInMillis": 218293,
"releaseDate": "2017-09-15",
"name": "rockstar (feat. 21 Savage)",
"isrc": "USUM71710087",
"playParams": {
"id": "1281165480",
"kind": "song"
},
"trackNumber": 1,
"composerName": "Austin Post, Louis Bell, Olufunmibi Awoshiley & Shayaa Abraham-Joseph",
"contentRating": "explicit"
}
*/
