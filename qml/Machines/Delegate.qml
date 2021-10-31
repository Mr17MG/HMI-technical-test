import QtQuick 2.15
import QtQuick.Controls.Material 2.15

Component {
    Item{
        property alias signalStrngthTxt: signalStrngthTxt
        property alias stateLight: stateLight

        width: view.width
        height: 50
        Rectangle{
            width: Math.max(400,parent.width/3*2)
            height: parent.height
            color: Qt.darker(stateLight.color,1.7)
            radius: 10

            anchors{
                horizontalCenter: parent.horizontalCenter
            }

            Item{
                id: lightItem
                width: 30
                height: parent.height
                anchors{
                    left: parent.left
                    leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                Rectangle{
                    id: stateLight
                    width: 10
                    height: width
                    radius: width

                    anchors{
                        centerIn: parent
                    }

                    state:{
                        if(model.state === 0)
                            return "warning"
                        else if(model.state === 1)
                            return "nominal"
                        else return "error"
                    }
                    Behavior on state {
                        SequentialAnimation{
                            PropertyAnimation{
                                target: stateLight
                                property: "width"
                                from: 10
                                to: 30
                                duration: 200
                            }
                            PropertyAnimation{
                                target: stateLight
                                property: "width"
                                from: 30
                                to: 10
                                duration: 200
                            }

                        }
                    }

                    states: [
                        State{
                            name: "warning"
                            PropertyChanges { target: stateLight; color: Material.color(Material.Yellow,Material.ShadeA700) }
                        },
                        State{
                            name: "nominal"
                            PropertyChanges { target: stateLight; color: Material.color(Material.Green,Material.ShadeA700) }
                        },
                        State{
                            name: "error"
                            PropertyChanges { target: stateLight; color: Material.color(Material.Red,Material.ShadeA700) }
                        }
                    ]
                }
            }

            Text{
                text: "["+(String(model.typeName).toUpperCase()??"")+"] - " + (model.name??"")
                color: "white"
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors{
                    left: lightItem.right
                    leftMargin: 5
                    right: signalStrngthTxt.left
                    rightMargin: 5
                }
            }

            Text{
                id: signalStrngthTxt
                text: model.strength+" %"
                color: "white"
                width: 30
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors{
                    right: parent.right
                    rightMargin: 15
                }
                font{
                    pixelSize: 14
                }

                Behavior on text {
                    SequentialAnimation{
                        ParallelAnimation{
                            PropertyAnimation{
                                target: signalStrngthTxt
                                property: "font.bold"
                                from: false
                                to: true
                                duration: 0
                            }
                            PropertyAnimation{
                                target: signalStrngthTxt
                                property: "font.pixelSize"
                                from: 14
                                to: 20
                                duration: 200
                            }
                        }
                        ParallelAnimation{
                            PropertyAnimation{
                                target: signalStrngthTxt
                                property: "font.bold"
                                from: true
                                to: false
                                duration: 0
                            }
                            PropertyAnimation{
                                target: signalStrngthTxt
                                property: "font.pixelSize"
                                from: 20
                                to: 14
                                duration: 200
                            }
                        }
                    }
                }
            }
        }
    }
}
