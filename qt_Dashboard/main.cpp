#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QtQml/qqml.h>
#include <QQmlContext>
#include <QtQmlIntegration/qqmlintegration.h>
#include <QtQml/qqmlregistration.h>
#include <SensorModel.h>
#include <MqttMessageBus.h>

using namespace Qt::StringLiterals;




int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    SensorModel sensorBackend;
    MqttMessageBus mqttBus;

    QObject::connect(&mqttBus, &MqttMessageBus::messageReceived,
                     &sensorBackend, &SensorModel::onMessageReceived);

    mqttBus.connectToHost();


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &sensorBackend);


    const QUrl url(u"qrc:/YourProjectName/main.qml"_s);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SensorDashboard", "Main");


    return QCoreApplication::exec();
}

