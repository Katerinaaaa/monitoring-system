#ifndef PINGCONTROLLER_H
#define PINGCONTROLLER_H

#include <QObject>
#include <Windows.h>
#include <QUdpSocket>

class PingController : public QObject
{
    Q_OBJECT
public:
    PingController();

    QString myAddress();    // узнаем свой IP

    // Для работы по UDP-протоколу в локальной сети
    QUdpSocket* socket;

    QString ip_ip = "0.0.0.0";  // необхожимо прописать нужный адрес преподавателя

public slots:
    // Отправляем пинг при загрузке программы
    void sendPing();

    //ждём сигнал от преподавателя для отправки данных
    void UdpChat();

    //отправляем информацию об открытых окнах студента
    void sendSnapshot(QString data);

    //формируем "сообщение" для отправки
    void strData(QString str, QString ip);

private slots:
    //читаем сигналы от преподавателя
    void read();
};

#endif // PINGCONTROLLER_H
