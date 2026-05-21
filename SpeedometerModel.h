#ifndef SPEEDOMETERMODEL_H
#define SPEEDOMETERMODEL_H
#include "RPMsg.h"
#define USE_SIMULATOR true

class SpeedometerModel : public RPMsg {
    Q_OBJECT

    Q_PROPERTY(float speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(float rpm READ rpm NOTIFY rpmChanged)


public:
    explicit SpeedometerModel(QObject *parent = nullptr);

    float speed() const { return m_speed; }
    float rpm() const { return m_rpm; }
    void update_data(const rpmsg_can_frame_t &structure);


private:

    float m_speed = 0;
    float m_rpm = 0;

    void updatespeed(float v);
    void updaterpm(float v);


signals:
    void speedChanged();
    void rpmChanged();


};

#endif
