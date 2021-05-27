import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

Rectangle{
    anchors.fill: parent
    visible: false

    Connections{
       target: _pong

       onShowKeylog:{
           key.text =  keylog
       }
    }

    Image{
        id: backround
        fillMode: Image.PreserveAspectCrop //подгоняет картиночку красиво, по центру
        source: "qrc:/image/image/white.jpg"
        anchors.fill: parent
        opacity: 0.9 //немножко прозрачный
    }

    Pause{} // кнопка паузы

    ColumnLayout{
        anchors.fill: parent
        spacing: 10

        //выводим информацию о том, что напечатал определённый студент
        //Окошко со слайдером для всего кода
        ScrollView {
            focusPolicy: Qt.WheelFocus
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            Layout.fillHeight: true
            Layout.preferredWidth: 0.85 * parent.width

            TextArea{
                id: key
                textFormat: Text.AutoText
                textMargin: 8
                wrapMode: Text.WrapAnywhere
                color : "white"
                placeholderTextColor : "white"
                placeholderText: qsTr("Keylog от студента")
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
                page1.visible = true    // возвращаем главное окно приложения
                keyWindow.visible = false // убираем окно с текстом keylog
                pushanimation.start()
            }

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
                text: "ВЕРНУТЬСЯ"
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
