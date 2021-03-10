#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <QUdpSocket>
#include <QDebug>

#include "studentsmodel.h"

#include "historsmodel.h"

class PongController : public QObject
{
    Q_OBJECT

public:
    explicit PongController(QObject *parent = nullptr);

    StudentsModel * s_model;

    HistorsModel * hist_model;

    int ident = 0; // для идентификаторов компьютеров

    int number = 0; // счётчик для количества попыток ввода пароля

    // Для работы по UDP-протоколу в локальной сети
    QUdpSocket* socket;

    QString myAddress();


public slots:
    // Соединение для получения данных
    void UdpChat();
    // Смотрим историю по каждому студенту
    void historyIp(QString addr);

    // Запрашиваем информацию об открытых окнах
    void wantSnap(QString addr);
    // Запрашиваем информацию о введённых символах
    void wantKeylog(QString addr);

    // Дальше всё про создание политик
    // Добавляем url в одну из политик
    void addUrl(QString url, QString filename);
    // Отображаем политику в окне QML
    void showPolitic(QString filename);
    // Очищаем файл с определённой политикой
    void clearPolitic(QString filename);
    //отправляем политику студентам
    void sendPolitic(QString filename, QString ip);

private slots:
    // Сохраняем информацию о компьютерах в сети за день
    void saveToLogFile(QString str);
    // Формируем сигналы для отправки студенту
    void strPolitic(QString politic, QString ip);
    void strData(QString message, QString ip);
    // Получаем сообщения и по их статусу идём в нужную функцию
    void read();
    // Считываем нажатие клавиш студента
    void readKeylog(QString str);
    // Считываем информацию об открытых окнах
    void readSnap(QString str);

signals:
    // выводим на экран ip-преподавателя
    void ipQml(QString ipAddress);
    // выводим на экран ip-студента в истории логов
    void ipStud(QString ipStudents);
    // меняем цвет карточки компьютера
    void changeDelegate(int num_qml, QString status);
    // смотрим историю логов по каждому компьютеру
    void showHistory();

    // смотрим открытые окна определённого студента
    void showSnap(QString snapshot);
    // смотрим введённые символы определённого студента
    void showKeylog(QString keylog);
    //будет отображать содержимое файла при его изменении
    void qmlPolitic(QString textfile);

protected:
    QObject *viewer;  // связь функций C++ с qml-страничками

};

#endif // PONGCONTROLLER_H
