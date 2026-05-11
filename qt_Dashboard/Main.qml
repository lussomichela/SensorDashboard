import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Automotive Dashboard")
    color: "#000000"

    //Component
    component GaugeWidget : Item {
        id: root
        property real value: 0
        property real min: 0
        property real max: 100
        property string title: ""
        property string unit: ""
        property string dialSource: ""

        width: 350; height: 350


        Image{
            id: dialImage
            source:root.dialSource
            anchors.fill: parent
            smooth: true
            antialiasing: true
            fillMode: Image.PreserveAspectFit
        }

        //angle for the needle
        function getAngle(val) {
            let startAngle = -140; // start angle
            let endAngle = 140;    // end
            let clampedVal = Math.max(root.min, Math.min(root.max, val));
            let ratio = (clampedVal - root.min) / (root.max - root.min);
            return startAngle + (ratio * (endAngle - startAngle));
        }


        // NEEDLE
         Image {
            id: needle
            source: "gauge_needle.png"
            height: parent.height * 0.45
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            antialiasing: true

            transformOrigin: Item.Bottom

            rotation: root.getAngle(root.value)

            Behavior on rotation {
                SpringAnimation {
                    spring: 2.5;
                    damping: 0.7;
                    mass: 1.0
                }
            }
        }

        Rectangle {
            width: 40; height: 40; radius: 20
            color: "#111111"
            border.color: "#333333"
            border.width: 2
            anchors.centerIn: parent
        }

        // TITLE
        /*Column {
            anchors.bottom: parent.bottom; anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 2

            Text {
                text: root.title
                color: "#AAAAAA"
                font.pixelSize: 14; font.bold: true; font.letterSpacing: 2
                anchors.horizontalCenter: parent.horizontalCenter
            }

        }*/
    }

    //DASHBOARD
     Row {
        anchors.centerIn: parent
        spacing: 80

        GaugeWidget {
            //title: "RPM"
            min: 0
            max: 8
            dialSource: "gauge_rpm.png"
            value: backend.rpm
        }

        GaugeWidget {
            //title: "SPEED"
            min: 0
            max: 260
            dialSource: "gauge_speed.png"
            value: backend.speed
        }



    }
}