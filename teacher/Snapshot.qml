import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

//Фон абстракт для шифрования
Rectangle{
    anchors.fill: parent
    visible: false

    Connections{
       target: _pong

       onShowSnap:{
           snap.text =  snapshot
       }
    }

    Image{
        id: backround
        fillMode: Image.PreserveAspectCrop //подгоняет картиночку красиво, по центру
        source: "qrc:/image/image/white.jpg"
        anchors.fill: parent
        opacity: 0.9 //немножко прозрачный
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 20

        //выводим студентов
        //Окошко со слайдером для всего кода
        ScrollView {
            focusPolicy: Qt.WheelFocus
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: 0.85 * parent.width


            TextArea{
                id: snap
                textFormat: Text.AutoText
                textMargin: 8
                wrapMode: Text.WrapAnywhere
                color : "white"
                placeholderText: qsTr("Snapshot от студента")
                placeholderTextColor : "white"
                readOnly: true
                font.family: "Courier"
                background: Rectangle{
                    anchors.fill: parent
                    opacity: 0.9 //немножко прозрачный
                    radius: 5;
                    color: "#000000"
                }
            }
        }

        MouseArea{
            id: my_button
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 35
            Layout.preferredWidth: 150
            Layout.bottomMargin: 20
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
                page1.visible = true // возвращаем окно авторизации
                snapWindow.visible = false // убираем окно с текстом
                pushanimation.start()
            }

            //белый фон кнопки
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
                text: "ВЕРНУТЬСЯ"
                font.weight: Font.Bold
                font.family: "Courier"
                color: "#ffffff"
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
