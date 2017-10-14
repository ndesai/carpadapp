#include "qmlsong.h"

#include <QDateTime>

QmlSong::QmlSong(QObject *parent)
    : QObject(parent)
{

}

void QmlSong::initializeWithJsonObject(const QJsonObject &jsonObject)
{
    QJsonObject attributes =  jsonObject.value("attributes").toObject();
    setArtistName(attributes.value("artistName").toString());
    setName(attributes.value("name").toString());
    setPlayParams(attributes.value("playParams").toVariant());
    setArtwork(attributes.value("artwork").toVariant());

    int durationInMillis = attributes.value("durationInMillis").toInt();
    qDebug() << "durationInMillis:" << durationInMillis;
    int mm = (durationInMillis / 1000) / 60;
    int ss = (durationInMillis / 1000) % 60;
    QString ssString = QString::number(ss);
    if (ss < 10) {
        ssString.prepend("0");
    }
    setDurationForDisplay(QString::number(mm) + ":" + ssString);
}

QVariant QmlSong::playParams() const
{
    return m_playParams;
}

QString QmlSong::name() const
{
    return m_name;
}

QString QmlSong::artistName() const
{
    return m_artistName;
}

void QmlSong::setPlayParams(QVariant playParams)
{
    if (m_playParams == playParams)
        return;

    m_playParams = playParams;
    emit playParamsChanged(m_playParams);
}

void QmlSong::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void QmlSong::setArtistName(const QString &artistName)
{
    if (m_artistName == artistName)
        return;

    m_artistName = artistName;
    emit artistNameChanged(m_artistName);
}

QVariant QmlSong::artwork() const
{
    return m_artwork;
}

QString QmlSong::durationForDisplay() const
{
    return m_durationForDisplay;
}

void QmlSong::setArtwork(QVariant artwork)
{
    if (m_artwork == artwork)
        return;

    m_artwork = artwork;
    emit artworkChanged(m_artwork);
}

void QmlSong::setDurationForDisplay(QString durationForDisplay)
{
    if (m_durationForDisplay == durationForDisplay)
        return;

    m_durationForDisplay = durationForDisplay;
    emit durationForDisplayChanged(m_durationForDisplay);
}

QDebug operator<<(QDebug debug, const QmlSong &s)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << s.name() << " by " << s.artistName();

    return debug;
}
