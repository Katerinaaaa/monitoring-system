#include <QTest>
#include "test_file.h"


Test_File::Test_File(QObject *parent) :
    QObject(parent)
{
}

// QCOMPARE выводит более подробное сообщение со сравнением
// QVERIFY выводит краткое сообщение об ошибке
// QEXPECT_FAIL показывает ожидаемый сбой и не считает за ошибку

void Test_File::test_ip_true()
{
    // здесь необходимо прописать адрес из настроек или ipconfig
    QCOMPARE(pong.myAddress(), "172.16.125.212");
}

void Test_File::test_ip_false()
{
    // прописываем любой чужой адрес
    QCOMPARE(pong.myAddress(), "172.16.125.210");
}

void Test_File::test_pass_true()
{
    // здесь необходимо прописать верный пароль  
    QVERIFY(pong.passEnter("12345") == 0);
}

void Test_File::test_pass_false()
{
    // здесь необходимо прописать неверный пароль
    QVERIFY(pong.passEnter("Another wrong pass") == 0);
}

void Test_File::test_politic_true()
{
    // здесь необходимо прописать отправляемую политику и ip студента
    QCOMPARE(pong.strPolitic("Allow politic", "192.168.1.0"), "Allow politic");
}

void Test_File::test_politic_false()
{
    // здесь необходимо прописать отправляемую политику и ip студента
    QCOMPARE(pong.strPolitic("Allow politic", "192.168.1.0"), "Prohibit politic");
}

void Test_File::test_message_true()
{
    // здесь необходимо прописать отправляемое сообщение и ip студента
    QCOMPARE(pong.strData("Sent message!", "192.168.1.0"), "IP: 192.168.1.0 Message: Sent message!");
}

void Test_File::test_message_false()
{
    // здесь необходимо прописать отправляемое сообщение и ip студента
    QCOMPARE(pong.strData("Sent message!", "192.168.1.0"), "Sent message!");
}

void Test_File::test_snap_true()
{
    // именно в таком сложном виде приложение студента присылает snapshot
    // проверяем, что функция может выделять только нужные данные
    QCOMPARE(pong.readSnap(" IP:192.168.1.10 State:snapshot Time:10:05:22 Data:Very important information snapshot!$END"),
                           "Very important information snapshot!");
}

void Test_File::test_snap_false()
{
    // именно в таком сложном виде приложение студента присылает snapshot
    // проверяем, что функция может выделять только нужные данные
    QCOMPARE(pong.readSnap(" IP:192.168.1.10 State:snapshot Time:10:05:22 Data:Very important information snapshot!$END"),
                           "Very important!");
}

void Test_File::test_keylog_true()
{
    // именно в таком сложном виде приложение студента присылает keylog
    // проверяем, что функция правильно выделяет IP-адрес для дальнейшей работы
    QCOMPARE(pong.readKeylog(" IP:192.168.1.10 State:keylog Time:10:05:22 Data:Keylog!$END"), "192.168.1.10");
}

void Test_File::test_keylog_false()
{
    // QEXPECT_FAIL показывает ожидаемый сбой и не считает за ошибку
    QEXPECT_FAIL("", "Will fix in the next release!", Continue);

    // именно в таком сложном виде приложение студента присылает keylog
    // проверяем, что функция правильно выделяет IP-адрес для дальнейшей работы
    QCOMPARE(pong.readKeylog(" IP:192.168.1.10 State:keylog Time:10:05:22 Data:Keylog!$END"), "Keylog!");
}

void Test_File::test_file_allow()
{
    // проверка, что,  такой файл существует
    QFINDTESTDATA("bin/allow.txt");
}

void Test_File::test_file_prohibit()
{
    // проверка, что,  такой файл существует
    QFINDTESTDATA("bin/prohibit.txt");
}

void Test_File::test_date_true()
{
    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");

    // проверяем, что текущая дата для записи keylog определяется верно
    QCOMPARE(pong.wantKeylog("192.168.1.0"), dateStr);
}

void Test_File::test_date_false()
{
    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");

    // проверяем, что текущая дата для записи keylog определяется верно
    QCOMPARE(pong.wantKeylog("192.168.1.0"), "01-01-1999");
}

void Test_File::test_savelog_true()
{
    // именно в таком сложном виде приложение студента присылает записи логов
    // проверяем, что функция правильно создаёт путь к папке для сохранения логов
    QCOMPARE(pong.saveToLogFile(" IP:192.168.1.10 State:ping Time:10:05:22 CAPTION: ___ COMMAND LINE: Student Online!"), "C:/log/192.168.1.10");
}

void Test_File::test_savelog_false()
{
    // именно в таком сложном виде приложение студента присылает записи логов
    // проверяем, что функция правильно создаёт путь к папке для сохранения логов
    QCOMPARE(pong.saveToLogFile(" IP:192.168.1.10 State:ping Time:10:05:22 CAPTION: ___ COMMAND LINE: Student Online!"), "C:/log/10:05:22");
}

void Test_File::test_show_true()
{
    // проверка, что,  такой файл существует и имеет следующее содержимое
    QString path = QFINDTESTDATA("bin/allow.txt");
    QCOMPARE(pong.showPolitic(path), "google.com");
}

void Test_File::test_show_false()
{
    // проверка, что,  такой файл существует и имеет следующее содержимое
    QString path = QFINDTESTDATA("bin/allow.txt");
    QCOMPARE(pong.showPolitic(path), "yandex.ru");
}

