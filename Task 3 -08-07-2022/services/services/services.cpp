#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <iostream>


wchar_t ServiceName[] = L"ZOHO_SERVICE";

SERVICE_STATUS          gSvcStatus;
SERVICE_STATUS_HANDLE   gSvcStatusHandle;
HANDLE                  ghSvcStopEvent = NULL;
DWORD                   gSvcCurrentState = SERVICE_START_PENDING;
bool g_SystemShutdown = false;

//static LPWSTR serviceName = L"My example service";
VOID ServiceMain(DWORD argc, LPTSTR argv[]);
BOOL ReportSvcStatus(DWORD state);

VOID _tmain(int argc, LPTSTR argv[])
{
    SERVICE_TABLE_ENTRY dispatchTable[] = {
        {ServiceName,ServiceMain},
        {NULL,NULL}
    };
    if (StartServiceCtrlDispatcher(dispatchTable)) {
        std::cout << "Service Registered";
    }

    else {
        std::cout << "Registration Failed:" << GetLastError();
    }
    return;
}
VOID WINAPI SvcCtrlHandler(DWORD control)
{
    switch (control)
    {
        // Entrie system is shutting down.
    case SERVICE_CONTROL_SHUTDOWN:
        g_SystemShutdown = true;
        // continue...
    // Service is being stopped.
    case SERVICE_CONTROL_STOP:
        ReportSvcStatus(SERVICE_STOP_PENDING);
        SetEvent(ghSvcStopEvent);
        break;
        // Ignoring all other events, but we must always report service status.
    default:
        ReportSvcStatus(gSvcCurrentState);
        break;
    }
    return;
}

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    // Must be called at start.
    gSvcStatusHandle = RegisterServiceCtrlHandler(ServiceName, &SvcCtrlHandler);
    
    // Startup code.
    ReportSvcStatus(SERVICE_START_PENDING);
    ghSvcStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    /* Here initialize service...
    Load configuration, acquire resources etc. */
    ReportSvcStatus(SERVICE_RUNNING);

    /* Main service code
    Loop, do some work, block if nothing to do,
    wait or poll for g_StopEvent... */
    while (WaitForSingleObject(ghSvcStopEvent, 3000) != WAIT_OBJECT_0)
    {
        // This sample service does "BEEP!" every 3 seconds.
        Beep(1000, 100);
    }

    ReportSvcStatus(SERVICE_STOP_PENDING);
    /* Here finalize service...
    Save all unsaved data etc., but do it quickly.
    If g_SystemShutdown, you can skip freeing memory etc. */
    CloseHandle(ghSvcStopEvent);
    ReportSvcStatus(SERVICE_STOPPED);
}



BOOL ReportSvcStatus(DWORD state)
{;
    gSvcCurrentState = state;
    SERVICE_STATUS serviceStatus = {
        SERVICE_WIN32_OWN_PROCESS,
        state,
        state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
        NO_ERROR,
        0,
        0,
        0,
    };
    return SetServiceStatus(gSvcStatusHandle, &serviceStatus);
}

