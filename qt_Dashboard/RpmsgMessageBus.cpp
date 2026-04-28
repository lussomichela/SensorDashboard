#include "RpmsgMessageBus.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QByteArray>

RpmsgMessageBus::RpmsgMessageBus(QObject *parent) : IMessageBus(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
    double temp = QRandomGenerator::global()->bounded(double(20.0), double(30.0));
        qDebug() << "RPMsg Simulation: Sending internal data...";
        emit messageReceived("sensor/temperature", QString::number(temp, 'f', 2).toUtf8());
    });
    timer->start(2000);
}

void RpmsgMessageBus::connectToHost() {
    qDebug() << "RPMsg Simulated Bus connected";
}

void RpmsgMessageBus::subscribe(const QString& topic) {
    qDebug() << "RPMsg Subscribed to simulated topic:" << topic;
}

void RpmsgMessageBus::sendMessage(const QString &topic, const QString &payload) {
    qDebug() << "RPMsg Sending payload to M4 core:" << payload;
}