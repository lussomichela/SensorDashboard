#include "SensorModel.h"
#include <QFile>       /* For file operation */
#include <QTextStream> /* For text streaming */
#include <Qdebug>      /* for debugging messages */
#include <QSocketNotifier>


Dashboard::Dashboard(QObject *parent) : QObject(parent) {
    m_rpmsgDevice = new QFile("/dev/rpmsg0",this );  /* open the rpmsg created on linux */

    if(!m_rpmsgDevice->open(QIODevice::ReadOnly)){ /* allows reading */
        qDebug() << " Error opening RPMsg device " << m_rpmsgDevice->errorString(); /* provides details */
    }else {
        qDebug() << "Connected to /dev/rpmsg0 ";
    }

    /* QSocketNotifier monitor the file descriptor /dev/rpmsg0 for readability.
     When the condition you're watching for happens, it emits the activated() signal.
     - parent the notifier: set "this" as the parent to auto-delete the notifier when the parent (QObject subclass) is destroyed */
    m_notifier = new QSocketNotifier(m_rpmsgDevice->handle(), QSocketNotifier::Read, this);

    /* Connect QSocketNotifier::activated(int fd) to a slot that reads data from the device */
    connect(m_notifier, &QSocketNotifier::activated, this, &Dashboard::onDeviceReadyRead);

}

/* In the slot, read data form the device using readAll() */
void Dashboard::onDeviceReadyRead() {

    /* Read the payload available on the file descriptor's queue (6 bytes buffer) */
    QByteArray buffer = m_rpmsgDevice->readAll();

    if (buffer.size() < (int)sizeof(rpmsg_can_frame_t)){

        const rpmsg_can_frame_t *data = reinterpret_cast<const rpmsg_can_frame_t*>(buffer.constData());

        /* Update the values */
        updatespeed(data ->speed);
        updaterpm (data -> rpm);

        qDebug() << "Data received | Speed:" << data->speed << "rpm:" <<data->rpm ;
    }
}



void Dashboard::updatespeed(float newValue) {
    if (m_speed != newValue) {
        m_speed = newValue;
        emit speedChanged();
    }
}

void Dashboard::updaterpm(float newValue) {
    if (m_rpm != newValue) {
        m_rpm = newValue;
        emit rpmChanged();
    }
}


