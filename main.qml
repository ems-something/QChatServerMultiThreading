import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls.Material 2.0
import server 1.0

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Chat Server")
    minimumHeight: 480
    maximumHeight: 480
    minimumWidth: 640
    maximumWidth: 640

    Material.theme: Material.Dark
    Material.accent: Material.color(Material.DeepPurple)

    Server {
        id: server
        objectName: "server"
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            OldControls.ScrollView {
                x: 30
                y: 30
                ListView {
                    id: listView
                    objectName: "clientsListView"
                    width: 100; height: 100
                    delegate: Rectangle {
                        height: 25
                        width: 100
                        color: Material.color(Material.Purple)
                        Text {
                            text: modelData
                            color:"#ffffff"
                        }
                    }
                }
            }
            Text {
                id: headerTabFiles
                objectName: "headerTabView"
                x: 200
                y: 20
                text: "Client's List"
                color: "#ffffff"
            }
            Text {
                id: tabFiles
                objectName: "fileTabView"
                x: 200
                y: 35
                color: "#ffffff"
            }
            /*Button{
                id: btnChange
                x: 30
                y: 340
                text: "PRIORIDAD"
                onClicked: {
                    if (btnChange.text == "PRIORIDAD")
                    {
                        server.changePlan(2)
                        btnChange.text = "FIFO"
                        btnChange.height = 50
                    }
                    else
                    {
                        server.changePlan(1)
                        btnChange.text = "PRIORIDAD"
                    }
                }
            }*/
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            id: btnInf
            text: qsTr("Información")
            objectName: "btnInfo"
        }
        TabButton {
            id: btnIni
            text: qsTr("Iniciar")
            objectName: "btnInit"
            onClicked: {
                if (btnIni.text == "Iniciar")
                {
                    server.setView(rootWindow)
                    btnIni.text = "Servidor"

                    // Create an instance of a server and then start it.
                    server.init()

                }
            }
        }
    }
}
