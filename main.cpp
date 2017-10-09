#include <QGuiApplication>
#include <QQmlApplicationEngine>

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

    return app.exec();
}
