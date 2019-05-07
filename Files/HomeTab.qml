import QtQuick 2.5
import QtQuick.Controls 2.5

Item{
    id: item
    Rectangle {
        id: rectangle
        color: "#ffffff"
        width: 1800
        height: 120

        Image {
            id: icon
            source: "qrc:/img/Images/Icons/MainView_Icon.png"
            width: 680
            height: 600
            opacity: 0.68
            x:480
            y:0
        }

        Text {
            id: text
            color: "#8512ea"
            font.bold: true
            styleColor: "#8330db"
            style: Text.Raised
            text: "Result Analyser"
            font.family: "Monotype Corsiva"
            font.pointSize: 75
        }

        Text {
            id: bulletList1
            color: "#000033"

            Text{
                x:10
                y:160
                font.pointSize: 18
                text: "     Create detailed and elaborate results \n\n"
                Image {
                    id: createtext
                    source: "qrc:/img/Images/Icons/home.png"
                    width: 40
                    height: 30
                }
                Text {
                    x:50
                    id: openExcelfile
                    text: qsTr("\n\n\n\n       Open Excel File")
                    Image {
                        x:-5
                        y:50
                        id: openFile
                        source: "qrc:/img/Images/Icons/open.png"
                        width: 25
                        height: 20
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: MainView.openFile()
                    }
                }

                Text {
                    x:50
                    y:30
                    id: printResult
                    text: qsTr("\n\n\n\n       Print Result")
                    Image {
                        x:-5
                        y:50
                        id: printR
                        source: "qrc:/img/Images/Icons/print.png"
                        width: 22
                        height: 20
                    }
                    MouseArea{
                        anchors.topMargin: 30
                        anchors.fill: parent;
                        onClicked: MainView.print()
                    }
                }

                Text {
                    x:50
                    y:60
                    id: logintext
                    text: qsTr("\n\n\n\n       Login")
                    Image {
                        x:-5
                        y:50
                        id: loginimg
                        source: "qrc:/img/Images/Icons/login.png"
                        width: 22
                        height: 20
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: MainView.logIn()
                    }
                }

                Text {
                    x:50
                    y:90
                    id: logouttext
                    text: qsTr("\n\n\n\n       Logout")
                    Image {
                        x:-5
                        y:50
                        id: logoutimg
                        source: "qrc:/img/Images/Icons/logout.png"
                        width: 22
                        height: 20
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: MainView.logOut()
                    }
                }

                Text {
                    x:50
                    y:120
                    id: settingstext
                    text: qsTr("\n\n\n\n       Open Settings")
                    Image {
                        x:-5
                        y:50
                        id: settingsimg
                        source: "qrc:/img/Images/Icons/settings.png"
                        width: 22
                        height: 20
                    }
                    MouseArea{
                        anchors.topMargin: 50
                        anchors.fill: parent;
                        onClicked: MainView.openSettings()
                    }
                }
            }



        }// bulleltlist1 ends

        Text {
            id: bulletList2
            color: "#000033"

            Text{
                x:10
                y:400
                font.pointSize: 18
                text: "     View performance report of the class\n\n"
                Image {
                    id: performance
                    source: "qrc:/img/Images/Icons/Report_Card_Icon.png"
                    width: 40
                    height: 30
                }
                Text {
                    x:50
                    id: viewPerformance
                    text: qsTr("\n\n\n\n       View Performance Report")
                    Image {
                        x:-5
                        y:50
                        id: viewPerformanceimg
                        source: "qrc:/img/Images/Icons/MainView_Icon.png"
                        width: 25
                        height: 20
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: MainView.visitPerformanceReport()
                    }
                }

                Text {
                    x:50
                    y:40
                    id: printtext
                    text: qsTr("\n\n\n\n       Print Performance Report")
                    Image {
                        x:-5
                        y:50
                        id: printImg
                        source: "qrc:/img/Images/Icons/print.png"
                        width: 25
                        height: 20
                    }
                    MouseArea{
                        anchors.topMargin: 50
                        anchors.fill: parent
                        onClicked: MainView.print()
                    }
                }
            }
        } // bulleltlist2 ends


}

}
