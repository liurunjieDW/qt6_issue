//qt6.5.1
import QtQuick
import QtQuick.Controls
import QtQuick3D
import Cpp2Qml
//qt5.15.9
//import QtQuick 2.15
//import QtQuick.Controls 2.15
//import QtQuick3D 1.15
//import Cpp2Qml 1.0

Item {
    id:root
    visible: true
    anchors.fill: parent

    MouseArea {
        width: root.width
        height: root.height
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
            console.log("clicked")
        }
        onPositionChanged: {
            var delat = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)

            //console.log("x:" + delat.x + "  y:" + delat.y)
            mainwindow.setX(mainwindow.x + delat.x)
            mainwindow.setY(mainwindow.y + delat.y)
        }
        onClicked: root.grabToImage(function(result) {
                            console.log(result.saveToFile("something.png"));
                        })
    }
    View3D {
        visible: true
        x: 0
        y: 0
        width: 640
        height: 480
        antialiasing: true

        Rectangle {
            visible: true
            x: 0
            y: 0
            width: 640
            height: 480
            border.color: "red"
            border.width: 1

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#FF090909"
                }
                GradientStop {
                    position: 0.7
                    color: "#10090909"
                }
                GradientStop {
                    position: 1.0
                    color: "#00090909"
                }
            }
        }
        environment: SceneEnvironment {
                antialiasingMode: SceneEnvironment.MSAA
                antialiasingQuality: SceneEnvironment.High
        }

        Node{
            DirectionalLight {
                color: "#e0e0e0"
                ambientColor: "#282828"
                brightness: 107
                x: perspectiveCamera.x
                y: perspectiveCamera.y
                z: perspectiveCamera.z
                eulerRotation: perspectiveCamera.eulerRotation
            }

            PerspectiveCamera {
                id: perspectiveCamera
                x: 0
                fieldOfView: 90
                eulerRotation.z: 0
                clipNear: 0.1
                clipFar: 110
                eulerRotation.y: 0
                z: 90
            }
            Text {
                objectName:"qmlnodetext"
                text: qsTr("helloCpp2Qml")
                font.pixelSize: 10
                color: "red"
                anchors.fill: parent
            }
        }
    }
}

