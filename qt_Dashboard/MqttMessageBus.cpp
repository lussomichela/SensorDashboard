#include "MqttMessageBus.h"
#include <QtMqtt/QMqttClient>

MqttMessageBus::MqttMessageBus(QObject *parent) : QObject(parent) {
    m_client = new QMqttClient(this);
    m_client->setHostname("localhost");
    m_client->setPort(1883);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray& message, const QMqttTopicName& topic) {
        emit messageReceived(topic.name(), message);
    });
}

void MqttMessageBus::connectToHost() {
    connect(m_client, &QMqttClient::connected, this, [this]() {
        qDebug() << "MQTT connected";

        m_client->subscribe(QLatin1String("sensor/temperature"));
        m_client->subscribe(QLatin1String("sensor/humidity"));
        m_client->subscribe(QLatin1String("sensor/pressure"));
        m_client->subscribe(QLatin1String("sensor/airQuality"));
        m_client->subscribe(QLatin1String("sensor/lightLevel"));
    });
     m_client->connectToHost();
}


void MqttMessageBus::subscribe(const QString& topic) {
    m_client->subscribe(topic);
}


void MqttMessageBus:: onMessage(const QString& topic, const QByteArray& payload){
    Q_UNUSED(payload);
    Q_UNUSED(topic);

}