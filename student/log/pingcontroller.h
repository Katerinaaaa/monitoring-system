#ifndef PINGCONTROLLER_H
#define PINGCONTROLLER_H

#include <QUdpSocket>
#include <Windows.h>

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

    // формируем "сообщение" для отправки
    void strData(QString str, QString ip);

    // отправляем логи преподавателю
    void sendAction(QString status, QString descrip);

};

#endif // PINGCONTROLLER_H
