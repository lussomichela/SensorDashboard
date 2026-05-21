#include "RPMsg.h"
#include "SpeedometerModel.h"



SpeedometerModel::SpeedometerModel(QObject *parent) : RPMsg(parent) {

    /*--------------------------Data simulator--------------------------*/
    if (USE_SIMULATOR) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            float randomSpeed = QRandomGenerator::global()->bounded(0, 240);
            float randomRpm = QRandomGenerator::global()->bounded(0, 80);

            updatespeed(randomSpeed);
            updaterpm(randomRpm);
        });
        timer->start(3000);
    }
    /*---------------------------------------------------------------------*/
}


void SpeedometerModel::update_data(const rpmsg_can_frame_t &structure) {

    if (USE_SIMULATOR) return;

    updatespeed(structure.speed);
    updaterpm(structure.rpm);

    qDebug() << "Data received | Speed:" << structure.speed << "rpm:" << structure.rpm;
}

void SpeedometerModel::updatespeed(float newValue) {
    if (m_speed != newValue) {
        m_speed = newValue;
        emit speedChanged();
    }
}

void SpeedometerModel::updaterpm(float newValue) {
    if (m_rpm != newValue) {
        m_rpm = newValue;
        emit rpmChanged();
    }
}


