#ifndef PONGCONTROLLER_H
#define PONGCONTROLLER_H

#include <QUdpSocket>
#include <QDebug>

#include "studentsmodel.h"
#include "historsmodel.h"

/**
 * @brief The PongController class Класс для обмена информацией между пользователем и студентами
 */
class PongController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief PongController
     * @param parent
     */
    explicit PongController(QObject *parent = nullptr);

    /**
     * @brief s_model
     */
    StudentsModel * s_model;

    /**
     * @brief hist_model
     */
    HistorsModel * hist_model;

    /**
     * @brief ident для идентификаторов компьютеров
     */
    int ident = 0;

    /**
     * @brief number счётчик для количества попыток ввода пароля
     */
    int number = 0;

    /**
     * @brief socket Для работы по UDP-протоколу в локальной сети
     */
    QUdpSocket* socket;

    /**
     * @brief myAddress Получение текущего IP-адреса преподавателя
     * @return IP-адрес пользователя
     */
    QString myAddress();


public slots:

    /**
     * @brief passEnter Сравниваем пароль для входа в систему
     * @param passwd Пароль пользователя
     */
    void passEnter(QString passwd);

    /**
     * @brief UdpChat Соединение для получения данных
     */
    void UdpChat();

    /**
     * @brief historyIp Смотрим историю по каждому студенту
     * @param addr IP-адрес студента
     */
    void historyIp(QString addr);


    /**
     * @brief wantSnap Запрашиваем информацию об открытых окнах
     * @param addr IP-адрес студента
     */
    void wantSnap(QString addr);

    /**
     * @brief wantKeylog Запрашиваем информацию о введённых символах
     * @param addr IP-адрес студента
     */
    void wantKeylog(QString addr);

    // Дальше всё про создание политик

    /**
     * @brief addUrl Добавляем url в одну из политик
     * @param url Адрес сайта
     * @param filename Название файла политики
     */
    void addUrl(QString url, QString filename);

    /**
     * @brief showPolitic Отображаем политику в окне QML
     * @param filename Название файла политики
     */
    void showPolitic(QString filename);

    /**
     * @brief clearPolitic Очищаем файл с определённой политикой
     * @param filename Название файла политики
     */
    void clearPolitic(QString filename);

    /**
     * @brief sendPolitic Отправляем политику студентам
     * @param filename Название файла политики
     * @param ip IP-адрес студента
     */
    void sendPolitic(QString filename, QString ip);

private slots:

    /**
     * @brief saveToLogFile Сохраняем информацию о компьютерах в сети за день
     * @param str Новая строка с логами
     */
    void saveToLogFile(QString str);

    /**
     * @brief strPolitic Формируем сигналы для отправки студенту
     * @param politic Содержимое файла с политиками
     * @param ip IP-адрес студента
     */
    void strPolitic(QString politic, QString ip);

    /**
     * @brief strData Отправка сообщений студенту
     * @param message Содержимое сообщения
     * @param ip IP-адрес студента
     */
    void strData(QString message, QString ip);

    /**
     * @brief read Получаем сообщения и по их статусу идём в нужную функцию
     */
    void read();

    /**
     * @brief readKeylog Считываем нажатие клавиш студента
     * @param str Передаваемый текст
     */
    void readKeylog(QString str);

    /**
     * @brief readSnap Считываем информацию об открытых окнах
     * @param str Передаваемый список с открытыми окнами
     */
    void readSnap(QString str);

signals:

    /**
     * @brief passTrue Сигнал об успешном вводе пароля
     */
    void passTrue();

    /**
     * @brief passFalse Сигнал о неудачном вводе пароля
     */
    void passFalse();

    /**
     * @brief exitPass Сообщаем о том, что попытки закончились и закрываем приложение
     */
    void exitPass();

    /**
     * @brief ipQml Выводим на экран ip-преподавателя
     * @param ipAddress IP-адрес пользователя
     */
    void ipQml(QString ipAddress);

    /**
     * @brief ipStud Выводим на экран ip-студента в истории логов
     * @param ipStudents IP-адрес студента
     */
    void ipStud(QString ipStudents);

    /**
     * @brief changeDelegate Изменение цвета карточки компьютера
     * @param num_qml Номер карточки на главном экране
     * @param status Текущий статус (цвет) карточки
     */
    void changeDelegate(int num_qml, QString status);

    /**
     * @brief showHistory Смотрим историю логов по каждому компьютеру
     */
    void showHistory();

    /**
     * @brief showSnap Смотрим открытые окна определённого студента
     * @param snapshot Список открытых окон студента
     */
    void showSnap(QString snapshot);

    /**
     * @brief showKeylog Смотрим введённые символы определённого студента
     * @param keylog Текст, введённый с клавиатуры студентом
     */
    void showKeylog(QString keylog);

    /**
     * @brief qmlPolitic Отображение содержимого файла при его изменении
     * @param textfile Содержимое файла
     */
    void qmlPolitic(QString textfile);

protected:
    /**
     * @brief viewer Связь функций C++ с qml-страничками
     */
    QObject *viewer;

};

#endif // PONGCONTROLLER_H
