#include "SensorModel.h"
#include <QTimer>



SensorModel::SensorModel(QObject *parent) : QObject(parent) {
    m_socket = new QLocalSocket(this);

    connect(m_socket, &QLocalSocket::connected, this, [this]() {
        qDebug() << ">>> Connected ";
        m_socket->write("\x01", 1);
        m_socket->flush();
        m_socket->waitForBytesWritten(500);

    });

    connect(m_socket, &QLocalSocket::readyRead, this, &SensorModel::onDataReceived);
    connect(m_socket, &QLocalSocket::errorOccurred, this, [this](QLocalSocket::LocalSocketError error) {
        qDebug() << ">>> Pipe State:" << m_socket->errorString();

        QTimer::singleShot(2000, this, [this]() {
            if (m_socket->state() == QLocalSocket::UnconnectedState) {
                m_socket->connectToServer("\\\\.\\pipe\\rpmsg_pipe");
            }
        });
    });

    m_socket->connectToServer("\\\\.\\pipe\\rpmsg_pipe");
}


void SensorModel::onDataReceived() {

    while (m_socket->bytesAvailable() >= sizeof(SensorPayload)) {
        QByteArray data = m_socket->read(sizeof(SensorPayload));
        const SensorPayload* payload = reinterpret_cast<const SensorPayload*>(data.constData());


        qDebug() << "VRING: ";
        qDebug() << "Temperature:" << payload->temperature;
        qDebug() << "Humidity: " << payload->humidity;
        qDebug() << "Pressure: " << payload->pressure;
        qDebug() << "airQuality: " << payload->airQuality;
        qDebug() << "lightLevel: " << payload->lightLevel;



        updateTemperature(payload->temperature);
        updateHumidity(payload->humidity);
        updatePressure(payload->pressure);
        updateairQuality(payload->airQuality);
        updatelightLevel(payload->lightLevel);
    }
}

void SensorModel::handleSocketError(QLocalSocket::LocalSocketError error) {
    qDebug() << "IPC Socket Error:" << m_socket->errorString();
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