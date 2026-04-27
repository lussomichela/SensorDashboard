from paho.mqtt import client as mqtt_client
from PySide6.QtCore import QObject, Property, Signal, Slot


class MqttSensorGateway (QObject):

    temperatureChanged = Signal()
    humidityChanged = Signal()
    pressureChanged = Signal()
    airQualityChanged = Signal()
    lightLevelChanged = Signal()

    def __init__(self):
        super().__init__()

        self._temperature = 0.0
        self._humidity = 0.0
        self._pressure = 0
        self._airQuality = 0
        self._lightLevel = 0

    def get_temperature(self):
        return self._temperature

    def get_humidity(self):
        return self._humidity

    def get_pressure(self):
        return self._pressure

    def get_airQuality(self):
        return self._airQuality

    def get_lightLevel(self):
        return self._lightLevel

    def set_temperature(self, value):
        if (self._temperature != value):
            self._temperature = value
            self.temperatureChanged.emit()

    def set_humidity(self, value):
        if (self._humidity != value):
            self._humidity = value
            self.humidityChanged.emit()

    def set_pressure(self, value):
        if (self._pressure != value):
            self._pressure= value
            self.pressureChanged.emit()

    def set_airQuality(self, value):
        if (self._airQuality != value):
            self._airQuality = value
            self.airQualityChanged.emit()

    def set_lightLevel(self, value):
        if (self._lightLevel != value):
            self._lightLevel = value
            self.lightLevelChanged.emit()


    temperature = Property(float, get_temperature, set_temperature, notify=temperatureChanged)
    humidity = Property(float, get_humidity, set_humidity, notify=humidityChanged)
    pressure = Property(float, get_pressure, set_pressure, notify=pressureChanged)
    airQuality = Property(float, get_airQuality, set_airQuality, notify=airQualityChanged)
    lightLevel = Property(float, get_lightLevel, set_lightLevel, notify=lightLevelChanged)


bridge = MqttSensorGateway()

# MQTT message
def on_message(client, userdata, message):
    message_received = float(message.payload.decode("utf-8"))
    topic = message.topic

    if topic == "sensor/temperature":
        bridge.set_temperature(message_received)
    elif topic == "sensor/humidity":
        bridge.set_humidity(message_received)
    elif topic == "sensor/pressure":
        bridge.set_pressure(message_received)
    elif topic == "sensor/airQuality":
        bridge.set_airQuality(message_received)
    elif topic == "sensor/lightLevel":
        bridge.set_lightLevel(message_received)


client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION2)
client._on_message = on_message
client.connect("localhost", 1883)

client.loop_start()
client.subscribe("sensor/temperature")
client.subscribe("sensor/humidity")
client.subscribe("sensor/pressure")
client.subscribe("sensor/airQuality")
client.subscribe("sensor/lightLevel")
