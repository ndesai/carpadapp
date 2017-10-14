#pragma once

#include <QObject>
#include "baselistmodel.h"
#include <QJsonDocument>
#include <QJsonArray>

#include "qmlsong.h"

class QmlTopSongsModel : public GenericListModel<QmlSong>
{
    Q_OBJECT
public:
    explicit QmlTopSongsModel(QObject *parent = nullptr);

    Q_INVOKABLE void initializeWithJson(const QString &jsonString);
};
