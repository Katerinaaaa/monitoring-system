#ifndef TEST_FILE_H
#define TEST_FILE_H
#include "pongcontroller.h"
#include <QObject>

class Test_File : public QObject
{
    Q_OBJECT
public:
    explicit Test_File(QObject *parent = nullptr);

    PongController pong;    // основной класс приложения

private slots: // должны быть приватными
    void test_ip_true();
    void test_ip_false();

    void test_pass_true();
    void test_pass_false();

    void test_politic_true();
    void test_politic_false();

    void test_message_true();
    void test_message_false();

    void test_snap_true();
    void test_snap_false();

    void test_keylog_true();
    void test_keylog_false();

    void test_file_allow();
    void test_file_prohibit();

    void test_date_true();
    void test_date_false();

    void test_savelog_true();
    void test_savelog_false();

    void test_show_true();
    void test_show_false();

};

#endif // TEST_FILE_H
