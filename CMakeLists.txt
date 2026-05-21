cmake_minimum_required(VERSION 3.16)

project(SensorDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    Qml
    QuickControls2
    Network
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSensorDashboard
    LedModel.h
    LedModel.cpp
    SpeedometerModel.h
    SpeedometerModel.cpp
    main.cpp
)

qt_add_qml_module(appSensorDashboard
    URI SensorDashboard
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        Dashboard3.png
        Dashboard4.png
        needle_red.png
        needle_white.png
        led_oil_on_r.png
        led_oil_off_r.png
        led_engine_off_r.png
        led_engine_on_r.png
        SOURCES RPMsg.cpp
        SOURCES RPMsg.h
)

set_target_properties(appSensorDashboard PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSensorDashboard
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::Network
)

install(TARGETS appSensorDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
