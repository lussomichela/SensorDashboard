#ifndef RPMSGMESSAGEBUS_H
#define RPMSGMESSAGEBUS_H



#include <QObject>
#include "IMessageBus.h"
#include <QDebug>

class RpmsgMessageBus : public QObject, public IMessageBus {
    Q_OBJECT

public:
    explicit RpmsgMessageBus(QObject *parent = nullptr) : QObject(parent) { }

    void connectToHost() override {
        qDebug() << "RPMsg Bus";
    }

    void subscribe(const QString& topic) override{
        qDebug() << "RPMsg Bus";
    }

    void onMessage(const QString& topic, const QByteArray& payload) override {}


signals:
    void messageReceived(const QString& topic, const QByteArray& payload);
};

#endif // RPMSGMESSAGEBUS_H
