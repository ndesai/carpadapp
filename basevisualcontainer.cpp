#include "basevisualcontainer.h"

BaseVisualContainer::BaseVisualContainer(QQuickItem *parent)
    : QQuickItem(parent)
{
    connect(this, &BaseVisualContainer::debugFlagsChanged,
            this, &BaseVisualContainer::debugFlagsChangedHandler);
}

void BaseVisualContainer::registerTypes(const char *uri, QQmlEngine *engine)
{
    Q_UNUSED(engine)
    qmlRegisterType<BaseVisualContainer>(uri, 1, 0, "BaseVisualContainer");
}

int BaseVisualContainer::debugFlags() const
{
    return m_debugFlags;
}

void BaseVisualContainer::setDebugFlags(int debugFlags)
{
    if (m_debugFlags == debugFlags) {
        return;
    }

    m_debugFlags = debugFlags;
    emit debugFlagsChanged(m_debugFlags);
}

void BaseVisualContainer::debugFlagsChangedHandler(int debugFlags)
{
    QmlUtility::DebugTypes flag = static_cast<QmlUtility::DebugTypes>(debugFlags);
    if (flag.testFlag(QmlUtility::DebugTypeContainer)) {
        qDebug() << "DebugTypeContainer.....";
    }
}
