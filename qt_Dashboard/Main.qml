import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes


Window {
    id: window
    width: 1000
    height: 850
    visible: true
    title: qsTr("Sensor Dashboard")
    color: "#f8f8ff" //ghostwhite

    property int gaugeSize: 220
    property color needleColor: "#000000" // black
    property color colorLow: "#3366FF"   // blue
    property color colorMid: "#008000"   // green
    property color colorHigh: "#FF0000"  // red


    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        // first row
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 40

            // TEMPERATURE
            Rectangle {
                width: gaugeSize; height: gaugeSize; radius: width / 2
                color: "#f5f5f5"; //whitesmoke
                border.color: "#808080"; border.width: 4

                Shape {
                    anchors.fill: parent; anchors.margins: 15; antialiasing: true
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorLow; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95;  //Defines the center of the arc
                            radiusX: 85; radiusY: 85;  //Defines the radii of the ellipse of which the arc is part
                            startAngle: -225;          //Defines the start angle of the arc
                            sweepAngle: (30/70)*270 }} //Defines the sweep angle of the arc
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorMid; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95;
                            radiusX: 85; radiusY: 85;
                            startAngle: -225 + (30/70)*270; sweepAngle: (20/70)*270 }}
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorHigh; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95;
                            radiusX: 85; radiusY: 85;
                            startAngle: -225 + (50/70)*270; sweepAngle: (20/70)*270 }}
                }

                Repeater {
                    model: 8
                    Item {
                        anchors.fill: parent; rotation:  index* (270/7) - 135
                        Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter;
                            y: 14; width: 2; height: 15; color: "#000000"
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter;
                            y: 34; text: (index*10)-20; color: "#000000";
                            font.pixelSize: 11; font.bold: true; rotation: -parent.rotation
                        }
                    }
                }

                Item {
                    anchors.fill: parent;
                    rotation: (backend.temperature + 20) * (270/70) - 135
                    Behavior on rotation {
                        SpringAnimation {
                            spring: 2.5; damping: 0.5
                        }
                    }
                    Rectangle {
                        width: 3; height: 85; color: needleColor;
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.verticalCenter; antialiasing: true
                    }
                }

                Rectangle {
                    anchors.centerIn: parent;
                    width: 14; height: 14; radius: 7; color: "#000000"
                }

                Column {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 50; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Text {
                        text: "TEMPERATURE"; font.pixelSize: 11; font.bold: true;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        color: backend.temperature > 30 ? colorHigh : (backend.temperature < 10 ? colorLow : colorMid)
                    }
                    Text {
                        text: backend.temperature.toFixed(1) + " °C";
                        font.pixelSize: 15; font.bold: true;
                        anchors.horizontalCenter: parent.horizontalCenter; color: parent.children[0].color
                    }
                }
            }

            // HUMIDITY
            Rectangle {
                width: gaugeSize; height: gaugeSize; radius: width / 2
                color: "#f5f5f5"; border.color: "#808080"; border.width: 4

                Shape {
                    anchors.fill: parent; anchors.margins: 15; antialiasing: true
                    ShapePath { fillColor: "transparent"; strokeColor: colorLow; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225; sweepAngle: (30/100)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorMid; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (30/100)*270; sweepAngle: (30/100)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorHigh; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (60/100)*270; sweepAngle: (40/100)*270 }}
                }

                Repeater {
                    model: 11
                    Item {
                        anchors.fill: parent; rotation: index * (270/10) - 135
                        Rectangle { anchors.horizontalCenter: parent.horizontalCenter; y: 14; width: 2; height: 15; color: "#000000" }
                        Text { anchors.horizontalCenter: parent.horizontalCenter; y: 34; text: index*10; color: "#000000"; font.pixelSize: 11; font.bold: true; rotation: -parent.rotation }
                    }
                }

                Item {
                    anchors.fill: parent; rotation: (backend.humidity * (270/100)) - 135
                    Behavior on rotation { SpringAnimation { spring: 2.5; damping: 0.5 } }
                    Rectangle { width: 3; height: 85; color: needleColor; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.verticalCenter; antialiasing: true }
                }

                Rectangle { anchors.centerIn: parent; width: 14; height: 14; radius: 7; color: "#000000" }

                Column {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 50; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Text { text: "HUMIDITY"; font.pixelSize: 11; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: backend.humidity > 60 ? colorHigh : (backend.humidity < 30 ? colorLow : colorMid) }
                    Text { text: backend.humidity.toFixed(0) + " %"; font.pixelSize: 15; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: parent.children[0].color }
                }
            }
        }

        // Second row
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 25

            // PRESSURE
            Rectangle {
                width: gaugeSize; height: gaugeSize; radius: width/2
                color: "#f5f5f5"; border.color: "#808080"; border.width: 4

                Shape {
                    anchors.fill: parent; anchors.margins: 15; antialiasing: true
                    ShapePath { fillColor: "transparent"; strokeColor: colorLow; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225; sweepAngle: (100/300)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorMid; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (100/300)*270; sweepAngle: (100/300)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorHigh; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (200/300)*270; sweepAngle: (100/300)*270 }}
                }

                Repeater {
                    model: 7
                    Item {
                        anchors.fill: parent; rotation: index * (270/6) - 135
                        Rectangle { anchors.horizontalCenter: parent.horizontalCenter; y: 14; width: 2; height: 15; color: "#000000" }
                        Text { anchors.horizontalCenter: parent.horizontalCenter; y: 35; text: 900+(index*50); color: "#000000"; font.pixelSize: 10; font.bold: true; rotation: -parent.rotation }
                    }
                }

                Item {
                    anchors.fill: parent; rotation: (backend.pressure - 900) * (270/300) - 135
                    Behavior on rotation { SpringAnimation { spring: 2.5; damping: 0.5 } }
                    Rectangle { width: 3; height: 85; color: needleColor; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.verticalCenter }
                }

                Rectangle { anchors.centerIn: parent; width: 14; height: 14; radius: 7; color: "#000000" }

                Column {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 50; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Text { text: "PRESSURE"; font.pixelSize: 11; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: backend.pressure > 1100 ? colorHigh : (backend.pressure < 1000 ? colorLow : colorMid) }
                    Text { text: backend.pressure.toFixed(0) + " hPa"; font.pixelSize: 15; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: parent.children[0].color }
                }
            }

            // AIR QUALITY
            Rectangle {
                width: gaugeSize; height: gaugeSize; radius: width/2
                color: "#f5f5f5"; border.color: "#808080"; border.width: 4

                Shape {
                    anchors.fill: parent; anchors.margins: 15; antialiasing: true
                    ShapePath { fillColor: "transparent"; strokeColor: colorLow; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225; sweepAngle: (100/500)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorMid; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (100/500)*270; sweepAngle: (200/500)*270 }}
                    ShapePath { fillColor: "transparent"; strokeColor: colorHigh; strokeWidth: 10
                        PathAngleArc { centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (300/500)*270; sweepAngle: (200/500)*270 }}
                }

                Repeater {
                    model: 6
                    Item {
                        anchors.fill: parent; rotation: index * (270/5) - 135
                        Rectangle { anchors.horizontalCenter: parent.horizontalCenter; y: 14; width: 2; height: 15; color: "#000000" }
                        Text { anchors.horizontalCenter: parent.horizontalCenter; y: 34; text: index*100; color: "#000000"; font.pixelSize: 11; font.bold: true; rotation: -parent.rotation }
                    }
                }

                Item {
                    anchors.fill: parent; rotation: (backend.airQuality * (270/500)) - 135
                    Behavior on rotation { SpringAnimation { spring: 2.5; damping: 0.5 } }
                    Rectangle { width: 3; height: 85; color: needleColor; anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.verticalCenter }
                }

                Rectangle { anchors.centerIn: parent; width: 14; height: 14; radius: 7; color: "#000000" }

                Column {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 50; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Text { text: "AIR QUALITY"; font.pixelSize: 11; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: backend.airQuality > 300 ? colorHigh : (backend.airQuality < 100 ? colorLow : colorMid) }
                    Text { text: backend.airQuality.toFixed(0) + " AQI"; font.pixelSize: 15; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; color: parent.children[0].color }
                }
            }

            // LIGHT LEVEL
            Rectangle {
                width: gaugeSize; height: gaugeSize; radius: width/2
                color: "#f5f5f5"; border.color: "#808080"; border.width: 4

                Shape {
                    anchors.fill: parent; anchors.margins: 15; antialiasing: true
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorLow; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225; sweepAngle: (3000/10000)*270 }}
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorMid; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (30/100)*270; sweepAngle: (4000/10000)*270 }}
                    ShapePath {
                        fillColor: "transparent"; strokeColor: colorHigh; strokeWidth: 10
                        PathAngleArc {
                            centerX: 95; centerY: 95; radiusX: 85; radiusY: 85; startAngle: -225 + (70/100)*270; sweepAngle: (3000/10000)*270 }}
                }

                Repeater {
                    model: 11
                    Item {
                        anchors.fill: parent; rotation: index * (270/10) - 135
                        Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter; y: 14; width: 2; height: 15; color: "#000000"
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter; y: 34; text: index*1000; color: "#000000";
                            font.pixelSize: 11; font.bold: true; rotation: -parent.rotation
                        }
                    }
                }

                Item {
                    anchors.fill: parent; rotation: (backend.lightLevel * (270/10000)) - 135
                    Behavior on rotation {
                        SpringAnimation {
                            spring: 2.5; damping: 0.5
                        }
                    }
                    Rectangle {
                        width: 3; height: 85; color: needleColor;
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.verticalCenter
                    }
                }

                Rectangle {
                    anchors.centerIn: parent;
                    width: 14; height: 14; radius: 7; color: "#000000"
                }

                Column {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 50; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Text {
                        text: "LIGHT LEVEL"; font.pixelSize: 11; font.bold: true;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        color: backend.lightLevel > 7000 ? colorHigh : (backend.lightLevel < 3000 ? colorLow : colorMid)
                    }
                    Text {
                        text: backend.lightLevel.toFixed(0) + " lux"; font.pixelSize: 15; font.bold: true;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        color: parent.children[0].color
                    }
                }
            }
        }
    }
}