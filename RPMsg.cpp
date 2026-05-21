
#include "RPMsg.h"
#include "SpeedometerModel.h"
#include "LedModel.h"



RPMsg::RPMsg(QObject *parent) : QObject(parent) {

    m_rpmsgDevice = new QFile("/dev/rpmsg0",this );  /* open the rpmsg created on linux */

    // Open in read-only, non-blocking, unbuffered mode
    if(!m_rpmsgDevice->open(QIODevice::ReadOnly | QIODevice::Unbuffered)){ /* allows reading */
        qDebug() << " Error opening RPMsg device " << m_rpmsgDevice->errorString(); /* provides details */
    }else {
        qDebug() << "Connected to /dev/rpmsg0 ";
    }

    int fd = m_rpmsgDevice->handle(); /* File Descriptor */
    if (fd == -1) {
        qCritical() << "Failed to get file descriptor for device";
        m_rpmsgDevice -> close();

        return;
    }else{

        /* QSocketNotifier monitor the file descriptor /dev/rpmsg0 for readability.
     When the condition you're watching for happens, it emits the activated() signal.
     - parent the notifier: set "this" as the parent to auto-delete the notifier when the parent (QObject subclass) is destroyed */
        m_notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);

        /* Connect QSocketNotifier::activated(int fd) to a slot that reads data from the device */
        connect(m_notifier, &QSocketNotifier::activated, this, &RPMsg::ReadyRead);


    }


}



void RPMsg:: ReadyRead() {
    QByteArray buffer = m_rpmsgDevice->readAll();
    int frameSize = sizeof(rpmsg_can_frame_t);

    while (buffer.size() >= frameSize) {
        const rpmsg_can_frame_t *structure = reinterpret_cast<const rpmsg_can_frame_t*>(buffer.constData());

        emit frameReceived(*structure);

        buffer.remove(0, frameSize);
    }
}

