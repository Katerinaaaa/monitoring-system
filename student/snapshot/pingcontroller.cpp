#include "pingcontroller.h"

#include <QDataStream>
#include <QHostInfo>
#include <QFile>
#include <QTime>

#include <QTextCodec>

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
    WCHAR title[260];
    if (!IsWindowVisible(hWnd))
        return TRUE;

    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);

    GetWindowText(hWnd, title, 260);

    QTextCodec *CodecUtf8=QTextCodec::codecForName("UTF-8"); //перевод из CP866 в Utf-8
    QString titleUtf=CodecUtf8->fromUnicode(title);

    QString str_pid = QString::number(pid);
    QString data = ("PID: " + str_pid + " TITLE: " + titleUtf);

    if (titleUtf != ""){
        QFile file("snapshot.txt");

        file.open(QIODevice::ReadWrite | QIODevice::Text
                  | QIODevice::Append );
        QTextStream log(&file);
        log.setCodec("UTF-8");
        log << data << endl;
        file.close();
    }

    if (lParam == 0) EnumChildWindows(hWnd, EnumChildProc, 1);
    return TRUE;    //continue enumeration
}

PingController::PingController()
{
   socket = new QUdpSocket(this);
}

void PingController::sendPing() {
    // Формируем ping
    QTime now = QTime::currentTime();
    QString timeStr = now.toString("hh:mm:ss");

    strData(" IP:" + myAddress() +
            " State:ping" +
            " Time:" + timeStr +
            " CAPTION: ___ COMMAND LINE: Student Online", ip_ip);
}

void PingController::sendSnapshot(QString data){
    // Формируем отправку снэпшота
    QTime now = QTime::currentTime();
    QString timeStr = now.toString("hh:mm:ss");

    strData(" IP:" + myAddress() +
            " State:snapshot" + " Time:" + timeStr +
            " Data:" + data + "$END", ip_ip);
}

void PingController::strData(QString str, QString ip) {
    QByteArray data; // Массив данных для отправки

    // Последовательно выводим в него байты
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint8(); // Тип сообщения
    out << str; // Само сообщение

    // Отправляем полученный массив данных преподавателю
    // на порт указанный в интерфейсе
    socket->writeDatagram(data,
                          QHostAddress(ip),
                          555);
}

QString PingController::myAddress() {
    QString ipAddress;
    QHostInfo info = QHostInfo::fromName( QHostInfo::localHostName() );
    QList<QHostAddress> listAddr= info.addresses();

    for( int i = 0; i < listAddr.size(); i ++ ){
        if( listAddr.at(i).protocol() == QAbstractSocket::IPv4Protocol ){
            ipAddress += listAddr.at(i).toString();
          }
    }
    return ipAddress;
}

void PingController::UdpChat() {
    qDebug() << "Listening...";
    socket = nullptr;

    // Создаём класс для работы с сетью
    socket = new QUdpSocket(this);

    // Все входящие на этот порт сообщения будут
    // поступать в нашу программу
    if(socket->bind(QHostAddress::Any, 555)) {
        qDebug() << "UDPCHAT";
        // При получении данных (сигнал readyRead)
        // вызываем слот, который читает и обрабатывает сообщение
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    }
}

void PingController::read() {
    while (socket->hasPendingDatagrams()) {
        qDebug() << "Reading message...";
        // буфер для полученных данных
        QByteArray buf;

        // Устанавливаем массиву размер
        // соответствующий размеру полученного пакета данных
        buf.resize(socket->pendingDatagramSize());
        QHostAddress* address = new QHostAddress();

        // Принимаем данные пришедшие по сети
        socket->readDatagram(buf.data(), buf.size(), address);

        // Разбор полученного пакета
        QDataStream in(&buf, QIODevice::ReadOnly);

        // Получаем тип пакета
        qint8 type = 0;
        in >> type;

        QString signal;
        in >> signal;

        qDebug() << "Signal from Teacher " << signal;

        QString Str = "filename:";
        int x = signal.indexOf(Str);
        x += Str.length();
        int y = signal.indexOf(".txt", x);
        QString filename = signal.mid(x, y-x) + ".txt";

        // отправляем преподавателю результат снэпшота
        if (signal == "wantSnap"){
            QFile file("snapshot.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                file.close();   //очищаем файл перед повторной отправкой

            EnumChildWindows(nullptr, EnumChildProc, 0);
            file.open(QIODevice::ReadOnly);
            QByteArray data =  file.readAll();
            file.close();
            sendSnapshot(data);
        }

        // считываем содержимое файла с политикой или файла с метками действий
        else{
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                file.close();   //очищаем файл перед открытием на запись

            file.open(QIODevice::WriteOnly);
            QTextStream log(&file);
            log.setCodec("UTF-8");
            log << signal << endl;
            file.close();
        }
    }
}
