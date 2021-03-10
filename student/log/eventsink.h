#ifndef EVENTSINK_H
#define EVENTSINK_H

#include <iostream>
#include <conio.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <QUdpSocket>

# pragma comment(lib, "wbemuuid.lib")

using namespace std;

class EventSink : public IWbemObjectSink
{
    LONG m_lRef;
    bool bDone;

public:
    EventSink() { m_lRef = 0; }
    ~EventSink() { bDone = true; }

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT
        STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    virtual HRESULT STDMETHODCALLTYPE Indicate(
        LONG lObjectCount,
        IWbemClassObject __RPC_FAR* __RPC_FAR* apObjArray
    );

    virtual HRESULT STDMETHODCALLTYPE SetStatus(
        /* [in] */ LONG lFlags,
        /* [in] */ HRESULT hResult,
        /* [in] */ BSTR strParam,
        /* [in] */ IWbemClassObject __RPC_FAR* pObjParam
    );

    void send(QString array, QString ip);
    void sendLog(wstring array, QString my_state);

    QUdpSocket* socket;
    QString ip_ip = "0.0.0.0";  // необхожимо прописать нужный адрес преподавателя
};

#endif
