#include <windows.h>
#include <wtsapi32.h>
#include <userenv.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "wtsapi32.lib")
#pragma comment (lib, "userenv.lib")
#pragma comment (lib, "advapi32.lib")
VOID _tmain(int argc,TCHAR argv[]){
     LPWSTR path = L"C:\\Windows\\System32\\notepad.exe";//change the path accordingly
        PROCESS_INFORMATION pi;
        SECURITY_ATTRIBUTES sa;
        STARTUPINFO si;
        DWORD nsid = 1;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        HANDLE htoken;
        TCHAR buf[256];
        DWORD sessionId;
        swprintf_s(buf, __T("Ready to launch..., SessionId = %d"), sessionId);
        sessionId = WTSGetActiveConsoleSessionId();
        WTSQueryUserToken(sessionId, &htoken);
        si.wShowWindow = SW_SHOWNORMAL;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.lpTitle = (LPWSTR)"Zoho Corp";
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
            0x00080000,
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
}