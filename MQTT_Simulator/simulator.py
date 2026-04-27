import paho.mqtt.client as mqtt
import time
import random

client = mqtt.Client(callback_api_version=mqtt.CallbackAPIVersion.VERSION2)
client.connect("localhost", 1883)

while True:
    temperature = round(random.uniform(-50.0, 50.0), 1)
    humidity= round(random.uniform(0.0 ,100.0),1)
    pressure= round(random.uniform(900 ,1200),1)
    airQuality= round(random.uniform(0 ,500),1)
    lightLevel= round(random.uniform(0 ,100),1)

    client.publish("sensor/temperature", temperature )
    client.publish("sensor/humidity", humidity  )
    client.publish("sensor/pressure", pressure  )
    client.publish("sensor/airQuality", airQuality  )
    client.publish("sensor/lightLevel", lightLevel )
    print(f"Sensor Dashboard: \nTemperature: {temperature} °C \nHumidity: {humidity} % \nPressure: {pressure} hPa \nAirquality: {airQuality} AQI \nLightLevel: {lightLevel} lux \n")
    time.sleep(3)

