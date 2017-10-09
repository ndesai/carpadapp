#include "qmlapplemusic.h"

#include <QtQml>

static const QString token = "eyJhbGciOiJFUzI1NiIsInR5cCI6IkpXVCIsImtpZCI6IkdYRjdHNTMyU0wifQ.eyJpc3MiOiJUSjVEOEc1TDVZIiwiaWF0IjoxNTA3NDgzMjEwLCJleHAiOjE1MDgwMDE2MTB9.8F_dIERqhmrZqUbcGDO3yfJLUUfbRetPOFm76q8EwRpv4tmQfRWyarUMWbC-YaMfeMY2TsIi4N3kLIqauiKk_g";
static const QString apiUrl = "https://api.music.apple.com/";
static const QString apiVersion = "v1";

QmlAppleMusic::QmlAppleMusic(QObject *parent)
    : QObject(parent)
    , m_networkAccessManager(new QNetworkAccessManager(this))
    , m_topSongsModel(nullptr)
{
    QObject::connect(m_networkAccessManager, &QNetworkAccessManager::finished,
                this, &QmlAppleMusic::replyReceived);

}

void QmlAppleMusic::registerTypes(const char *uri, QQmlEngine *engine)
{
    Q_UNUSED(engine)
    qmlRegisterType<QmlAppleMusic>(uri, 1, 0, "AppleMusic");
    qmlRegisterType<QmlTopSongsModel>(uri, 1, 0, "TopSongsModel");
    qmlRegisterUncreatableType<QmlSong>(uri, 1, 0, "QmlSong", "Not creatable");
}

void QmlAppleMusic::createRequest(const QString &url, const QJSValue &callback)
{
    if (url.isEmpty()) {
        qWarning() << "url is empty.";
        return;
    }

    QNetworkRequest request;
    request.setRawHeader("Authorization", ("Bearer " + token).toUtf8());

    QUrl compiledUrl = QUrl(apiUrl + "/" + apiVersion + "/" + url);
    request.setUrl(QUrl::fromEncoded(compiledUrl.toEncoded()));

    qDebug() << "requesting: " << request.url();

    if (callback.isCallable()) {
        m_callbackHash.insert(compiledUrl, callback);
    }

    m_networkAccessManager->get(request);
}

QmlTopSongsModel* QmlAppleMusic::topSongsModel() const
{
    return m_topSongsModel;
}

void QmlAppleMusic::setTopSongsModel(QmlTopSongsModel *topSongsModel)
{
    if (m_topSongsModel == topSongsModel)
        return;

    m_topSongsModel = topSongsModel;
    emit topSongsModelChanged(m_topSongsModel);
}

void QmlAppleMusic::replyReceived(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (!statusCode.isValid()) {
        return;
    }
    int status = statusCode.toInt();
    if (status != 200) {
        qWarning() << "statusCode: " << status;
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QJSValue callback = m_callbackHash.value(reply->url(), QJSValue());

        if (callback.isCallable()) {
    //        QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
    //        qDebug() << json;
            callback.call(QJSValueList() << QString::fromUtf8(reply->readAll()));
            m_callbackHash.remove(reply->url());
        } else {
            qWarning() << "callback is no good";
        }
    } else {
        qWarning() << "error: " << reply->error();
    }

}
