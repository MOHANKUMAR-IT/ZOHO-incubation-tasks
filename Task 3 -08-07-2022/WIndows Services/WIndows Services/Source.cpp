#include <Windows.h>
#include <tchar.h>

SERVICE_STATUS        g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

VOID WINAPI ServiceMain(DWORD argc, LPTSTR argv[]);
VOID WINAPI ServiceCtrlHandler(DWORD);
DWORD WINAPI ServiceWorkerThread(LPVOID lpParam);

#define SERVICE_NAME _T("My Sample Service")

int _tmain(DWORD argc, LPTSTR argv[])
{
    OutputDebugString(_T("My Sample Service: Main: Entry"));
    
    SERVICE_TABLE_ENTRY ServiceTable[] =
    {
        {(LPWSTR)SERVICE_NAME, ServiceMain},
        {NULL, NULL}
    };

    if (StartServiceCtrlDispatcher(ServiceTable) == FALSE)
    {
        OutputDebugString(_T("My Sample Service: Main: StartServiceCtrlDispatcher returned error"));
        return GetLastError();
    }

    OutputDebugString(_T("My Sample Service: Main: Exit"));
    return 0;
}


VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv)
{
    DWORD Status = E_FAIL;

    OutputDebugString(_T("My Sample Service: ServiceMain: Entry"));

    g_StatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);

    if (g_StatusHandle == NULL)
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: RegisterServiceCtrlHandler returned error"));
        return;
    }

    // Tell the service controller we are starting
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = NO_ERROR;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;
    g_ServiceStatus.dwWaitHint = 3000;
    if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    /*
     * Perform tasks neccesary to start the service here
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Service Start Operations"));
    
    // Create stop event to wait on later.
    

    // Tell the service controller we are started
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    // Start the thread that will perform the main task of the service
    HANDLE hThread = CreateThread(NULL, 0, ServiceWorkerThread, NULL, 0, NULL);

    OutputDebugString(_T("My Sample Service: ServiceMain: Waiting for Worker Thread to complete"));

    // Wait until our worker thread exits effectively signaling that the service needs to stop
    WaitForSingleObject(hThread, INFINITE);

    OutputDebugString(_T("My Sample Service: ServiceMain: Worker Thread Stop Event signaled"));


    /*
     * Perform any cleanup tasks
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Cleanup Operations"));

    CloseHandle(g_ServiceStopEvent);

    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;

    if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

}


VOID WINAPI ServiceCtrlHandler(DWORD CtrlCode)
{
    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Entry"));

    switch (CtrlCode)
    {
    case SERVICE_CONTROL_STOP:

        OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SERVICE_CONTROL_STOP Request"));

        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
            break;

        /*
         * Perform tasks neccesary to stop the service here
         */

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;

        if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
        {
            OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SetServiceStatus returned error"));
        }

        // This will signal the worker thread to start shutting down
        SetEvent(g_ServiceStopEvent);

        break;

    default:
        break;
    }

    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Exit"));
}


BOOL CALLBACK EnumThreadWndProc(HWND hWnd, LPARAM lParam)
{
    HWND hWndNp = hWnd;
    SendMessageW(hWndNp, WM_SETTEXT, 0, (WPARAM)L"Hello");
    return 0; // ...stop enum
}
VOID createNewProcess() {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(
        NULL, _tcsdup(TEXT("notepad")),
        NULL, NULL, FALSE, 0, NULL, NULL,
        &si, &pi)
        )
    {
        //printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    if (0 == WaitForInputIdle(pi.hProcess, 5000))
    {
        EnumThreadWindows(pi.dwThreadId,
            EnumThreadWndProc, NULL);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


    //system("C:\\windows\\notepad.exe hello.txt");
    //swprintf_s(buf, __T("Ready to launch..., SessionId = %d"), sessionId);
    /*STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));*/

    // if( argc != 2 )
    // {
    //     printf("Usage: %s [cmdline]\n", argv[0]);
    //     return 0;
    // }
    /*si.lpDesktop = (LPWSTR)"winsta0\default";
    si.wShowWindow = SW_SHOW;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.lpTitle = (LPWSTR)"my_process_console";
    si.cb = sizeof(si);*/

    // Start the child process. 
    //if (!CreateProcessAsUser(_T("D:\\a.exe"),   // No module name (use command line)
    //    (LPWSTR)" testing.txt",        // Command line
    //    NULL,
    //    NULL,
    //    FALSE,          // Set handle inheritance to FALSE
    //    0,              // No creation flags
    //    NULL,           // Use parent's environment block
    //    NULL,           // Use parent's starting directory 
    //    &si,            // Pointer to STARTUPINFO structure
    //    &pi)           // Pointer to PROCESS_INFORMATION structure
    //    )
    //{
    //    MessageBox(NULL, _T("Unable to create process."), _T("Error"), MB_OK);
    //    return;
    //}
    //MessageBox(NULL, _T("Unable to create process."), _T("Error"), MB_OK);
    //HWND console_name = FindWindow(NULL, (LPWSTR)"my_process_console");
    //if (console_name) {
    //    ShowWindow(console_name, SW_SHOW);
    //}
    // Wait until child process exits.
    //WaitForSingleObject(pi.hProcess, INFINITE);
    //// Close process and thread handles. 
    //CloseHandle(pi.hProcess);
    //CloseHandle(pi.hThread);
    return;
}

DWORD WINAPI ServiceWorkerThread(LPVOID lpParam)
{
    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL)
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: CreateEvent(g_ServiceStopEvent) returned error"));

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;

        if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
        {
            OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
        }
        return ERROR_INVALID_FUNCTION;
    }
    OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Entry"));

    //  Periodically check if the service has been requested to stop
    while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0)
    {
        /*
         * Perform main service function here
         */
        createNewProcess();
         //  Simulate some work by sleeping
        Sleep(3000);
    }

    OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Exit"));

    return ERROR_SUCCESS;
}

//
// Purpose: 
//   Installs a service in the SCM database
//
// Parameters:
//   None
// 
// Return value:
//   None
//
//VOID SvcInstall()
//{
//    SC_HANDLE schSCManager;
//    SC_HANDLE schService;
//    TCHAR szPath[MAX_PATH];
//
//    if (!GetModuleFileName(NULL, szPath, MAX_PATH))
//    {
//        OutputDebugString(_T("Cannot install service (%d)\n"+ GetLastError()));
//        return;
//    }
//
//    // Get a handle to the SCM database. 
//
//    schSCManager = OpenSCManager(
//        NULL,                    // local computer
//        NULL,                    // ServicesActive database 
//        SC_MANAGER_ALL_ACCESS);  // full access rights 
//
//    if (NULL == schSCManager)
//    {
//        OutputDebugString(_T("OpenSCManager failed (%d)\n"+ GetLastError()));
//        return;
//    }
//
//    // Create the service
//
//    schService = CreateService(
//        schSCManager,              // SCM database 
//        SERVICE_NAME,                   // name of service 
//        SERVICE_NAME,                   // service name to display 
//        SERVICE_ALL_ACCESS,        // desired access 
//        SERVICE_WIN32_OWN_PROCESS, // service type 
//        SERVICE_DEMAND_START,      // start type 
//        SERVICE_ERROR_NORMAL,      // error control type 
//        szPath,                    // path to service's binary 
//        NULL,                      // no load ordering group 
//        NULL,                      // no tag identifier 
//        NULL,                      // no dependencies 
//        NULL,                      // LocalSystem account 
//        NULL);                     // no password 
//
//    if (schService == NULL)
//    {
//        OutputDebugString(_T("CreateService failed (%d)\n", GetLastError()));
//        CloseServiceHandle(schSCManager);
//        return;
//    }
//    else OutputDebugString(_T("Service installed successfully\n"));
//
//    CloseServiceHandle(schService);
//    CloseServiceHandle(schSCManager);
//}