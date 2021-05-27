import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.3

Page{
    Connections {
        target: _pong   // все эти сигналы находятся в pongcontroller
        onIpQml: {      // в окно будем выводить ip преподавателя
            ip_address.text = "Ваш ip-адрес: " + ipAddress
        }

        onShowHistory:{ // будем открывать другую странику с историей логов
            page1.visible = false
            historyWindow.visible = true
        }

        onShowSnap:{    // будем открывать другую страничку с информацией об открытых окнах студента
            page1.visible = false
            snapWindow.visible = true
        }

        onShowKeylog:{  // будем открывать другую страничку с информацией, введённой студентом с клавиатуры
            page1.visible = false
            keyWindow.visible = true
        }
    }


    ScrollView{
        anchors.fill: parent

        Image{
            id: backround
            anchors.fill: parent
            source: "qrc:/image/image/black.jpg"
            fillMode: Image.PreserveAspectCrop //подгоняет картиночку красиво, по центру  
        }

        Pause{} // кнопка паузы

        ColumnLayout{
            anchors.fill: parent
            spacing: 10

            Rectangle{
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
                Layout.topMargin: 10
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 0.6 * parent.width
                Layout.preferredHeight: 60
                opacity: 0.9 //немножко прозрачный
                radius: 5;

                TextEdit{
                    id: ip_address
                    readOnly: true
                    color: "#ffffff"
                    font.pointSize: 14
                    font.weight: Font.Bold
                    font.family: "Courier"
                    anchors.centerIn: parent
                }
            }

            //выводим карточки студентов
            GridView{
                id: gridView
                cellHeight: 200
                cellWidth: 320
                Layout.alignment: Qt.AlignHCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.topMargin: 20
                Layout.leftMargin: 40
                enabled: true
                model: _students

                //карточка с фоном
                delegate: Rectangle{
                    radius: 10
                    width: 300
                    height: 180
                    opacity: 0.9
                    color: {
                        if (status == "good" || status == "ping"){
                            grad.color = "#c6f500"
                        }
                        else if (status == "warning"){
                            grad.color = "orange"
                        }
                        else if (status == "danger"){
                            grad.color = "#fd0006"
                        }
                    }

                    gradient: Gradient {
                        GradientStop {
                            id: grad
                            position: 0.00;
                        }
                        GradientStop {
                            position: 1.00;
                            color: "#000000"
                        }
                    }

                    Connections {           // нельзя вынести вне модели, иначе делигаты не будут изменяться
                        target: _pong
                        onChangeDelegate: {
                            if (model.index === num_qml){
                                if (status == "good" || status == "ping") {
                                    grad.color = "#c6f500"
                                }
                                else if (status == "warning"){
                                    grad.color = "orange"
                                }
                                else if (status == "danger"){
                                    grad.color = "#fd0006"
                                }
                            }
                        }
                    }

                    GridLayout{
                        anchors.centerIn: parent
                        columns: 1
                        rows: 2

                        Label{  //ip-адрес
                            text: "IP: " + addr
                            Layout.column: 0
                            Layout.row: 1
                            color: "#ffffff"
                            font.pointSize: 12
                            font.family: "Courier"
                            Layout.fillHeight: true
                            Layout.bottomMargin: 10
                            Layout.preferredWidth: 0.9 * parent.width
                            Layout.alignment: Qt.AlignHCenter
                        }

                            MouseArea{
                                id: my_button
                                Layout.alignment: Qt.AlignHCenter
                                Layout.preferredHeight: 35
                                Layout.preferredWidth: 205
                                hoverEnabled: true                          //изменение цвета при наведении
                                onEntered: {
                                    button.color = "#000000"
                                    label.color =  "#ffffff"
                                }
                                onExited: {
                                    button.color = "#ffffff"
                                    label.color =  "#000000"
                                }

                                onClicked: {
                                    historyIp(addr);
                                    pushanimation.start()
                                }

                                //фон кнопки
                                Rectangle{
                                    id: button
                                    anchors.fill: parent
                                    radius: 5
                                    opacity: 0.9
                                }

                                //текст для кнопки
                                Label{
                                    id: label
                                    anchors.centerIn: parent
                                    text: "История"
                                    font.weight: Font.Bold
                                    font.family: "Courier"
                                    font.pixelSize: 14
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

                            RowLayout{
                                MouseArea{
                                    id: my_button1
                                    Layout.alignment: Qt.AlignHCenter
                                    Layout.preferredHeight: 35
                                    Layout.preferredWidth: 100
                                    hoverEnabled: true                          //изменение цвета при наведении
                                    onEntered: {
                                        button1.color = "#000000"
                                        label1.color =  "#ffffff"
                                    }
                                    onExited: {
                                        button1.color = "#ffffff"
                                        label1.color =  "#000000"
                                    }

                                    onClicked: {
                                        wantSnap(addr);
                                        pushanimation1.start()
                                    }

                                    //фон кнопки
                                    Rectangle{
                                        id: button1
                                        anchors.fill: parent
                                        radius: 5
                                        opacity: 0.9
                                    }

                                    //текст для кнопки
                                    Label{
                                        id: label1
                                        anchors.centerIn: parent
                                        text: "Snapshot"
                                        font.weight: Font.Bold
                                        font.family: "Courier"
                                        font.pixelSize: 14
                                    }

                                    //вдавливание для кнопки (т.к. она кастомная)
                                    ScaleAnimator{
                                        id: pushanimation1
                                        target: my_button1
                                        from: 0.9
                                        to: 1.0
                                        duration: 300
                                    }
                                }

                                MouseArea{
                                    id: my_button2
                                    Layout.alignment: Qt.AlignHCenter
                                    Layout.preferredHeight: 35
                                    Layout.preferredWidth: 100
                                    hoverEnabled: true                          //изменение цвета при наведении
                                    onEntered: {
                                        button2.color = "#000000"
                                        label2.color =  "#ffffff"
                                    }
                                    onExited: {
                                        button2.color = "#ffffff"
                                        label2.color =  "#000000"
                                    }

                                    onClicked: {
                                        wantKeylog(addr);
                                        pushanimation2.start()
                                    }

                                    //фон кнопки
                                    Rectangle{
                                        id: button2
                                        anchors.fill: parent
                                        radius: 5
                                        opacity: 0.9
                                    }

                                    //текст для кнопки
                                    Label{
                                        id: label2
                                        anchors.centerIn: parent
                                        text: "Keylog"
                                        font.weight: Font.Bold
                                        font.family: "Courier"
                                        font.pixelSize: 14
                                    }

                                    //вдавливание для кнопки (т.к. она кастомная)
                                    ScaleAnimator{
                                        id: pushanimation2
                                        target: my_button2
                                        from: 0.9
                                        to: 1.0
                                        duration: 300
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
