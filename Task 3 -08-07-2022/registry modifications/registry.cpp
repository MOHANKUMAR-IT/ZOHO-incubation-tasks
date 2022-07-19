
#include <tchar.h>
#include <Windows.h>
#include <iostream>
using namespace std;

BOOL CreateRegistryKey(HKEY hKeyParent,LPCWSTR subkey)
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
            KEY_ALL_ACCESS ,
            NULL,
            &hKey,
            &dwDisposition);
    if (Ret != ERROR_SUCCESS)
    {
        printf("Error opening or creating new key\n");
        return FALSE;
    }
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
	LPCSTR t= _T("Software\\Hello");
	if (CreateRegistryKey(HKEY_LOCAL_MACHINE, t))cout << "Created";
	// if (DeleteRegistryKey(HKEY_LOCAL_MACHINE, t))cout << "Deleted";
	return 0;
}