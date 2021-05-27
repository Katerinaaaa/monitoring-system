import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.1

ApplicationWindow {
    id: window
    visible: true
    width: 960
    height: 650
    title: qsTr("Приложение преподавателя")
    Connections {
        target: window
        onClosing: {
            close.accepted = false
            messageDialog.visible = true
        }
    }

    // уведомление перед закрытием приложения преподавателя
    MessageDialog {
        id: messageDialog
        visible: false
        icon: StandardIcon.Warning
        title: "Внимание!"
        text: "Вы уверены, что хотите закрыть приложение?\nВсе полученные Вами данные можно будет найти ТОЛЬКО в архиве"
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            close.accepted = true
            Qt.quit()
        }
    }

    signal myAddress()

    signal passEnter(string passwd);
    signal historyIp(string addr)
    signal wantSnap(string addr)
    signal wantKeylog(string addr)
    signal sendMess(string addr)  

    signal addUrl(string url, string filename)
    signal showPolitic(string filename)
    signal clearPolitic(string filename)
    signal sendPolitic(string filename, string addr)


    SwipeView {
        id: swipeView
        font.bold: true
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1{
            id: page1
            visible: false
        }

        Page2{
            id: page2
        }
    }

     footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Главная панель")
        }

        TabButton {
            text: qsTr("Создание политик")
        }
     }

     // страничка с историей логов от каждого студента
     History{
         id: historyWindow
     }

     // страничка с информацией об открытых окнах студента
     Snapshot{
         id: snapWindow
     }

     // страничка с информацией, введённой с клавиатуры студентом
     Keylogger{
         id: keyWindow
     }

     // окно для ввода пароля преподавателя
     Password{
         id: passWindow
     }

}






