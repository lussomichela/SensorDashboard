import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 1280
    height: 900
    visible: true
    title: qsTr("Dashboard")
    color: "#000000"

    component GaugeWidget : Item {
        id: root
        property real value: 0
        property real min: 0
        property real max: 100
        property string title: ""
        property string unit: ""

        property var tickAngles: [-132, -92, -52, -16, 16, 52, 92, 132]

        property real distance: 110

        function getAngle(val) {
            let clampedVal = Math.max(root.min, Math.min(root.max, val));
            let ratio = (clampedVal - root.min) / (root.max - root.min);
            let start = tickAngles[0];
            let end = tickAngles[tickAngles.length - 1];
            return start + (ratio * (end - start));
        }

        width: 320; height: 320

        Image {
            id: bg
            source: "Gauge.png"
            anchors.fill: parent
            smooth: true
        }

        // NUMERICAL SCALE
        Repeater {
            model: root.tickAngles.length
            Item {
                anchors.fill: parent
                rotation: root.tickAngles[index]
                Text {
                    text: Math.round(root.min + (index * (root.max - root.min) / (root.tickAngles.length - 1)))
                    color: "white"
                    font.pixelSize: 18
                    font.bold: true
                    antialiasing: true

                    anchors.horizontalCenter: parent.horizontalCenter
                    y: parent.height / 2 - root.distance
                    rotation: -parent.rotation
                }
            }
        }

        // NEEDLE
        Image {
            id: needle
            source: "gauge_needle.png"
            height: parent.height * 0.46
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            antialiasing: true

            transform: Rotation {
                origin.x: needle.width / 2
                origin.y: needle.height
                angle: root.getAngle(root.value)

                Behavior on angle {
                    SpringAnimation { spring: 2.2; damping: 0.6; mass: 1.0 }
                }
            }
        }


        Rectangle {
            width: 58; height: 58; radius: 29
            color: "#111111"; border.color: "#222222"; border.width: 2
            anchors.centerIn: parent
        }

        // TITLES AND UNITS
        Column {
            anchors.bottom: parent.bottom; anchors.bottomMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: root.title; color: "#777777";
                font.pixelSize: 10; font.bold: true; font.letterSpacing: 2;
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                text: root.unit; color: "#ff8c00";
                font.pixelSize: 15; font.bold: true;
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // LAYOUT
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 40

        // FIRST ROW
        RowLayout {
            spacing: 30
            Layout.alignment: Qt.AlignHCenter

            GaugeWidget {
                title: "TEMPERATURE"; unit: "°C"; min: -20; max: 50
                value: backend.temperature
            }
            GaugeWidget {
                title: "HUMIDITY"; unit: "%"; min: 30; max: 100
                value: backend.humidity
            }
            GaugeWidget {
                title: "PRESSURE"; unit: "HPA"; min: 900; max: 1250
                value: backend.pressure
            }
        }

        // SECOND ROW
        RowLayout {
            spacing: 30
            Layout.alignment: Qt.AlignHCenter

            GaugeWidget {
                title: "AIR QUALITY"; unit: "AQI"; min: 0; max: 700
                value: backend.airQuality
            }
            GaugeWidget {
                title: "LIGHT LEVEL"; unit: "LUX"; min: 0; max: 7000
                value: backend.lightLevel
            }
        }
    }
}


