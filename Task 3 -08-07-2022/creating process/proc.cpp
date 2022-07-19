#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
int _tmain( int argc, TCHAR *argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // if( argc != 2 )
    // {
    //     printf("Usage: %s [cmdline]\n", argv[0]);
    //     return 0;
    // }

    // Start the child process. 
    if (!CreateProcess(_T("d:\\PSTools\\psexec.exe"),   // No module name (use command line)
        (LPSTR)" -sid notepad.exe",        // Command line
        NULL,
        NULL,
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        std::cout<<"Failed"<<GetLastError();
        return 0;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE);
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    return 0;
}