#ifndef SENSORMODEL_H
#define SENSORMODEL_H


#include <QObject>
#include <QDebug>
#include <QQmlEngine>



class SensorModel : public QObject
{

    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(float humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(int pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(float airQuality READ airQuality NOTIFY airQualityChanged)
    Q_PROPERTY(float lightLevel READ lightLevel NOTIFY lightLevelChanged)

    public:
    explicit SensorModel(QObject *parent = nullptr);
    float temperature() const {return m_temperature; }
    float humidity() const {return m_humidity; }
    int pressure() const {return m_pressure; }
    int airQuality() const {return m_airQuality; }
    int lightLevel() const {return m_lightLevel; }

    void updateTemperature( float newValue);
    void updateHumidity( float newValue);
    void updatePressure( float newValue);
    void updateairQuality( float newValue);
    void updatelightLevel( float newValue);


    void onMessageReceived(const QString& topic, const QByteArray& message);

signals:
    void temperatureChanged();
    void humidityChanged();
    void pressureChanged();
    void airQualityChanged();
    void lightLevelChanged();

private:
    float m_temperature;
    float m_humidity;
    float m_pressure;
    float m_airQuality;
    float m_lightLevel;

};





#endif //SENSORMODEL_H
