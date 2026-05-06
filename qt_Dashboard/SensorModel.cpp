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

    while (m_clientSocket->canReadLine()) {
        QByteArray line = m_clientSocket->readLine().trimmed();
        QString dataString = QString::fromUtf8(line);

        if (dataString.startsWith("DATA|")) {
            QStringList parts = dataString.split('|');

            if (parts.size() >= 6) {
                bool ok;
                float temp = parts[1].toFloat(&ok);
                float hum = parts[2].toFloat();
                float press = parts[3].toFloat();
                float air = parts[4].toFloat();
                float light = parts[5].toFloat();

                if (ok) {
                    qDebug() << "Parsed Values - Temp:" << temp << "Hum:" << hum;
                    updateTemperature(temp);
                    updateHumidity(hum);
                    updatePressure(press);
                    updateairQuality(air);
                    updatelightLevel(light);
                }
            }
        }
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

