#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#pragma pack(1)
typedef struct {
    float temperature;
    float humidity;
    float pressure;
    float airQuality;
    float lightLevel;
} SensorPayload;
#pragma pack()

class SensorModel : public QObject {
    Q_OBJECT

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

private slots:
    void onDataReceived();

private:
    QTcpServer* m_tcpServer;
    QTcpSocket* m_clientSocket;

    float m_temperature = 0;
    float m_humidity = 0;
    float m_pressure = 0;
    float m_airQuality = 0;
    float m_lightLevel = 0;

    void updateTemperature(float v);
    void updateHumidity(float v);
    void updatePressure(float v);
    void updateairQuality(float v);
    void updatelightLevel(float v);

signals:
    void temperatureChanged();
    void humidityChanged();
    void pressureChanged();
    void airQualityChanged();
    void lightLevelChanged();
};

#endif