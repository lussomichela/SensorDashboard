# SensorDashboard
Environmental Sensor Dashboard


├── MQTT_Simulator/          # Python Hardware Simulation
│   ├── simulator.py         # Data generation logic
│   └── MqttGateway.py       # MQTT Gateway
├── qt_Dashboard/            # C++/QML Desktop Application
│   ├── CMakeLists.txt  
│   ├── IMessageBus.cpp        
│   ├── IMessageBus.h        # Abstract Message Bus Interface
│   ├── main.cpp        
│   └── Main.qml             # Frontend UI definitions
│   ├── MqttMessageBus.h     # MQTT Implementation
│   ├── MqttMessageBus.cpp   
│   ├── RpmsgMessageBus.h   
│   ├── SensorModel.cpp      # Sensor data management logic
│   ├── SensorModel.h
├── .gitignore               
└── README.md                # Project documentation
