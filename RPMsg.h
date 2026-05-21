#ifndef RPMSG_H
#define RPMSG_H

#include <QObject>
#include <QFile>           /* For file operation */
#include <QTextStream>     /* For text streaming */
#include <QDebug>          /* For debugging messages */
#include <QSocketNotifier> /* To monitor the fd for readability */

/*For data simulator*/
#include <QTimer>
#include <QRandomGenerator>


/**
 * @struct rpmsg_can_frame_t
 * @brief Structure representing the CAN data frame received via RPMSG.
 *
 * This structure is packed to ensure exact memory mapping when reading
 * raw bytes from the character device.
 */
#pragma pack(1)
typedef struct {
    uint16_t speed;            /* 2 byte */
    uint16_t rpm;              /* 2 byte */
    uint8_t engine_fault;      /* 1 byte */
    uint8_t oil_temperature;   /* 1 byte */
} rpmsg_can_frame_t;
#pragma pack()




class RPMsg : public QObject {
    Q_OBJECT


public:
    explicit RPMsg(QObject *parent = nullptr);
    QFile* m_rpmsgDevice;

private:
    QSocketNotifier* m_notifier;
    void ReadyRead();

signals:
    void frameReceived(const rpmsg_can_frame_t &frame);

};



#endif // RPMSG_H
