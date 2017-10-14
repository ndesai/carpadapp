#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQuickWindow>

#include "qmlapplemusic.h"
#include "qmlutility.h"
#include "basevisualcontainer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const char *uri = "app.st";
    QmlAppleMusic::registerTypes(uri, &engine);
    QmlUtility::registerTypes(uri, &engine);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

//    QQuickWindow *qWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));

//    Q_ASSERT(qWindow != nullptr);

//    QSurfaceFormat format = qWindow->format();
//    format.setSamples(16);
//    qWindow->setFormat(format);

    return app.exec();
}
