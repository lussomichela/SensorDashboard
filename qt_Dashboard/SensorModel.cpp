#include "SensorModel.h"

SensorModel::SensorModel(QObject *parent) : QObject(parent) {
    // Inizialization
    m_temperature = 25.0f;
    m_humidity = 45.0f;
    m_pressure = 1000.0f;
    m_airQuality = 50.0f;
    m_lightLevel = 500.0f;
}

void SensorModel::onMessageReceived(const QString& topic, const QByteArray& message) {
    bool ok;
    float value = message.toFloat(&ok);

    if (!ok) return;

    if (topic == "sensor/temperature") {
        updateTemperature(value);
    } else if (topic == "sensor/humidity") {
        updateHumidity(value);
    } else if (topic == "sensor/pressure") {
        updatePressure(value);
    } else if (topic == "sensor/airQuality") {
        updateairQuality(value);
    } else if (topic == "sensor/lightLevel") {
        updatelightLevel(value);
    }
}





void SensorModel::updateTemperature(float newValue) {
    //Range: -50 +50 °C
    if (newValue < -50.0f || newValue > 50.0f) return;

    if (m_temperature != newValue) {
        m_temperature = newValue;
        emit temperatureChanged();
    }
}

void SensorModel::updateHumidity(float newValue) {
    //Range: 0 100 %
    if (newValue < 0.0f || newValue > 100.0f) return;

    if (m_humidity != newValue) {
        m_humidity = newValue;
        emit humidityChanged();
    }
}

void SensorModel::updatePressure(float newValue) {
    // Range: 900 - 1200 hPa
    if (newValue < 900.0f || newValue > 1200.0f) return;

    if (m_pressure != newValue) {
        m_pressure = newValue;
        emit pressureChanged();
    }
}

void SensorModel::updateairQuality(float newValue) {
    // Range: 0 - 500 AQI
    if (newValue < 0.0f || newValue > 500.0f) return;

    if (m_airQuality != newValue) {
        m_airQuality = newValue;
        emit airQualityChanged();
    }
}

void SensorModel::updatelightLevel(float newValue) {
    // Range: 0 - 1000 lux
    if (newValue < 0.0f || newValue > 10000.0f) return;

    if (m_lightLevel != newValue) {
        m_lightLevel = newValue;
        emit lightLevelChanged();
    }
}



