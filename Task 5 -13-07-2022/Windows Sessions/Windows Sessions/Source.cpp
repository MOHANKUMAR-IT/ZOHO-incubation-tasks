#include <iostream>

#include <comdef.h>
#include <Wbemidl.h>
#include <wtsapi32.h>	
#include <tchar.h>
#include <Windows.h>
#pragma comment(lib, "Wtsapi32.lib")
HMODULE hLib = LoadLibrary(_T("wtsapi32.dll"));
using namespace std;
int WINAPI main(int argc, char argv[])
{
    WTS_SESSION_INFOA* sessionInfo = new WTS_SESSION_INFOA();
    DWORD count;
    WTSEnumerateSessionsA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfo, &count);
    for (DWORD i = 0; i < count; i++)
    {
        WCHAR* sessionUser;
        DWORD bytes;
        if (!WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionInfo[i].SessionId, WTSUserName, &sessionUser, &bytes))
        {
            std::cout << (L"WTSQuerySessionInformation error: %s\n");
            continue;
        }

        wprintf(L"  * Session %d: \n      user: %s\n      state: %d\n      name: ",
            sessionInfo[i].SessionId,
            sessionUser,
            sessionInfo[i].State);
        std::cout << sessionInfo[i].pWinStationName << endl;
    }
    return 0;
}