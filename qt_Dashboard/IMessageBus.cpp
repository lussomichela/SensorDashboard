#ifndef IMESSAGEBUS_H
#define IMESSAGEBUS_H

#include <QString>
#include <QByteArray>
class IMessageBus {
public:
    virtual void connect() = 0;
    virtual void subscribe(const QString& topic) = 0;
    virtual void onMessage(const QString& topic, const QByteArray& payload) = 0;
    virtual ~IMessageBus() = default;
};

#endif // IMESSAGEBUS_H
