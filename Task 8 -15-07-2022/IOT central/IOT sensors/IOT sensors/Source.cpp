#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <chrono>
#include <thread>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
void sendMsg(SOCKET& sock, string userInput) {
	char buf[4096];

	if (userInput.size() > 0)		// Make sure the user has typed in something
	{
		// Send the text
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	}
}
void main(int argc, char** argv)
{
	if (argc<2) {
		cout << "Specify On/Off Condtion as argument!\n";
		return;
	}
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cout << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cout << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Do-while loop to send and receive data
	//
	string sensor = argv[1];
	string val = argv[2];
	cout << "Sending sensor:" << sensor << " value:" << val << endl;
	transform(val.begin(), val.end(), val.begin(), ::tolower);
	sendMsg(sock, sensor);
	sendMsg(sock, val);
	//string userInput;


	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
