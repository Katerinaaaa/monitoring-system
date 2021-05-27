import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12

Rectangle{
    id:pagehist
    anchors.fill: parent
    visible: false

    // отображаем ip истории студента, карточку которого открыли
    Connections{
       target: _pong

       onIpStud:{
           studIp.text = "История студента: " + ipStudents
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


        // Табличка с IP студента
        Rectangle{
            gradient: Gradient {
                GradientStop {
                    position: 0.00;
                    color: "#9B9E94"
                }
                GradientStop {
                    position: 1.00;
                    color: "#000000"
                }
            }
            Layout.topMargin: 20
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 0.6 * parent.width
            Layout.preferredHeight: 50
            opacity: 0.9 //немножко прозрачный
            radius: 5;

            TextEdit{
                id: studIp
                readOnly: true
                color: "#ffffff"
                font.pointSize: 14
                font.weight: Font.Bold
                font.family: "Courier"
                anchors.centerIn: parent
            }
        }

        //переключатель между всей историей и опасными действиями
        RowLayout {
            Layout.alignment:  Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            RadioButton {
                id: all
                text: qsTr("ВСЕ ДЕЙСТВИЯ")
                font.pixelSize: 14
                font.family: "Courier"
                font.weight: Font.Bold
                checked: true
                onCheckedChanged: {
                    if (all.checked == true){  //если выключатель на кнопке "Все действия"
                        listView.visible = true;
                        listView2.visible = false;
                    }
                }
            }

            RadioButton {
                id: danger
                text: qsTr("ОПАСНЫЕ ДЕЙСТВИЯ")
                font.pixelSize: 14
                font.family: "Courier"
                font.weight: Font.Bold
                checked: false
                onCheckedChanged: {
                    if (danger.checked == true){  //если выключатель на кнопке "Опасные действия"
                        listView2.visible = true;
                        listView.visible = false;
                    }
                }
            }
        }


        ListView{
            id: listView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: 0.85 * pagehist.width
            Layout.bottomMargin: 30
            visible: true
            enabled: true
            spacing: 20
            model: _modelHist //модель с историей логов студента

            //карточка с параметрами
            delegate: Rectangle{
                width: parent.width
                height: 80
                radius: 5
                color: {
                    if (status == "good" || status == "ping"){
                        status_png.source = "qrc:/image/image/good.png"
                    }
                    else if (status == "warning"){
                        status_png.source = "qrc:/image/image/warning.png"
                    }
                    else if (status == "danger"){
                        status_png.source = "qrc:/image/image/danger.png"
                    }
                }

                gradient: Gradient {
                    GradientStop {
                        color: "#9B9E94"
                        position: 0.00;
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#000000"
                    }
                }

                GridLayout{
                    anchors.fill: parent
                    columns: 4
                    rows: 2

                    Image{  //Статус
                        id: status_png
                        Layout.column: 0
                        Layout.rowSpan: 2
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 50
                        Layout.leftMargin: 10
                        Layout.rightMargin: 10
                    }

                    Label{  //время
                        text: time
                        Layout.column: 1
                        Layout.row: 0
                        color: "#ffffff"
                        font.pointSize: 12
                        font.family: "Courier"
                        Layout.preferredHeight: 0.2 * parent.height
                        Layout.preferredWidth: 0.2 * parent.width
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.rightMargin: 10
                    }

                    Label{  //дата
                        text: date
                        Layout.column: 1
                        Layout.row: 1
                        color: "#ffffff"
                        font.pointSize: 12
                        font.family: "Courier"
                        Layout.preferredHeight: 0.3 * parent.height
                        Layout.preferredWidth: 0.2 * parent.width
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.rightMargin: 10
                    }

                    Label{  //событие
                        text: exe
                        Layout.column: 2
                        Layout.rowSpan: 2
                        color: "#ffffff"
                        font.pointSize: 12
                        font.family: "Courier"
                        wrapMode: Text.WrapAnywhere
                        Layout.preferredHeight: 0.3 * parent.height
                        Layout.preferredWidth: 0.2 * parent.width
                        Layout.rightMargin: 10
                    }

                    Label{  //путь
                        text: descrip
                        Layout.column: 3
                        Layout.rowSpan: 2
                        color: "#ffffff"
                        font.pointSize: 10
                        font.family: "Courier"
                        wrapMode: Text.WrapAnywhere
                        Layout.preferredHeight: 0.8 * parent.height
                        Layout.fillWidth: true
                        Layout.rightMargin: 20
                    }
                }
            }
        }

        // выбираем только опасные действия
        ListView{
            id: listView2
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: 0.85 * pagehist.width
            Layout.bottomMargin: 30
            visible: false
            enabled: true
            model: _modelHist //модель с историей логов студента

            //карточка с фоном
            delegate: Item{
                id:item
                width: parent.width
                height: 100
                Rectangle{
                    width: parent.width
                    height: 80
                    radius: 5
                    anchors.bottomMargin: 10
                    visible: {
                        if (status != "danger"){
                            item.visible = false
                            item.height = 0
                        }
                    }

                    gradient: Gradient {
                        GradientStop {
                            color: "#9B9E94"
                            position: 0.00;
                        }
                        GradientStop {
                            position: 1.00;
                            color: "#000000"
                        }
                    }

                    GridLayout{
                        anchors.fill: parent
                        width: parent.width
                        height: 80
                        columns: 4
                        rows: 2

                        Image{  //Статус
                            Layout.column: 0
                            Layout.rowSpan: 2
                            Layout.preferredHeight: 50
                            Layout.preferredWidth: 50
                            Layout.leftMargin: 10
                            Layout.rightMargin: 10
                            source: "qrc:/image/image/danger.png"
                        }

                        Label{  //время
                            text: time
                            Layout.column: 1
                            Layout.row: 0
                            color: "#ffffff"
                            font.pointSize: 12
                            font.family: "Courier"
                            Layout.preferredHeight: 0.2 * parent.height
                            Layout.preferredWidth: 0.2 * parent.width
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.rightMargin: 10
                        }

                        Label{  //дата
                            text: date
                            Layout.column: 1
                            Layout.row: 1
                            color: "#ffffff"
                            font.pointSize: 12
                            font.family: "Courier"
                            Layout.preferredHeight: 0.3 * parent.height
                            Layout.preferredWidth: 0.2 * parent.width
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.rightMargin: 10
                        }

                        Label{  //событие
                            text: exe
                            Layout.column: 2
                            Layout.rowSpan: 2
                            color: "#ffffff"
                            font.pointSize: 12
                            font.family: "Courier"
                            wrapMode: Text.WrapAnywhere
                            Layout.preferredHeight: 0.3 * parent.height
                            Layout.preferredWidth: 0.2 * parent.width
                            Layout.rightMargin: 10
                        }

                        Label{  //путь
                            text: descrip
                            Layout.column: 3
                            Layout.rowSpan: 2
                            color: "#ffffff"
                            font.pointSize: 10
                            font.family: "Courier"
                            wrapMode: Text.WrapAnywhere
                            Layout.preferredHeight: 0.8 * parent.height
                            Layout.fillWidth: true
                            Layout.rightMargin: 20
                        }
                    }
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
                button.color = "#ffffff"
                label.color =  "#000000"
            }
            onExited: {
                button.color = "#000000"
                label.color =  "#ffffff"
            }

            onClicked: {
                page1.visible = true;           // возвращаем главное окно приложение
                historyWindow.visible = false;  // убираем вкладку с историей логов
                all.checked = true;
                pushanimation.start();
                _modelHist.clearR();            // очищаем модель истории
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
                color:"#ffffff"
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
