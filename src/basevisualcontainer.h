#pragma once
#include <QQuickItem>
#include "qmlutility.h"
#include "logger.h"

class BaseVisualContainer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int debugFlags READ debugFlags WRITE setDebugFlags NOTIFY debugFlagsChanged)
public:
    friend class QmlUtility;
    explicit BaseVisualContainer(QQuickItem *parent = nullptr);
    static void registerTypes(const char *uri, QQmlEngine *engine);
    int debugFlags() const;

signals:
    void debugFlagsChanged(int debugFlags);

public slots:
    void setDebugFlags(int debugFlags);

private slots:
    void debugFlagsChangedHandler(int debugFlags);

private:
    int m_debugFlags;

};
