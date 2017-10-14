#pragma once

#include <QAbstractListModel>
#include <QHash>

class BaseListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BaseListModel(QObject *parent);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

protected:
    void appendItem(QObject *item);
    QList<QObject *> m_itemList;

private Q_SLOTS:
    void onDataChanged();

private:
    QHash<int, int> m_propertySignalIndexHash;
};

template <typename T>
class GenericListModel : public BaseListModel
{
public:
    explicit GenericListModel(QObject *parent)
        : BaseListModel(parent)
    {

    }

    void append(T *item)
    {
        appendItem(item);
    }

    T *at(int i)
    {
        return qobject_cast<T *>(m_itemList.at(i));
    }
};
