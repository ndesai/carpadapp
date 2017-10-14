#pragma once

#include <QObject>
#include <QtNetwork>
#include <QJSValue>
#include "qmltopsongsmodel.h"

class QQmlEngine;
class QmlAppleMusic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QmlTopSongsModel* topSongsModel READ topSongsModel WRITE setTopSongsModel NOTIFY topSongsModelChanged)

public:
    explicit QmlAppleMusic(QObject *parent = nullptr);
    static void registerTypes(const char *uri, QQmlEngine *engine);
    Q_INVOKABLE void createRequest(const QString &url, const QJSValue &callback = QJSValue());
    QmlTopSongsModel* topSongsModel() const;

signals:
    void topSongsModelChanged(QmlTopSongsModel *topSongsModel);

public slots:
    void setTopSongsModel(QmlTopSongsModel *topSongsModel);

private slots:
    void replyReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkAccessManager;
    QHash<const QUrl, QJSValue> m_callbackHash;

    QmlTopSongsModel *m_topSongsModel;
};
