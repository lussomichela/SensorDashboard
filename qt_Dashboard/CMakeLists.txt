cmake_minimum_required(VERSION 3.16)

project(SensorDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6Mqtt_DIR "C:/Qt/6.11.0/mingw_64/lib/cmake/Qt6Mqtt")
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS
    Mqtt
    WebSockets
    Quick
    Core
    Gui
    Qml
    QuickControls2
    Core5Compat
)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appSensorDashboard
    main.cpp
    Main.qml
)

qt_add_qml_module(appSensorDashboard
    URI SensorDashboard
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        IMessageBus.h
        MqttMessageBus.h
        MqttMessageBus.cpp

        SensorModel.h
        SensorModel.cpp
)

target_include_directories(appSensorDashboard PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    "C:/Qt/6.11.0/mingw_64/include"
    "C:/Qt/6.11.0/mingw_64/include/QtMqtt"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSensorDashboard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSensorDashboard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSensorDashboard
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::WebSockets
    Qt6::Mqtt
    Qt6::Core5Compat
)


install(TARGETS appSensorDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
