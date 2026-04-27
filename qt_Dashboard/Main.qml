import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Sensor Dashboard")

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30


        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 40



            Rectangle {
                id: temperature
                width: 100; height: 100; radius: width/2


                gradient: Gradient {
                    GradientStop {
                        position: 0.0;
                        color:{
                            if(backend.temperature > 30) return "#FF0000"   //light red
                            if(backend.temperature < 10) return "#0000FF" //light blue
                            return "#008000" //green
                        }


                        Behavior on color {
                            ColorAnimation { duration: 500}
                        }

                    }

                    GradientStop {
                        position: 1.0;
                        color:{
                            if(backend.temperature > 30) return "#8b0000"   //dark red
                            if(backend.temperature < 10) return "#00008b" //dark blue
                            return "#006400" //darkgreen
                        }

                        Behavior on color {
                            ColorAnimation {duration: 1000}
                        }
                    }
                }

                border.color: "white"
                border.width: 2


                Column {
                    anchors.centerIn: parent
                    spacing: 5

                    Text {
                        text: "Temperature"
                        color: "white"
                        font.pixelSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter
                        }

                    Text {
                        text: backend.temperature.toFixed(1) + " °C"
                        color: "white"
                        font.pixelSize: 20
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        }
                }
            }


            Rectangle {
                id: humidity
                width: 100; height: 100; radius: width/2


                gradient: Gradient {
                    GradientStop {
                        position: 0.0;
                        color:{
                            if(backend.humidity > 60) return "#FF0000"   //light red
                            if(backend.humidity < 30) return "#0000FF" //light blue
                            return "#008000" //green
                        }


                        Behavior on color {
                            ColorAnimation { duration: 500}
                        }

                    }

                    GradientStop {
                        position: 1.0;
                        color:{
                            if(backend.humidity > 60) return "#8b0000"   //dark red
                            if(backend.humidity < 30) return "#00008b" //dark blue
                            return "#006400" //darkgreen
                        }

                        Behavior on color {
                            ColorAnimation {duration: 1000}
                        }
                    }
                }

                border.color: "white"
                border.width: 2


                Column {
                    anchors.centerIn: parent
                    spacing: 5

                    Text {
                        text: "Humidity"
                        color: "white"
                        font.pixelSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter
                        }

                    Text {
                        text: backend.humidity.toFixed(1) + " %"
                        color: "white"
                        font.pixelSize: 20
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        }
                }
            }



        }



        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 40


        Rectangle {
            id: pressure
            width: 100; height: 100; radius: width/2


            gradient: Gradient {
                GradientStop {
                    position: 0.0;
                    color:{
                        if(backend.pressure > 1020) return "#FF0000"   //light red
                        if(backend.pressure < 1000) return "#0000FF" //light blue
                        return "#008000" //green
                    }


                    Behavior on color {
                        ColorAnimation { duration: 500}
                    }

                }

                GradientStop {
                    position: 1.0;
                    color:{
                        if(backend.pressure > 1020) return "#8b0000"   //dark red
                        if(backend.pressure < 1000) return "#00008b" //dark blue
                        return "#006400" //darkgreen
                    }

                    Behavior on color {
                        ColorAnimation {duration: 1000}
                    }
                }
            }

            border.color: "white"
            border.width: 2


            Column {
                anchors.centerIn: parent
                spacing: 5

                Text {
                    text: "Pressure"
                    color: "white"
                    font.pixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    text: backend.pressure + " hPa"
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    }
            }
        }


        Rectangle {
            id: airQuality
            width: 100; height: 100; radius: width/2


            gradient: Gradient {
                GradientStop {
                    position: 0.0;
                    color:{
                        if(backend.airQuality > 300) return "#FF0000"   //light red
                        if(backend.airQuality < 100) return "#0000FF" //light blue
                        return "#008000" //green
                    }


                    Behavior on color {
                        ColorAnimation { duration: 500}
                    }

                }

                GradientStop {
                    position: 1.0;
                    color:{
                        if(backend.airQuality > 300) return "#8b0000"   //dark red
                        if(backend.airQuality < 100) return "#00008b" //dark blue
                        return "#006400" //darkgreen
                    }

                    Behavior on color {
                        ColorAnimation {duration: 1000}
                    }
                }
            }

            border.color: "white"
            border.width: 2


            Column {
                anchors.centerIn: parent
                spacing: 5

                Text {
                    text: "Air Quality"
                    color: "white"
                    font.pixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    text: backend.airQuality + " AQI"
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    }
            }
        }


        Rectangle {
            id: lightLevel
            width: 100; height: 100; radius: width/2


            gradient: Gradient {
                GradientStop {
                    position: 0.0;
                    color:{
                        if(backend.lightLevel > 800) return "#FF0000"   //light red
                        if(backend.lightLevel < 300) return "#0000FF" //light blue
                        return "#008000" //green
                    }


                    Behavior on color {
                        ColorAnimation { duration: 500}
                    }

                }

                GradientStop {
                    position: 1.0;
                    color:{
                        if(backend.lightLevel > 800) return "#8b0000"   //dark red
                        if(backend.lightLevel < 300) return "#00008b" //dark blue
                        return "#006400" //darkgreen
                    }

                    Behavior on color {
                        ColorAnimation {duration: 1000}
                    }
                }
            }

            border.color: "white"
            border.width: 2


            Column {
                anchors.centerIn: parent
                spacing: 5

                Text {
                    text: "Light Level"
                    color: "white"
                    font.pixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    text: backend.lightLevel + " lux"
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    }
            }
        }


        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                inputPanel.y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            NumberAnimation {
                properties: "y"
                easing.type: Easing.InOutQuad
            }
        }
    }
}
