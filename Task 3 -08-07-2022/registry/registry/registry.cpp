
#include <tchar.h>
#include <Windows.h>
#include <iostream>
using namespace std;
BOOL CreateRegistryKey(HKEY hKeyParent, LPCWSTR subkey)
{
    DWORD dwDisposition; //It verify new key is created or open existing key
    HKEY  hKey;
    DWORD Ret;
    Ret =
        RegCreateKeyEx(
            hKeyParent,
            subkey,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_WRITE,
            NULL,
            &hKey,
            &dwDisposition);

    if (Ret != ERROR_SUCCESS) 
    {
        printf("Error opening or creating new key\n");
        return FALSE;
    }
    LPCTSTR value = TEXT("SomeKey\\key");
    LPCTSTR data = TEXT("TestData");

    LONG setRes = RegSetValueEx(hKey, value, 0, REG_SZ, (LPBYTE)data, _tcslen(data) * sizeof(TCHAR));
    RegCloseKey(hKey); //close the key

    return TRUE;
}
BOOL DeleteRegistryKey(HKEY hKeyParent, LPCWSTR subkey) {
    DWORD Ret;
    Ret = RegDeleteKey(hKeyParent, subkey);
    if (Ret != ERROR_SUCCESS)
    {
        printf("Error opening or creating new key\n");
        return FALSE;
    }
    
    return TRUE;
}
int main()
{
    LPCWSTR t = L"Software\\Hello\\key";
    if (CreateRegistryKey(HKEY_LOCAL_MACHINE, t))cout << "Created";
   // if (DeleteRegistryKey(HKEY_LOCAL_MACHINE, t))cout << "Deleted";
    return 0;
}