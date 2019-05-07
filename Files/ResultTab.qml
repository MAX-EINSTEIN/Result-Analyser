import QtQuick 2.5
import QtQuick.Controls 2.5

Item {

    id:rootItem
    Text {
        id: headingText
        color: "#7035e4"
        text: qsTr("Choose the layout you require for the results")
        font.family: "Monotype Corsiva"
        font.bold: true
        font.pointSize: 20
    }

    Rectangle {
        id: layout1
        x: 40
        y: 40
        width:500
        height: 220
        radius: 16
        border.width: 1
        Item {
            x:12
            y:10
            id: pages
            Rectangle{
                id:page1
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page2
                x:162
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page3
                x:325
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
        }
    }

    Rectangle {
        id: layout2
        x: 600
        y: 40
        width: 500
        height: 220
        radius: 16
        border.width: 1
        Item {
            x:12
            y:10
            id: pages1
            Rectangle{
                id:page21
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page22
                x:162
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page23
                x:325
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
        }
    }

    Rectangle {
        id: layout3
        x: 40
        y: 300
        width:500
        height: 220
        radius: 16
        border.width: 1
        Item {
            x:12
            y:10
            id: pages3
            Rectangle{
                id:page31
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page32
                x:162
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page33
                x:325
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
        }
    }

    Rectangle {
        id: layout4
        x: 600
        y: 300
        width: 500
        height: 220
        radius: 16
        border.width: 1
        Item {
            x:12
            y:10
            id: pages4
            Rectangle{
                id:page41
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page42
                x:162
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
            Rectangle{
                id:page43
                x:325
                width: 150
                height: 200
                radius: 16
                border.width: 1
            }
        }
    }

}



/*##^## Designer {
    D{i:0;autoSize:true;height:600;width:1200}
}
 ##^##*/
