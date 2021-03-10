import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.3

// страничка с интерфейсом для создания политик на ограничения
// по сайтам и их отправкой студентам
Page{
    Connections {
        target: _pong // в окно будем выводить нашу политику
        onQmlPolitic: {
            showpolitic.text = textfile
        }
    }

    Image{  // наш фон
        anchors.fill: parent
        source: "qrc:/image/image/black.jpg"
        fillMode: Image.PreserveAspectCrop  //подгоняет картиночку красиво, по центру
    }


    ColumnLayout{
        anchors.fill: parent
        spacing: 20

        //переключатель между политиками
        Rectangle{
            Layout.topMargin: 20
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 0.6 * parent.width
            opacity: 0.9
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 0.00;
                    color: "#ffffff"
                }
                GradientStop {
                    position: 1.00;
                    color: "#000000"
                }
            }

            RowLayout {
                anchors.fill: parent

                RadioButton {
                    id: allow
                    text: qsTr("Запретить всё кроме...")
                    font.pixelSize: 14
                    font.family: "Courier"
                    font.weight: Font.Bold
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.leftMargin: 10
                    checked: true
                    onCheckedChanged: {
                        if (allow.checked == true){
                            showPolitic("allow.txt")
                            url_area.text = ""
                            url_area.placeholderText = qsTr("Введите URL разрешённого сайта/сайтов")
                        }
                    }
                }

                RadioButton {
                    id: prohib
                    text: qsTr("Разрешить всё кроме...")
                    font.pixelSize: 14
                    font.family: "Courier"
                    font.weight: Font.Bold
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.rightMargin: 10
                    onCheckedChanged: {
                        if (prohib.checked == true){
                            showPolitic("prohibit.txt")
                            url_area.text = ""
                            url_area.placeholderText = qsTr("Введите URL запрещённого сайта/сайтов")
                        }
                    }
                }
            }
        }

        // это строка для добавления новых url с окошком и кнопкой
        RowLayout{
            Layout.preferredHeight: 50
            Layout.preferredWidth: 0.8 * parent.width
            Layout.alignment: Qt.AlignHCenter

            ScrollView {
                focusPolicy: Qt.WheelFocus
                Layout.alignment: Qt.AlignLeft
                Layout.preferredHeight: 50
                Layout.preferredWidth: 0.78 * parent.width

                TextArea{
                    id: url_area
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.family: "Courier"
                    textFormat: Text.AutoText
                    placeholderText: qsTr("Введите URL разрешённого сайта/сайтов")
                    placeholderTextColor : "black"
                    background: Rectangle{
                        anchors.fill: parent
                        opacity: 0.9 //немножко прозрачный
                        radius: 5;
                    }
                }
            }

            MouseArea{
                id: url_button
                Layout.alignment: Qt.AlignRight
                Layout.preferredHeight: 50
                Layout.preferredWidth: 0.2 * parent.width
                hoverEnabled: true   //изменение цвета при наведении
                onEntered: {
                    url_rect.color = "#8C8C8C"
                    url_label.color =  "#ffffff"
                }
                onExited: {
                    url_rect.color = "#ffffff"
                    url_label.color =  "#000000"
                }

                onClicked: {
                    if (allow.checked == true &&    //запрещено всё кроме
                            url_area.text != ""){  //нельзя добавить пустую строку
                        addUrl(url_area.text, "allow.txt")
                        url_push.start()
                        url_area.text = ""
                    }
                    else if (prohib.checked == true &&  //разрешено всё кроме
                                    url_area.text != ""){ //нельзя добавить пустую строку
                        addUrl(url_area.text, "prohibit.txt")

                        url_area.text = ""
                    }
                }

                //фон кнопки
                Rectangle{
                    id: url_rect
                    radius: 5
                    opacity: 0.9
                    color: "white"
                    anchors.fill: parent
                }

                //текст для кнопки
                Label{
                    id: url_label
                    text: "Добавить"
                    font.pixelSize: 14
                    font.weight: Font.Bold
                    font.family: "Courier"
                    anchors.centerIn: parent
                }

                //вдавливание для кнопки (т.к. она кастомная)
                ScaleAnimator{
                    id: url_push
                    target: url_button
                    from: 0.9
                    to: 1.0
                    duration: 300
                }
            }
        }

        // окошко, которое выводит содержимое политик
        ScrollView {
            focusPolicy: Qt.WheelFocus
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: 0.8 * parent.width

            // сделали именно textarea, чтобы можно было записывать
            // сразу много сайтов и с новых строк
            TextArea{
                id: showpolitic
                textFormat: Text.AutoText
                wrapMode: Text.WrapAnywhere
                placeholderText: qsTr("В данный момент файл пуст.")
                placeholderTextColor : "black"
                font.family: "Courier"
                readOnly: true
                background: Rectangle{
                    radius: 5;
                    opacity: 0.9
                    anchors.fill: parent
                }

                MouseArea{
                    id: clear_button
                    height: 30
                    width: 120
                    anchors.right: showpolitic.right
                    anchors.bottom: showpolitic.bottom
                    anchors.bottomMargin: 0
                    anchors.rightMargin: 0
                    hoverEnabled: true                          //изменение цвета при наведении
                    onEntered: {
                        clear_rect.color = "#000000"
                        clear_label.color =  "#ffffff"
                    }
                    onExited: {
                        clear_rect.color = "#ffffff"
                        clear_label.color =  "#000000"
                    }

                    onClicked: {
                        if (allow.checked == true){
                            clearPolitic("allow.txt");
                        }
                        else if (prohib.checked == true){
                            clearPolitic("prohibit.txt");
                        }
                        clear_push.start()
                    }

                    //фон кнопки
                    Rectangle{
                        id: clear_rect
                        radius: 5
                        opacity: 0.9
                        color: "white"
                        anchors.fill: parent
                    }

                    //текст для кнопки
                    Label{
                        id: clear_label
                        text: "Очистить файл"
                        font.pixelSize: 12
                        font.family: "Courier"
                        font.weight: Font.Bold
                        anchors.centerIn: parent
                    }

                    //вдавливание для кнопки (т.к. она кастомная)
                    ScaleAnimator{
                        id: clear_push
                        target: clear_button
                        from: 0.9
                        to: 1.0
                        duration: 300
                    }
                }
            }
        }

        // Самая главная кнопка - для отправки политики студентам
        MouseArea{
            id: send_button
            Layout.bottomMargin: 20
            Layout.preferredWidth: 180
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter
            hoverEnabled: true      //изменение цвета при наведении
            onEntered: {
                send_rect.color = "#8C8C8C"
                send_lable.color =  "#ffffff"
            }
            onExited: {
                send_rect.color = "#ffffff"
                send_lable.color =  "#000000"
            }

            onClicked: {
                if (allow.checked == true){
                    sendPolitic("allow.txt", "172.16.122.66");
                }
                else if (prohib.checked == true){
                    sendPolitic("prohibit.txt", "172.16.122.66");
                }
                send_push.start()
            }

            //фон кнопки
            Rectangle{
                id: send_rect
                radius: 5
                opacity: 0.9
                color: "white"
                anchors.fill: parent
            }

            //текст для кнопки
            Label{
                id: send_lable
                text: "Отправить политику"
                font.pixelSize: 14
                font.family: "Courier"
                font.weight: Font.Bold
                anchors.centerIn: parent
            }

            //вдавливание для кнопки (т.к. она кастомная)
            ScaleAnimator{
                id: send_push
                target: send_button
                from: 0.9
                to: 1.0
                duration: 300
            }
        }
    }
}
