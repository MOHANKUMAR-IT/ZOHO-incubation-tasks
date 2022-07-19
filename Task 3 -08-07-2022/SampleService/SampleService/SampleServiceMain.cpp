#include <windows.h>
#include <wtsapi32.h>
#include <userenv.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "wtsapi32.lib")
#pragma comment (lib, "userenv.lib")
#pragma comment (lib, "advapi32.lib")

SERVICE_STATUS        g_ServiceStatus = {0};
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler (DWORD);
DWORD ServiceWorkerThread ();

#define SERVICE_NAME  _T("My Sample Service")

int _tmain (int argc, TCHAR *argv[])
{
    OutputDebugString(_T("My Sample Service: Main: Entry"));

    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL, NULL}
    };

    if (StartServiceCtrlDispatcher (ServiceTable) == FALSE)
    {
       OutputDebugString(_T("My Sample Service: Main: StartServiceCtrlDispatcher returned error"));
       return GetLastError ();
    }

    OutputDebugString(_T("My Sample Service: Main: Exit"));
    return 0;
}


VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv)
{
    DWORD Status = E_FAIL;

    OutputDebugString(_T("My Sample Service: ServiceMain: Entry"));

    g_StatusHandle = RegisterServiceCtrlHandler (SERVICE_NAME, ServiceCtrlHandler);

    if (g_StatusHandle == NULL) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: RegisterServiceCtrlHandler returned error"));
        goto EXIT;
    }

    // Tell the service controller we are starting
    ZeroMemory (&g_ServiceStatus, sizeof (g_ServiceStatus));
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0 | 200;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    /* 
     * Perform tasks neccesary to start the service here
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Service Start Operations"));

    // Create stop event to wait on later.
    g_ServiceStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: CreateEvent(g_ServiceStopEvent) returned error"));

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
	    {
		    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
	    }
        goto EXIT; 
    }    

    // Tell the service controller we are started
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | 200;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
	    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    // Start the thread that will perform the main task of the service
    //HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
    ServiceWorkerThread();
    OutputDebugString(_T("My Sample Service: ServiceMain: Waiting for Worker Thread to complete"));

    // Wait until our worker thread exits effectively signaling that the service needs to stop
    //WaitForSingleObject (hThread, INFINITE);
    
    OutputDebugString(_T("My Sample Service: ServiceMain: Worker Thread Stop Event signaled"));
    
    
    /* 
     * Perform any cleanup tasks
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Cleanup Operations"));

    CloseHandle (g_ServiceStopEvent);

    g_ServiceStatus.dwControlsAccepted = 0 | 200;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
	    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
    
    EXIT:
    OutputDebugString(_T("My Sample Service: ServiceMain: Exit"));

    return;
}
int DisplayResourceNAMessageBox()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"Resource not available\nDo you want to try again?",
        (LPCWSTR)L"Account Details",
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        break;
    case IDTRYAGAIN:
        // TODO: add code
        break;
    case IDCONTINUE:
        // TODO: add code
        break;
    }

    return msgboxID;
}

VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Entry"));

    switch (CtrlCode) 
	{
     case SERVICE_CONTROL_STOP :

        OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SERVICE_CONTROL_STOP Request"));

        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
           break;

        /* 
         * Perform tasks neccesary to stop the service here 
         */
        
        g_ServiceStatus.dwControlsAccepted = 0 | 200;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
		{
			OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SetServiceStatus returned error"));
		}

        // This will signal the worker thread to start shutting down
        SetEvent (g_ServiceStopEvent);

        break;
     case 200:
         DisplayResourceNAMessageBox();
     default:
         break;
    }

    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Exit"));
}


DWORD ServiceWorkerThread ()
{
    OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Entry"));

    //  Periodically check if the service has been requested to stop
    while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0)
    {        
        /* 
         * Perform main service function here
         */
        LPWSTR path = L"C:\\Windows\\System32\\notepad.exe";
        PROCESS_INFORMATION pi;
        SECURITY_ATTRIBUTES sa;
        STARTUPINFO si;
        DWORD nsid = 1;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        HANDLE htoken;
        TCHAR buf[256];
        DWORD sessionId;

        sessionId = WTSGetActiveConsoleSessionId();
        WTSQueryUserToken(sessionId, &htoken);
        si.wShowWindow = SW_SHOWNORMAL;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.lpDesktop = (LPWSTR)"winsta0\\default";
        sa.bInheritHandle = 0;
        sa.nLength = sizeof(sa);
        void* lpEnvironment = NULL;
        HANDLE phtoken;
        SECURITY_ATTRIBUTES Security1;
        SECURITY_ATTRIBUTES Security2;
        DuplicateTokenEx(htoken, TOKEN_ASSIGN_PRIMARY | TOKEN_ALL_ACCESS, 0, SecurityImpersonation, TokenPrimary, &phtoken);
        CreateEnvironmentBlock(&lpEnvironment, phtoken, FALSE);
        if (CreateProcessAsUser(phtoken, 
            NULL, 
            path,
            &Security1, &Security2,
            FALSE, 
            CREATE_NEW_CONSOLE | EXTENDED_STARTUPINFO_PRESENT,
            &lpEnvironment,
            NULL,
            &si,
            &pi))
        {
            /* Process has been created; work with the process and wait for it to
            terminate. */
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }

        CloseHandle(htoken);
        //  Simulate some work by sleeping
        Sleep(3000);
    }

    OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Exit"));
    return ERROR_SUCCESS;
}