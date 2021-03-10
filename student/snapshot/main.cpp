#include <QCoreApplication>

#include "pingcontroller.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PingController ping;

    ping.sendPing();    //отправляем пинг преподавателю

    ping.UdpChat();     //слушаем и ждём сообщение "wantSnap", а также файлы с метками

    return a.exec();
}


