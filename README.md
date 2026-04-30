# SensorDashboard
Environmental Sensor Dashboard

```text
├── MQTT_Simulator/          # Python Hardware Simulation
│   ├── simulator.py         # Data generation logic
│   └── MqttGateway.py       # MQTT Gateway
├── qt_Dashboard/            # C++/QML Desktop Application
│   ├── CMakeLists.txt  
│   ├── IMessageBus.h        # Abstract Message Bus Interface
│   ├── main.cpp        
│   └── Main.qml             # Frontend UI definitions
│   ├── MqttMessageBus.h     # MQTT Implementation
│   ├── MqttMessageBus.cpp   
│   ├── SensorModel.cpp      # Sensor data management logic
│   ├── SensorModel.h
├── Simulator_Ubuntu/
│   ├── main.c
├── .gitignore               
└── README.md                # Project documentation
```
