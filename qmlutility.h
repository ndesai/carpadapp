#pragma once

#include <QObject>
#include <QVariant>
#include <QQmlEngine>
#include <QFlags>
#include <QColor>

class QmlUtility : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlUtility)
    Q_PROPERTY(bool isDebugAllEnabled READ isDebugAllEnabled WRITE setIsDebugAllEnabled NOTIFY isDebugAllEnabledChanged)
public:
    explicit QmlUtility(QQmlEngine *qmlEngine, QObject *parent = nullptr);
    static void registerTypes(const char *uri, QQmlEngine *engine);
    Q_INVOKABLE void setGlobalProperty(const QString &key, const QVariant &value);
    void initializeGlobalProperties();

    /*! Singleton instance for both Qml and C++ */
    static QmlUtility *s_instance;

    /*! Standard singleton provider */
    static QmlUtility* instance(QQmlEngine *qmlEngine);

    /*! QML-based singleton provider */
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    /*! Retrieve a random color in hex value */
    Q_INVOKABLE QColor getRandomColor();

    /*! Test to retrieve the ID of a QML Object */
    Q_INVOKABLE QString getQmlIdentifier(QObject *qmlItem);

    Q_INVOKABLE QJSValue getQmlObjectById(const QString& id);

    enum DebugType {
        DebugTypeList = 1,
        DebugTypeListDelegate = 2,
        DebugTypeContainer = 4,
        DebugTypeImage = 8,
        DebugTypeText = 16
    };
    Q_ENUM(DebugType)
    Q_DECLARE_FLAGS(DebugTypes, DebugType)

    bool isDebugAllEnabled() const;

public slots:
    void setIsDebugAllEnabled(bool isDebugAllEnabled);

signals:
    void isDebugAllEnabledChanged(bool isDebugAllEnabled);

private:
    QQmlEngine *m_qmlEngine;
    bool m_isDebugAllEnabled;
};
Q_DECLARE_METATYPE(QmlUtility::DebugTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(QmlUtility::DebugTypes)
