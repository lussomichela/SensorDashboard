#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QFile>
#include <Qdebug>
#include <QSocketNotifier>


#pragma pack(1)
typedef struct {
    uint16_t speed;            /* 2 byte */
    uint16_t rpm;              /* 2 byte */
    uint8_t engine_fault;      /* 1 byte */
    uint8_t oil_temperature;   /* 1 byte */
} rpmsg_can_frame_t;
#pragma pack()

class Dashboard : public QObject {
    Q_OBJECT

    Q_PROPERTY(float speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(float rpm READ rpm NOTIFY rpmChanged)


public:
    explicit Dashboard(QObject *parent = nullptr);

    float speed() const { return m_speed; }
    float rpm() const { return m_rpm; }


private slots:
    void onDeviceReadyRead();

private:
    QFile* m_rpmsgDevice;
    QSocketNotifier* m_notifier;

    float m_speed = 0;
    float m_rpm = 0;

    void updatespeed(float v);
    void updaterpm(float v);


signals:
    void speedChanged();
    void rpmChanged();

};

#endif