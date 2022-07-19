#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

int main(int argc, char** argv)
{
    HRESULT hres;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);

    /*HRESULT CoInitializeEx(
        [in, optional] LPVOID pvReserved,
        [in]           DWORD  dwCoInit COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED
    );*/

    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x"
            << hex << hres << endl;
        return 1;                  // Program has failed.
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------

    hres = CoInitializeSecurity(
        NULL,                          //The access permissions that a server will use to receive calls
        -1,                          // COM authentication  If this parameter is 0, no authentication services will be registered and the server cannot receive secure calls. A value of -1 tells COM to choose which authentication services to register, and if this is the case, the asAuthSvc parameter must be NULL
        NULL,                        // Authentication services  An array of authentication services that a server is willing to use to receive a call.
        NULL,                        // Reserved This parameter is reserved and must be NULL.
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info A pointer to SOLE_AUTHENTICATION_LIST, which is an array of SOLE_AUTHENTICATION_INFO structures. This list indicates the information for each authentication service that a client can use to call a server.
        EOAC_NONE,                   // Additional capabilities Additional capabilities of the client or server, specified by setting one or more EOLE_AUTHENTICATION_CAPABILITIES value
        NULL                         // Reserved This parameter is reserved and must be NULL.
    );

    /*HRESULT CoInitializeSecurity(
        [in, optional] PSECURITY_DESCRIPTOR        pSecDesc,
        [in]           LONG                        cAuthSvc,
        [in, optional] SOLE_AUTHENTICATION_SERVICE * asAuthSvc,
        [in, optional] void* pReserved1,
        [in]           DWORD                       dwAuthnLevel,
        [in]           DWORD                       dwImpLevel,
        [in, optional] void* pAuthList,
        [in]           DWORD                       dwCapabilities,
        [in, optional] void* pReserved3
    );*/

    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return 1;                    // Program has failed.
    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

   /* HRESULT CoCreateInstance(
        [in]  REFCLSID  rclsid,   The CLSID associated with the data and code that will be used to create the object.
        [in]  LPUNKNOWN pUnkOuter,  If NULL, indicates that the object is not being created as part of an aggregate.If non-NULL, pointer to the aggregate object's IUnknown interface
        [in]  DWORD     dwClsContext,  Context in which the code that manages the newly created object will run.
        [in]  REFIID    riid,  A reference to the identifier of the interface to be used to communicate with the object.
        [out] LPVOID * ppv   Address of pointer variable that receives the interface pointer requested in riid. 
    );*/

    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object."
            << " Err code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return 1;                 // Program has failed.
    }

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    IWbemServices* pSvc = NULL;

    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
        NULL,                    // User name. NULL = current user
        NULL,                    // User password. NULL = current
        0,                       // Locale. NULL indicates current
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos)
        0,                       // Context object 
        &pSvc                    // pointer to IWbemServices proxy
    );

    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return 1;                // Program has failed.
    }

    cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );//Sets the authentication information that will be used to make calls on the specified proxy

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the name of the operating system
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_BIOS"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for processes failed. "
            << "Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }
    else
    {
        IWbemClassObject* pclsObj;
        ULONG uReturn = 0;

        while (pEnumerator)
        {
            hres = pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn)
            {
                break;
            }

            VARIANT vtProp;

            // Get the value of the Name property
            hres = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
            wcout << "Service Tag : " << vtProp.bstrVal << endl;
            VariantClear(&vtProp);

            pclsObj->Release();
            pclsObj = NULL;
        }

    }
    // Cleanup
    // ========

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;   // Program successfully completed.

}
