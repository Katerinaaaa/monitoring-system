#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "pongcontroller.h"
#include "studentsmodel.h"
#include "historsmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();

    PongController pong;

    context->setContextProperty("_pong", &pong);
    context->setContextProperty("_students", pong.s_model);

    context->setContextProperty("_modelHist", pong.hist_model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    pong.myAddress();   //адрес будем выводить при открытии приложения
    pong.UdpChat();     //принимаем данные от студента

    QObject::connect(engine.rootObjects().first(), SIGNAL(historyIp(QString)),
            &pong, SLOT(historyIp(QString)));   //смотрим историю событий по каждому студенту

    QObject::connect(engine.rootObjects().first(), SIGNAL(wantSnap(QString)),
            &pong, SLOT(wantSnap(QString)));    //запрашиваем у студента список открытых окон

    QObject::connect(engine.rootObjects().first(), SIGNAL(wantKeylog(QString)),
            &pong, SLOT(wantKeylog(QString)));    //смотрим, что печатал студент

    //Все последущие сигналы нужны для создания и отправки файлов с политиками
    QObject::connect(engine.rootObjects().first(), SIGNAL(addUrl(QString, QString)),
            &pong, SLOT(addUrl(QString, QString)));    //добавляем разрешённый сайт в файл

    QObject::connect(engine.rootObjects().first(), SIGNAL(showPolitic(QString)),
            &pong, SLOT(showPolitic(QString)));    //отображаем существующую политику в окне

    QObject::connect(engine.rootObjects().first(), SIGNAL(clearPolitic(QString)),
            &pong, SLOT(clearPolitic(QString)));    //очищаем файл с политикой

    QObject::connect(engine.rootObjects().first(), SIGNAL(sendPolitic(QString, QString)),
            &pong, SLOT(sendPolitic(QString, QString)));    //отправляем файл с политикой студентам

    pong.showPolitic("allow.txt"); // потому что кнопка сразу стоит на этой политике

    return app.exec();
}
