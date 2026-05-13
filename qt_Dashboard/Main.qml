import QtQuick
import QtQuick.Controls

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Automotive Dashboard")
    color: "#000000"

    component Needle : Image {
        id: needleImage
        property real value: 0
        property real minValue: 0
        property real maxValue: 100
        property real startAngle: -140
        property real endAngle: 140

        fillMode: Image.PreserveAspectFit
        antialiasing: true
        smooth: true

        rotation: {
            let ratio = (Math.max(minValue, Math.min(maxValue, value)) - minValue) / (maxValue - minValue);
            return startAngle + (ratio * (endAngle - startAngle));
        }

        transformOrigin: Item.Center

        Behavior on rotation {
            SpringAnimation {
                spring: 2.5
                damping: 0.7
                mass: 1.0
            }
        }
    }

    // dashboard
    Image {
        id: dashboardBase
        source: "Dashboard2.png"
        anchors.centerIn: parent
        width: parent.width * 0.95
        fillMode: Image.PreserveAspectFit

        // rpm
        Item {
            id: rpm
            x: parent.width * 0.146
            y: parent.height * 0.680
            width: 1; height: 1

            Needle {
                id: rpmNeedle
                source: "needle_red.png"
                height: dashboardBase.height / 3.4
                anchors.centerIn: parent

                minValue: 0
                maxValue: 80
                value: backend.rpm
            }
        }

        // speed
        Item {
            id: speed
            x: parent.width * 0.763
            y: parent.height * 0.680
            width: 1; height: 1

            Needle {
                id: speedNeedle
                source: "needle_white.png"
                height: dashboardBase.height / 3.4
                anchors.centerIn: parent

                minValue: 0
                maxValue: 240
                value: backend.speed
            }
        }
    }
}