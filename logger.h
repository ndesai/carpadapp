#pragma once

#include <QObject>
#include <QQmlEngine>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QQmlEngine *qmlEngine, QObject *parent = nullptr);

    /*! Singleton instance for both Qml and C++ */
    static Logger *s_instance;

    /*! Standard singleton provider */
    static Logger* instance(QQmlEngine *qmlEngine = nullptr);

    /*! QML-based singleton provider */
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    QQmlEngine *m_qmlEngine;
};
