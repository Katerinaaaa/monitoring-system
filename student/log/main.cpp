#include <QCoreApplication>
#include <QDebug>

#include "pingcontroller.h"
#include <eventsink.h>

# pragma comment(lib, "wbemuuid.lib")


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "Russian");
        HRESULT hres;

        // Step 1: --------------------------------------------------
        // Initialize COM. ------------------------------------------

        hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if (FAILED(hres))
        {
            cout << "Failed to initialize COM library. Error code = 0x"
                << hex << hres << endl;
            return 1;                  // Program has failed.
        }

        // Step 2: --------------------------------------------------
        // Set general COM security levels --------------------------
        // Note: If you are using Windows 2000, you need to specify -
        // the default authentication credentials for a user by using
        // a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
        // parameter of CoInitializeSecurity ------------------------

        hres = CoInitializeSecurity(
            nullptr,
            -1,                          // COM negotiates service
            nullptr,                        // Authentication services
            nullptr,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
            nullptr,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities
            nullptr                         // Reserved
        );


        if (FAILED(hres))
        {
            cout << "Failed to initialize security. Error code = 0x"
                << hex << hres << endl;
            CoUninitialize();
            return 1;                      // Program has failed.
        }

        // Step 3: ---------------------------------------------------
        // Obtain the initial locator to WMI -------------------------

        IWbemLocator* pLoc = nullptr;

        hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

        if (FAILED(hres))
        {
            cout << "Failed to create IWbemLocator object. "
                << "Err code = 0x"
                << hex << hres << endl;
            CoUninitialize();
            return 1;                 // Program has failed.
        }

        // Step 4: ---------------------------------------------------
        // Connect to WMI through the IWbemLocator::ConnectServer method

        IWbemServices* pSvc = nullptr;

        // Connect to the local root\cimv2 namespace
        // and obtain pointer pSvc to make IWbemServices calls.
        hres = pLoc->ConnectServer(
            _bstr_t(L"root\\CIMV2"),
            nullptr,
            nullptr,
            nullptr,
            NULL,
            nullptr,
            nullptr,
            &pSvc
        );

        if (FAILED(hres))
        {
            cout << "Could not connect. Error code = 0x"
                << hex << hres << endl;
            pLoc->Release();
            CoUninitialize();
            return 1;                // Program has failed.
        }

        cout << "Connected to root\\CIMV2 WMI namespace" << endl;


        // Step 5: --------------------------------------------------
        // Set security levels on the proxy -------------------------

        hres = CoSetProxyBlanket(
            pSvc,                        // Indicates the proxy to set
            RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
            RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
            nullptr,                        // Server principal name
            RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
            RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
            nullptr,                        // client identity
            EOAC_NONE                    // proxy capabilities
        );

        if (FAILED(hres))
        {
            cout << "Could not set proxy blanket. Error code = 0x" << hex << hres << endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return 1;               // Program has failed.
        }

        // Step 6: -------------------------------------------------
        // Receive event notifications -----------------------------

        // Use an unsecured apartment for security
        IUnsecuredApartment* pUnsecApp = nullptr;

        hres = CoCreateInstance(CLSID_UnsecuredApartment, nullptr, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);

        EventSink* pSink = new EventSink;
        pSink->AddRef();

        IUnknown* pStubUnk = nullptr;
        pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

        IWbemObjectSink* pStubSink = nullptr;
        pStubUnk->QueryInterface(IID_IWbemObjectSink, (void**)&pStubSink);

        BSTR WQL;
        WQL = (BSTR) L"Select * From __InstanceCreationEvent Within 1 "
            L"Where TargetInstance ISA 'Win32_Process' "
            ;

        // The ExecNotificationQueryAsync method will call
        // The EventQuery::Indicate method when an event occurs
        hres = pSvc->ExecNotificationQueryAsync(
            _bstr_t("WQL"), _bstr_t(WQL), WBEM_FLAG_SEND_STATUS, nullptr, pStubSink);

        // Check for errors.
        if (FAILED(hres))
        {
            printf("ExecNotificationQueryAsync failed with = 0x%X\n", hres);
            pSvc->Release();
            pLoc->Release();
            pUnsecApp->Release();
            pStubUnk->Release();
            pSink->Release();
            pStubSink->Release();
            CoUninitialize();
            return 1;
        }

        // Wait for the event
        cout << "Press any key to terminate" << endl;
        while (!_kbhit()) {}

        hres = pSvc->CancelAsyncCall(pStubSink);


        // Cleanup
        // ========

        pSvc->Release();
        pLoc->Release();
        pUnsecApp->Release();
        pStubUnk->Release();
        pSink->Release();
        pStubSink->Release();
        CoUninitialize();

    return a.exec();
}
