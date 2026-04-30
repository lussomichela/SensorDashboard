#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SensorModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    static SensorModel sensorBackend;

    engine.rootContext()->setContextProperty("backend", &sensorBackend);

    const QUrl url("qrc:/qt/qml/SensorDashboard/Main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}