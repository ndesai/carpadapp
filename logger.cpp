#include "logger.h"

#include <QQmlContext>
#include <QtQml>

#include <QDebug>

Logger *Logger::s_instance = nullptr;

Logger::Logger(QQmlEngine *qmlEngine, QObject *parent)
    : QObject(parent)
    , m_qmlEngine(qmlEngine)
{

}

Logger *Logger::instance(QQmlEngine *qmlEngine) {
    if (!s_instance) {
        s_instance = new Logger(qmlEngine, QCoreApplication::instance());
    }
    return s_instance;
}

QObject *Logger::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return Logger::instance(engine);
}
