#include <Windows.h>
#include <iostream>

#define serviceName "My Sample Service"

int main(int argc, char* argv[])
{

	SC_HANDLE handle = ::OpenSCManager(NULL, NULL,
		SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = ::OpenService(handle, (LPCWSTR)serviceName,
		SERVICE_ALL_ACCESS);
	DWORD ctrlCode = 200;
	SERVICE_STATUS lpServiceStatus;
	if (ControlService(hService, ctrlCode, &lpServiceStatus)) {
		std::cout << "Passed";
	}
	else {
		std::cout << "Failed";
	}

	return 0;
}