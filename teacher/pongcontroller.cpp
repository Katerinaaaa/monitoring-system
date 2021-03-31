#include "pongcontroller.h"

#include <QTextStream>
#include <QDataStream>
#include <QHostInfo>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QCryptographicHash>

PongController::PongController(QObject *QMLObject) : viewer(QMLObject)
{
    socket = new QUdpSocket(this);
    s_model= new StudentsModel();       // модель подключённых студентов
    hist_model = new HistorsModel();    // модель истории логов студентов

    //очищаем файл для работы с моделью студента
    QFile file("model.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        file.close();
}

//функция входа в систему через пароль
void PongController::passEnter(QString passwd)
{
    QByteArray my_pass = "827ccb0eea8a706c4c34a16891f84e7b";    // пароль лучше поменять

    QByteArray pass;
    pass += passwd;

    QString result = QString(QCryptographicHash::hash((pass),QCryptographicHash::Md5).toHex());

    if (my_pass == result){
        emit passTrue(); // сигнал для Qml об успехе;)
        number = 0;         // обнуляем счётчик
    }
    else {
        number ++;
        if (number < 3){
            emit passFalse();   //сигнал для Qml о провале:(
        }
        else{
            emit exitPass(); //сигнал для Qml что попытки закончились:(
        }
    }
}

void PongController::UdpChat() {
    qDebug() << "Listening...";
    socket = nullptr;

    // Создаём класс для работы с сетью
    socket = new QUdpSocket(this);

    // Все входящие на этот порт сообщения будут
    // поступать в нашу программу
    if(socket->bind(QHostAddress::Any, 555)) {
        qDebug() << "UDPCHAT";
        // При получении данных (сигнал readyRead)
        // вызываем слот, который читает и обрабатывает сообщение
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    }
}

void PongController::wantSnap(QString ip){
    QFile file("snapshot.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        file.close();
    strData("wantSnap", ip);
}

void PongController::sendPolitic(QString filename, QString ip){
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream log(&file);
    log.setCodec("UTF-8");
    QString textfile = file.readAll();
    file.close();

    strPolitic("filename:" + filename + "\r\n" + textfile, ip);
}

void PongController::strPolitic(QString politic, QString ip) {
    QByteArray data; // Массив данных для отправки

    // Последовательно выводим в него байты
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint8(); // Тип сообщения
    out << politic; // Само сообщение

    // Отправляем полученный массив данных студенту
    // на порт указанный в интерфейсе
    socket->writeDatagram(data,
                          QHostAddress(ip),
                          555);
    qDebug() << "Файл отправлен";
}

void PongController::strData(QString message, QString ip) {
    QByteArray data; // Массив данных для отправки

    // Последовательно выводим в него байты
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint8(); // Тип сообщения
    out << message; // Само сообщение

    // Отправляем полученный массив данных студенту
    // на порт указанный в интерфейсе
    socket->writeDatagram(data,
                          QHostAddress(ip),
                          555);
    qDebug() << "Выбрали: " << ip;
    qDebug() << "Отправляем студенту: " << message;
}

void PongController::read() {
    while (socket->hasPendingDatagrams()) {
        // буфер для полученных данных
        QByteArray buf;

        // Устанавливаем массиву размер
        // соответствующий размеру полученного пакета данных
        buf.resize(socket->pendingDatagramSize());
        QHostAddress* address = new QHostAddress();

        // Принимаем данные пришедшие по сети
        socket->readDatagram(buf.data(), buf.size(), address);

        // Разбор полученного пакета
        QDataStream in(&buf, QIODevice::ReadOnly);

        // Получаем тип пакета
        qint8 type = 0;
        in >> type;

        QString str;
        in >> str;

        int x = 0;
        int y = 0;

        //Смотрим какой компьютер и что именно нам прислал

        QString Str0 = "IP:";
        x = str.indexOf(Str0);
        x += Str0.length();
        y = str.indexOf(" State:", x);
        QString addr = str.mid(x, y-x);

        QString Str1 = "State:";
        x = str.indexOf(Str1);
        x += Str1.length();
        y = str.indexOf(" Time:", x);
        QString status = str.mid(x, y-x);

        if (status == "snapshot"){
            qDebug() << "Получил Snapshot";
            readSnap(str);
            break;
        }

        else if (status == "keylog"){
            qDebug() << "Получил Keylog";
            readKeylog(str);
            break;
        }

        QString Str2 = "Time:";
        x = str.indexOf(Str2);
        x += Str2.length();
        y = str.indexOf(" CAPTION", x);
        QString time = str.mid(x, y-x);

        QString Str3 = "CAPTION:";
        x = str.indexOf(Str3);
        x += Str3.length();
        y = str.indexOf(" COMMAND", x);
        QString exe = str.mid(x, y-x);

        QString Str4 = "COMMAND LINE:";
        x = str.indexOf(Str4);
        x += Str4.length();
        y = str.indexOf(".exe", x);
        QString descrip = str.mid(x, y+6-x);

        qDebug() << "Saving...";

        saveToLogFile(str); //сохраняем, для дальнейшей работы с историей

        QStringList strList;
        QStringList colComp;

        QFile file("model.txt");

        //считаем количество компьютеров в сети
        int line = 0;
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
             stream.readLine();
             line++;
        }
        qDebug() << "Компьютеров в сети: " << line;
        file.close();

        //массив со всеми комьютерами для дальнейшей работы
        file.open(QIODevice::ReadOnly);
        while(!file.atEnd())
        {
             colComp << file.readLine();
        }
        file.close();

        //если компьютер с таким же ip появится ещё раз,
        //то счётчик увеличится и добавит итем в модель
        int peremennaya = 0;

        if(line != 0){
            int a = 0;
            file.open(QIODevice::ReadWrite | QIODevice::Text);
            while(!file.atEnd())
            {
                strList << file.readLine();
                qDebug() << strList[a];

                QString my_str = strList[a];

                int x = 0;
                int y = 0;

                QString Str0 = "IP:";
                x = my_str.indexOf(Str0);
                x += Str0.length();
                y = my_str.indexOf(" State:", x);
                QString addr1 = my_str.mid(x, y-x);

                QString Str1 = "State:";
                x = my_str.indexOf(Str1);
                x += Str1.length();
                y = my_str.indexOf(" Time:", x);
                QString status1 = my_str.mid(x, y-x);

                int num_qml = QVariant(a).toInt();

                QString num = QVariant(a).toString();

                QString change_str = " IP:" + addr +
                        " State:" + status1 +
                        " Time:" + time +
                        " CAPTION:" + exe +
                        " COMMAND LINE:" + descrip +
                        " ID:" + num;

                //Если такой делигат уже есть, то меняем его состояние
                if (addr == addr1){
                    QFile file("model.txt");
                    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                        file.close();
                    file.open(QIODevice::WriteOnly);
                    qDebug() << "Уже существует!" << a;
                    peremennaya = 1;

                    /*Добавляем строку и сохраняем содержимое контейнера в тот же файл*/
                    QString str_line = change_str + "\r\n";
                    QTextStream stream(&file);
                    stream.setCodec("UTF-8");

                    int count = 0;
                    foreach(QString s, colComp){

                        if (count == a){
                            colComp[a] = "";
                            colComp[a].insert(0,str_line);
                            foreach(QString s, colComp){
                                stream << s;
                            }
                            break;
                        }
                        else if (count != a)
                            count++;
                    }
                    emit changeDelegate(num_qml, status); // меняем цвет у делегата
                    break;
                }

                else if(a == line-1){
                    QTextStream log(&file);
                    log.setCodec("UTF-8");
                    log << str << " ID:" << ident << "\r\n";
                    break;
                }
                else {
                    a++;
                }
            }
            file.close();
        }

        else{
            file.open(QIODevice::ReadWrite | QIODevice::Text
                      | QIODevice::Append );
            QTextStream log(&file);
            log.setCodec("UTF-8");
            log << str << " ID:" << ident << endl;
            file.close();
        }

        if (peremennaya == 0){
            s_model->addItem(StudentObject(addr, status));
            qDebug() << addr << "IP";
            qDebug() << status << "STATE";

            ident += 1;
        }
        else
            qDebug() << "А такой делегат уже есть, отправляем сигнал в QML";

        // отправляем файл с "опасными" и системными приложениями
        // студенту, для работы с ними.
        /*if (status == "ping"){
            sendPolitic("danger.txt", addr);
            sendPolitic("system.txt", addr);
        }*/
    }
}

void PongController::readSnap(QString str){

    QFile file("snapshot.txt");

    int x = 0;
    int y = 0;

    QString Str1 = "Data:";
    x = str.indexOf(Str1);
    x += Str1.length();
    y = str.indexOf("$END", x);
    QString snapshot = str.mid(x, y-x);

    file.open(QIODevice::WriteOnly |  QIODevice::Text |
              QIODevice::Append );
    QTextStream log(&file);
    log.setCodec("UTF-8");
    log << snapshot << endl;
    file.close();

    emit showSnap(snapshot);

    qDebug() << "Получил Снап";
}

void PongController::readKeylog(QString str){
    int x = 0;
    int y = 0;

    QString Str0 = "IP:";
    x = str.indexOf(Str0);
    x += Str0.length();
    y = str.indexOf(" State:", x);
    QString addr = str.mid(x, y-x);

    QString Str1 = "Data:";
    x = str.indexOf(Str1);
    x += Str1.length();
    y = str.indexOf(" $END:", x);
    QString keylog = str.mid(x, y-x);

    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");

    // Создание папки
    QString path("C:/keylog/" + addr);
    QDir dir;
    dir.mkpath(path);

    QTime time = QTime::currentTime();
    QString timeStr = time.toString("hh-mm-ss");
    QFile file(path + "/" + dateStr + ".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.close();
    file.open(QIODevice::WriteOnly | QIODevice::Text
              | QIODevice::Append );
    QTextStream log(&file);
    log.setCodec("UTF-8");
    log << keylog << endl;
    file.close();

}

void PongController::wantKeylog(QString addr){

    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");

    QString path("C:/keylog/" + addr + "/");

    QFile file(path + dateStr + ".txt");

    file.open(QIODevice::ReadOnly);
    QTextStream log(&file);
    log.setCodec("UTF-8");

    QString keylog = file.readAll();

    file.close();
    emit showKeylog(keylog);
}

void PongController::saveToLogFile(QString str) {
    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");
    qDebug() << dateStr;

    int x = 0;
    int y = 0;

    QString Str0 = "IP:";
    x = str.indexOf(Str0);
    x += Str0.length();
    y = str.indexOf(" State:", x);
    QString addr = str.mid(x, y-x);

    // Создание папки
    QString path("C:/log/" + addr);
    QDir dir;
    dir.mkpath(path);

    QFile file(path + "/" + dateStr + ".txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text
              | QIODevice::Append );
    QTextStream log(&file);
    log.setCodec("UTF-8");
    log << str << endl;
    file.close();
}

QString PongController::myAddress() {

    QString ipAddress;
    QHostInfo info = QHostInfo::fromName( QHostInfo::localHostName() );
    QList<QHostAddress> listAddr= info.addresses();

    for( int i = 0; i < listAddr.size(); i++ ){
        if( listAddr.at(i).protocol() == QAbstractSocket::IPv4Protocol ){
            ipAddress += listAddr.at(i).toString();
          }
    }
    //посылаем сигнал в Qml
    emit ipQml(ipAddress);
    return ipAddress;
}

void PongController::historyIp(QString addr){

    QDate now = QDate::currentDate();
    QString dateStr = now.toString("dd-MM-yyyy");

    QString path("C:/log/" + addr + "/");

    QFile file(path + dateStr + ".txt");

    file.open(QIODevice::ReadOnly);
    QTextStream log(&file);
    log.setCodec("UTF-8");

    QStringList strList;

    QString history;

    int a = 0;
    while(!file.atEnd())
    {
        strList << file.readLine();

        QString my_str = strList[a];

        history += my_str;

        int x = 0;
        int y = 0;

        QString Str1 = "State:";
        x = my_str.indexOf(Str1);
        x += Str1.length();
        y = my_str.indexOf(" Time:", x);
        QString status = my_str.mid(x, y-x);

        QString date = dateStr;

        QString Str2 = "Time:";
        x = my_str.indexOf(Str2);
        x += Str2.length();
        y = my_str.indexOf(" CAPTION", x);
        QString time = my_str.mid(x, y-x);

        QString Str3 = "CAPTION:";
        x = my_str.indexOf(Str3);
        x += Str3.length();
        y = my_str.indexOf(" COMMAND", x);
        QString exe = my_str.mid(x, y-x);

        QString Str4 = "COMMAND LINE:";
        x = my_str.indexOf(Str4);
        x += Str4.length();
        y = my_str.indexOf(".exe", x);
        QString descrip = my_str.mid(x, y+6-x);

        hist_model->addItem(HistorObject(status, time, date, exe, descrip));
        a++;
    }

    file.close();
    emit showHistory();     // показываем историю студента
    emit ipStud(addr);      // и его ip
}

void PongController::addUrl(QString url, QString filename){

    QFile file(filename);
    file.open(QIODevice::WriteOnly |  QIODevice::Text |
              QIODevice::Append );
    QTextStream log(&file);
    log.setCodec("UTF-8");
    log << url << endl;
    file.close();

    showPolitic(filename);
}

void PongController::showPolitic(QString filename){

    QFile file(filename);
    file.open(QIODevice::ReadWrite);    //чтобы создался,если его нет
    QTextStream log(&file);
    log.setCodec("UTF-8");
    QString textfile = file.readAll();
    file.close();

    //обновляем данные в окне QML
    emit qmlPolitic(textfile);
}

void PongController::clearPolitic(QString filename){

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        file.close();
    file.close();

    showPolitic(filename);
}
