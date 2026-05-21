#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SpeedometerModel.h"
#include "LedModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    SpeedometerModel *speedometerBackend = new SpeedometerModel(&app);
    LedModel *ledBackend = new LedModel(&app);

    QObject::connect(speedometerBackend, &RPMsg::frameReceived, speedometerBackend, &SpeedometerModel::update_data);
    QObject::connect(speedometerBackend, &RPMsg::frameReceived, ledBackend, &LedModel::update_data);


    engine.rootContext()->setContextProperty("backend", speedometerBackend);
    engine.rootContext()->setContextProperty("messageBus", ledBackend);

    const QUrl url("qrc:/qt/qml/SensorDashboard/Main.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}

