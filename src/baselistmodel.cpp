#include <QMetaProperty>
#include <QDebug>
#include "baselistmodel.h"

BaseListModel::BaseListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QVariant BaseListModel::data(const QModelIndex &index, int role) const
{
    QObject *item = m_itemList.at(index.row());
    return item->property(item->metaObject()->property(role).name());
}

/*
 * Returns the number of items attached to the list.
 */
int BaseListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_itemList.size();
}

/*
 * Generates a hash out of QMetaObject property-index and property-name.
 */
QHash<int, QByteArray> BaseListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    if (!m_itemList.isEmpty()) {
        for(int i = 0; i < m_itemList.at(0)->metaObject()->propertyCount(); i++) {
            roles[i] = m_itemList.at(0)->metaObject()->property(i).name();
        }
    }

    return roles;
}

/*
 * Append Item to List.
 */
void BaseListModel::appendItem(QObject *item)
{
    /* map the notify()-signal-index with the property-index when the first item get's inserted */
    if (m_itemList.isEmpty()) {
        for(int i = 0; i < item->metaObject()->propertyCount(); i++) {
            m_propertySignalIndexHash.insert(item->metaObject()->property(i).notifySignalIndex(), i);
        }
    }

    /* connect each notify()-signals to the onDataChanged()-slot which call's the dataChanged()-signal */
    for(int i = 0; i < item->metaObject()->propertyCount(); i++) {
        connect(item, "2" + item->metaObject()->property(i).notifySignal().methodSignature(), this, SLOT(onDataChanged()));
    }

    /* finally append the item the list */
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_itemList.append(item);
    endInsertRows();
}

/*
 * Helper-Slot that emit's the dataChanged()-signal of QAbstractListModel.
 */
void BaseListModel::onDataChanged()
{
    QModelIndex index = createIndex(m_itemList.indexOf(sender()),0);

    QVector<int> roles;
    roles.append(m_propertySignalIndexHash.value(senderSignalIndex()));
    emit dataChanged(index, index, roles);
}
