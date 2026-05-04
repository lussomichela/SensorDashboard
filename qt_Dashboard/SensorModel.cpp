#include "SensorModel.h"
#include <QTimer>

SensorModel::SensorModel(QObject *parent) : QObject(parent) {
    m_tcpServer = new QTcpServer(this);
    m_clientSocket = nullptr;

    if (!m_tcpServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server Error:" << m_tcpServer->errorString();
    } else {
        qDebug() << "Listening on port 1234...";
    }

    connect(m_tcpServer, &QTcpServer::newConnection, this, [this]() {
        m_clientSocket = m_tcpServer->nextPendingConnection();
        qDebug() << ">>> Bridge Connected";

        connect(m_clientSocket, &QTcpSocket::readyRead, this, &SensorModel::onDataReceived);

        connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]() {
            qDebug() << ">>> Bridge Disconnected";
            m_clientSocket->deleteLater();
            m_clientSocket = nullptr;
        });
    });
}

void SensorModel::onDataReceived() {
    if (!m_clientSocket) return;

    while (m_clientSocket->bytesAvailable() >= sizeof(SensorPayload)) {
        QByteArray data = m_clientSocket->read(sizeof(SensorPayload));
        const SensorPayload* payload = reinterpret_cast<const SensorPayload*>(data.constData());

        qDebug() << "VRING Received:";
        qDebug() << "Temperature:" << payload->temperature;
        qDebug() << "Humidity:" << payload->humidity;
        qDebug() << "Pressure:" << payload->pressure;
        qDebug() << "AirQuality:" << payload->airQuality;
        qDebug() << "LightLevel:" << payload->lightLevel;

        updateTemperature(payload->temperature);
        updateHumidity(payload->humidity);
        updatePressure(payload->pressure);
        updateairQuality(payload->airQuality);
        updatelightLevel(payload->lightLevel);
    }
}

void SensorModel::updateTemperature(float newValue) {
    if (m_temperature != newValue) {
        m_temperature = newValue;
        emit temperatureChanged();
    }
}

void SensorModel::updateHumidity(float newValue) {
    if (m_humidity != newValue) {
        m_humidity = newValue;
        emit humidityChanged();
    }
}

void SensorModel::updatePressure(float newValue) {
    if (m_pressure != newValue) {
        m_pressure = newValue;
        emit pressureChanged();
    }
}

void SensorModel::updateairQuality(float newValue) {
    if (m_airQuality != newValue) {
        m_airQuality = newValue;
        emit airQualityChanged();
    }
}

void SensorModel::updatelightLevel(float newValue) {
    if (m_lightLevel != newValue) {
        m_lightLevel = newValue;
        emit lightLevelChanged();
    }
}