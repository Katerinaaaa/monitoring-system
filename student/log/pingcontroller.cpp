#include "pingcontroller.h"

#include <QDataStream>
#include <QHostInfo>
#include <QFile>
#include <QTime>


PingController::PingController()
{
   socket = new QUdpSocket(this);
}

void PingController::sendAction(QString status, QString descrip) {
    // Формируем сообщение для преподавателя
    QTime now = QTime::currentTime();
    QString timeStr = now.toString("hh:mm:ss");

    strData(" IP:" + myAddress() +
            " State:" + status +
            " Time:" + timeStr +
            " COMMAND LINE:" + descrip, ip_ip);
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
                          555 );
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
    qDebug() << ipAddress;

    return ipAddress;
}
