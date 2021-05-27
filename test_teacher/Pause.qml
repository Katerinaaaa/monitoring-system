import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.3

//кнопка паузы
Button{
    id: pause
    width: 40
    height: 40
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.margins: 20

    onClicked: {
        pushanimation01.start()
        passWindow.visible = true // прячем окно авторизации
        page1.visible = false // показываем окно нашего приложени
    }

    background: Image {
        id: menu
        anchors.fill: parent
        source: "qrc:/image/image/pause.png"
    }

    ScaleAnimator{
        id: pushanimation01
        target: pause
        from: 0.7
        to: 1.0
        duration: 120
        running: false
    }
}
