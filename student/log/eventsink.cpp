#include "eventsink.h"
#include "pingcontroller.h"

#include <QDataStream>
#include <QHostInfo>
#include <QFile>
#include <QTime>

ULONG EventSink::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}

ULONG EventSink::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if (lRef == 0)
        delete this;
    return lRef;
}

HRESULT EventSink::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink*)this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}


HRESULT EventSink::Indicate(long lObjectCount,
    IWbemClassObject** apObjArray)
{
    socket = new QUdpSocket();

    HRESULT hr = S_OK;
    _variant_t vtProp;
    wchar_t * caption;
    wchar_t * commandLine;

    for (int i = 0; i < lObjectCount; i++)
    {
        hr = apObjArray[i]->Get(_bstr_t(L"TargetInstance"), 0, &vtProp, nullptr, nullptr);
        if (!FAILED(hr))
        {
            IUnknown* str = vtProp;
            hr = str->QueryInterface(IID_IWbemClassObject, reinterpret_cast<void**>(&apObjArray[i]));
            if (SUCCEEDED(hr))
            {
                _variant_t cn;
                hr = apObjArray[i]->Get(L"Caption", 0, &cn, nullptr, nullptr);
                if (SUCCEEDED(hr))
                {
                    if ((cn.vt == VT_NULL) || (cn.vt == VT_EMPTY)){
                        wcout << "Caption : " << ((cn.vt == VT_NULL) ? "NULL" : "EMPTY") << endl;
                    }
                    else
                        if ((cn.vt & VT_ARRAY))
                            wcout << "Caption : " << "Array types not supported (yet)" << endl;
                        else{
                            caption = cn.bstrVal;
                            wstring ws(caption);
                            // your new String
                            string caption(ws.begin(), ws.end());
                            cout << "SEE !!! Caption  !!! " << caption << endl;
                        }
                }
                VariantClear(&cn);

                hr = apObjArray[i]->Get(L"CommandLine", 0, &cn, nullptr, nullptr);
                if (SUCCEEDED(hr))
                {
                    if ((cn.vt == VT_NULL) || (cn.vt == VT_EMPTY)){
                        wcout << "CommandLine : " << ((cn.vt == VT_NULL) ? "NULL" : "EMPTY") << endl;
                    }
                    else
                        if ((cn.vt & VT_ARRAY))
                            wcout << "CommandLine : " << "Array types not supported (yet)" << endl;
                        else{

                            commandLine = cn.bstrVal;
                            wstring ws(commandLine);
                            // your new String
                            string commandLine(ws.begin(), ws.end());
                            cout << "SEE !!!  CommandLine !!! " << commandLine << endl;
                        }
                }
                VariantClear(&cn);
            }
        }
        VariantClear(&vtProp);

        string str1 = " CAPTION:";
        wstring wStr1(std::begin(str1), std::end(str1));

        string str2 = " COMMAND LINE:";
        wstring wStr2(std::begin(str2), std::end(str2));

        wstring array;
        array.append(wStr1);
        array.append(caption);

        wstring ws(caption);
        // your new String
        string cap(ws.begin(), ws.end());   // название исполняемого файла

        //Считываем файл с системными службами
        QFile serv("system.txt");
        serv.open(QIODevice::ReadOnly);
        QTextStream l(&serv);
        l.setCodec("UTF-8");

        //считываем файл со службами построчно
        QStringList list;

        // по умолчанию действие отправлять нужно
        bool Send = true;
        int a = 0;
        while(!serv.atEnd())
        {
            list << serv.readLine();
            QString services = list[a]; // берём по одной строке
            // названия в файле перечислены через Enter, убираем их
            services.remove(QString("\r\n"), Qt::CaseInsensitive);
            // преобазование string в QString
            QString new_cap = QString::fromStdString(cap);

            // если exe относится к системной службе
            if(new_cap == services){
                qDebug() << "Системная служба" << new_cap;
                Send = false;           // говорим, что не будем отправлять действие
                break;                  // прекращаем считывание файла
            }
            a++;
        }
        serv.close();

        if (Send == false){ // если служба системная
            break;          // выходим из функции без отправки действия
        }

        QString my_state;
        my_state = "warning"; // по умолчанию, действие не опасное

        //Считываем файл с "опасными" действиями
        QFile file("danger.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream log(&file);
        log.setCodec("UTF-8");

        //считываем файл с действиями построчно
        QStringList strList;

        int s = 0;
        while(!file.atEnd())
        {
            strList << file.readLine();
            QString action = strList[s]; // берём по одной строке
            // названия в файле перечислены через Enter, убираем их
            action.remove(QString("\r\n"), Qt::CaseInsensitive);
            // преобазование string в QString
            QString new_cap = QString::fromStdString(cap);

            // если совершаемое действие относится к опасным
            if(new_cap == action){
                qDebug() << "ОПАСНО!!!";
                my_state = "danger";    // назначаем ему статус
                break;                  // прекращаем считывание файла
            }
            s++;
        }

        file.close();

        array.append(wStr2);
        array.append(commandLine);

        wcout << "SEE !!!  OUR ARR !!! " << array << endl;

        sendLog(array, my_state);
    }

    return WBEM_S_NO_ERROR;
}

void EventSink::sendLog(wstring array, QString my_state){

    QFile file ("myfile.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        file.close();

    socket = new QUdpSocket();

    QString ipAddress;
    QHostInfo info = QHostInfo::fromName( QHostInfo::localHostName() );
    QList<QHostAddress> listAddr= info.addresses();

    for( int i = 0; i < listAddr.size(); i ++ ){
        if( listAddr.at(i).protocol() == QAbstractSocket::IPv4Protocol ){
            ipAddress += listAddr.at(i).toString();
          }
    }

    string smth = " IP:";
    wstring final(std::begin(smth), std::end(smth));

    string my_ip = ipAddress.toStdString();
    wstring ip(std::begin(my_ip), std::end(my_ip));

    final.append(ip);

    string status = " State:";
    wstring my_status(std::begin(status), std::end(status));

    final.append(my_status);

    string x = my_state.toStdString();
    wstring my_stat(std::begin(x), std::end(x));

    final.append(my_stat);

    string time = " Time:";
    wstring my_time(std::begin(time), std::end(time));

    final.append(my_time);

    QTime now = QTime::currentTime();
    QString timeStr = now.toString("hh:mm:ss");

    // Записываем входящие сообщения в файл
    final.append(timeStr.toStdWString());

    final.append(array);

    qDebug() << "FOLLOWING MESSAGE !!!!!!! " << final;

    file.open(QIODevice::WriteOnly | QIODevice::Text
              | QIODevice::Append );
    QTextStream log(&file);
    log.setCodec("UTF-8");
    log << final;
    file.close();

    file.open(QIODevice::ReadOnly);
    QString data =  file.readAll();
    file.close();

    send(data, ip_ip);
}

void EventSink::send(QString array, QString ip){

    // Полный пакет данных будет в массиве data
    QByteArray data; // Массив данных для отправки

    // Последовательно выводим в него байты
    QDataStream out(&data, QIODevice::WriteOnly);
    out << qint8(); // Тип сообщения
    out << array; // Само сообщение

    // Отправляем полученный массив данных преподавателю
    // на порт указанный в интерфейсе

    // отправляем сообщение преподавателю
    socket->writeDatagram(data,
                          QHostAddress(ip),
                          555);
}

HRESULT EventSink::SetStatus(
    /* [in] */ LONG lFlags,
    /* [in] */ HRESULT hResult,
    /* [in] */ BSTR strParam,
    /* [in] */ IWbemClassObject __RPC_FAR* pObjParam
)
{
    if (lFlags == WBEM_STATUS_COMPLETE)
    {
        printf("Call complete. hResult = 0x%X\n", hResult);
    }
    else if (lFlags == WBEM_STATUS_PROGRESS)
    {
        printf("Call in progress.\n");
    }

    return WBEM_S_NO_ERROR;
}
