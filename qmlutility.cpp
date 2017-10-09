#include "qmlutility.h"
#include "basevisualcontainer.h"

#include <QQmlContext>
#include <QtQml>
#include <QFontDatabase>

QmlUtility *QmlUtility::s_instance = nullptr;

QmlUtility::QmlUtility(QQmlEngine *qmlEngine, QObject *parent)
    : QObject(parent)
    , m_qmlEngine(qmlEngine)
    , m_isDebugAllEnabled(true)
{
    qDebug() << "Fonts:\n" << QFontDatabase().families();
}

QmlUtility *QmlUtility::instance(QQmlEngine *qmlEngine) {
    if (!s_instance) {
        s_instance = new QmlUtility(qmlEngine, QCoreApplication::instance());
    }
    return s_instance;
}

QObject *QmlUtility::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return QmlUtility::instance(engine);
}

bool QmlUtility::isDebugAllEnabled() const
{
    return m_isDebugAllEnabled;
}

void QmlUtility::setIsDebugAllEnabled(bool isDebugAllEnabled)
{
    if (m_isDebugAllEnabled == isDebugAllEnabled)
        return;

    m_isDebugAllEnabled = isDebugAllEnabled;
    emit isDebugAllEnabledChanged(m_isDebugAllEnabled);
}

void QmlUtility::registerTypes(const char *uri, QQmlEngine *engine)
{
    qmlRegisterSingletonType<QmlUtility>(uri, 1, 0, "Utility", &QmlUtility::qmlInstance);
    BaseVisualContainer::registerTypes(uri, engine);
}

void QmlUtility::setGlobalProperty(const QString &key, const QVariant &value)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(m_qmlEngine != nullptr);

    m_qmlEngine->rootContext()->setContextProperty(key, value);
}

void QmlUtility::initializeGlobalProperties()
{
    this->setGlobalProperty("__debug", false);
}

QColor QmlUtility::getRandomColor()
{
    float currentHue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return QColor::fromHslF(std::fmod(currentHue, 1.0f), 1.0, 0.5);
}

