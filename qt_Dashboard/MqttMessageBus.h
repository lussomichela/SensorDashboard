#ifndef MQTTMESSAGEBUS_H
#define MQTTMESSAGEBUS_H


#include <QObject>
#include <QtMqtt/QMqttClient>
#include "IMessageBus.h"

class MqttMessageBus : public QObject, public IMessageBus {

    Q_OBJECT

public:
    explicit MqttMessageBus(QObject *parent = nullptr);

    void connectToHost() override;
    void subscribe(const QString& topic) override;
    void onMessage(const QString& topic, const QByteArray& payload) override;

signals:
    void messageReceived(const QString &topic, const QByteArray &payload);


private:
    QMqttClient *m_client;
};


#endif // MQTTMESSAGEBUS_H
