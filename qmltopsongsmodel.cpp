#include "qmltopsongsmodel.h"

QmlTopSongsModel::QmlTopSongsModel(QObject *parent)
    : GenericListModel<QmlSong>(parent)
{

}

void QmlTopSongsModel::initializeWithJson(const QString &jsonString)
{
    QJsonDocument json = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = json.object();
    QJsonObject jsonResultsObject = jsonObject.value(QStringLiteral("results")).toObject();
    QJsonArray jsonArraySongs = jsonResultsObject.value("songs").toArray();
    QJsonArray jsonArrayData = (jsonArraySongs.at(0)).toObject().value("data").toArray();

    foreach (const QJsonValue &value, jsonArrayData) {
        QJsonObject obj = value.toObject();

        QmlSong *song = new QmlSong(this);
        song->initializeWithJsonObject(obj);

        qDebug() << "append: " << song->name();

        this->append(song);
    }

    qDebug() << "initialize: " << jsonArrayData;
}

