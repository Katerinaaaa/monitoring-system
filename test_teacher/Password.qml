import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtTest 1.2

Page{
    anchors.fill: parent
    visible: true

    Connections{
       target: _pong

       //вызывается из С++ если пароль введён верно
       onPassTrue:{
           passWindow.visible = false // прячем окно авторизации
           page1.visible = true // показываем окно нашего приложения
           welcome.text = "Приложение в режиме ожидания.\nВведите пароль."
           passwd.text = ""
       }

       //вызывается из С++ если пароль безопасности введён неверно
       onPassFalse: {
           passwd.text = ""
           welcome.text = "Вы ввели неверный пароль.\nПопробуйте ещё раз"
       }

       //вызывается из С++ если количество попыток превышено
       onExitPass: {
           welcome.text = "Количество попыток превышено!\nВы злоумышленник!\nДо свидания!"
           passwd.visible = false
           my_button.visible = false;
           time.running = true
       }
    }

    Timer{  // для того, чтобы закрывать программу не сразу
        id: time
        interval: 3000
        running: false
        onTriggered: {
            Qt.quit()
        }
    }

    Image{
        id: backround
        fillMode: Image.PreserveAspectCrop //подгоняет картиночку красиво, по центру
        source: "qrc:/image/image/black.jpg"
        anchors.fill: parent
        opacity: 0.9 //немножко прозрачный
    }

    Rectangle{
        color: "#ffffff"
        anchors.centerIn: parent
        height: 0.5 * parent.height
        width: 0.5 * parent.width
        opacity: 0.9
        radius: 5
    }

    ColumnLayout{
        anchors.centerIn: parent
        height: 0.4 * parent.height
        width: 0.4 * parent.width

        TextEdit{
            id: welcome
            text: "Добро пожаловать!\nВведите пароль безопасности\nдля входа в систему!"
            wrapMode: Text.WrapAnywhere
            readOnly: true
            color: "#000000"
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
        }


        TextField{  //В это окошко мы вводим пароль, который передаётся в С++
            id: passwd
            text: ""
            placeholderText: qsTr("Пароль")
            font.letterSpacing: 0.3
            font.pixelSize: 14
            font.weight: Font.Light
            font.family: "Tahoma"
            color: "black"
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            cursorVisible: true
            echoMode: TextInput.Password
            background: Rectangle{
                anchors.fill: parent
                color: "white"
            }
        }

        MouseArea{
            id: my_button
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 35
            Layout.preferredWidth: 150
            Layout.bottomMargin: 10
            hoverEnabled: true                          //изменение цвета при наведении
            onEntered: {
                button.color = "#CDCDCB"
                label.color =  "#000000"
            }
            onExited: {
                button.color = "#000000"
                label.color =  "#ffffff"
            }

            onClicked: {
                passEnter(passwd.text);
                pushanimation.start()
            }

            //ТЕСТ КЕЙС КНОПКИ !!!!!

            /*TestCase{
                name: "Clicked button enter"
                when: windowShown
                function test_click(){
                    my_button.clicked();
                    //compare(my_button.)
                }

            }*/

            //чёрный фон кнопки
            Rectangle{
                id: button
                anchors.fill: parent
                radius: 5
                opacity: 0.9
                color: "#000000"
            }

            //текст для кнопки
            Label{
                id: label
                anchors.centerIn: parent
                text: "ВОЙТИ"
                font.weight: Font.Bold
                font.family: "Courier"
                color: "white"
            }

            //вдавливание для кнопки (т.к. она кастомная)
            ScaleAnimator{
                id: pushanimation
                target: my_button
                from: 0.9
                to: 1.0
                duration: 300
            }
        }
    }
}


