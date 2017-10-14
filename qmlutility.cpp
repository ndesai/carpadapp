#include "qmlutility.h"
#include "basevisualcontainer.h"

#include <QQmlContext>
#include <QtQml>
#include <QFontDatabase>

#include <QtQml/private/qv4qobjectwrapper_p.h>
#include <QtQml/private/qv8engine_p.h>
#include <QtQml/private/qjsvalue_p.h>
#include <QtQml/private/qv4scopedvalue_p.h>
#include <QtQml/private/qqmlcontext_p.h>
#include <QtQml/private/qqmlboundsignal_p.h>

QmlUtility *QmlUtility::s_instance = nullptr;

QmlUtility::QmlUtility(QQmlEngine *qmlEngine, QObject *parent)
    : QObject(parent)
    , m_qmlEngine(qmlEngine)
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    , m_isDebugAllEnabled(false)
#else
    , m_isDebugAllEnabled(true)
#endif
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

QString QmlUtility::getQmlIdentifier(QObject *qmlItem)
{
    return "";
}

QJSValue QmlUtility::getQmlObjectById(const QString& id) {
    QV4::ExecutionEngine *v4 = QV8Engine::getV4(m_qmlEngine);
    QV4::Scope scope(const_cast<QV4::ExecutionEngine *>(v4));
    QV4::ScopedString name(scope, v4->newString(id));
    return QJSValue(v4, v4->currentContext->getProperty(name));
}


