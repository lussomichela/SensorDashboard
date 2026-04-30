#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>
#include <QLocalSocket>

//main.c
#pragma pack(1)
struct SensorPayload {
    float temperature;
    float humidity;
    float pressure;
    float airQuality;
    float lightLevel;
};
#pragma pack()

class SensorModel : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(float humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(float pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(float airQuality READ airQuality NOTIFY airQualityChanged)
    Q_PROPERTY(float lightLevel READ lightLevel NOTIFY lightLevelChanged)

public:
    explicit SensorModel(QObject *parent = nullptr);
    float temperature() const { return m_temperature; }
    float humidity() const { return m_humidity; }
    float pressure() const { return m_pressure; }
    float airQuality() const { return m_airQuality; }
    float lightLevel() const { return m_lightLevel; }

    void updateTemperature(float newValue);
    void updateHumidity(float newValue);
    void updatePressure(float newValue);
    void updateairQuality(float newValue);
    void updatelightLevel(float newValue);

signals:
    void temperatureChanged();
    void humidityChanged();
    void pressureChanged();
    void airQualityChanged();
    void lightLevelChanged();

private slots:
    void onDataReceived();
    void handleSocketError(QLocalSocket::LocalSocketError error);

private:
    float m_temperature = 0.0;
    float m_humidity = 0.0;
    float m_pressure = 0.0;
    float m_airQuality = 0.0;
    float m_lightLevel = 0.0;

    QLocalSocket *m_socket;
};

#endif





