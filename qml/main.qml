import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Machines 1.0

ApplicationWindow {
    id: root

    width: 640
    height: 480
    visible: true

    minimumWidth: 410
    minimumHeight: 200

    title: qsTr("Sensors_List")

    background: Rectangle{
        color: "#cacaca"
    }

    ListView{
        id: view
        spacing: 5
        clip: true
        anchors {
            margins: 5
            bottom: testBtn.top
            top: parent.top
            left: parent.left
            right: parent.right
        }

        model: myModel

        delegate: MachineDelegate{}
    }

    RoundButton{
        id: testBtn
        text: qsTr("Random Signal (Test)")
        Material.background:  Material.DeepPurple
        Material.foreground: "White"
        width: 400
        anchors{
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: {
            let index = Math.round(Math.random() * ((view.model.rowCount()-1) - 0));
            view.positionViewAtIndex(index,ListView.Contain)

            let role =  Math.round(Math.random() * (259 - 258) + 258);

            let value = 0;
            if(role === 259)
                value = Number(Math.random() * (100 - 0)).toFixed(2);
            else
                value = Math.round(Math.random() * (2 - 0));

            myModel.setDataByIndex(index,value,role)
            console.log(index,value,role)
        }
    }

    Connections{
        target: myModel

        function onStateChanged(index,newState){
            view.currentIndex = index

            let st;
            if(newState === 0)
                 st = "warning"
            else if(newState === 1)
                st = "nominal"
            else st = "error"

            view.currentItem.stateLight.state = st
        }

        function onStrengthChanged(index,newStrength){
            view.currentIndex = index
            view.currentItem.signalStrngthTxt.text = Number(newStrength).toFixed(2) +" %"
        }
    }
}
