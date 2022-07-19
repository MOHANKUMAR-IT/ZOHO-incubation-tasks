#include <iostream>
#include <ws2tcpip.h>
#include <unordered_map>
#include <string>
#pragma comment (lib,"ws2_32.lib")
using namespace std;


void printEnvironmentState(unordered_map<string, string>& sensorStatus) {
    cout << " SENSORS   " << "STATUS \n";
    for (auto it : sensorStatus) {
        cout << it.first << "   " << it.second << endl;
    }
}
void main() {
    unordered_map<string, string> sensorStatus;
    sensorStatus["fan"] = "off";
    sensorStatus["light"] = "off";
    sensorStatus["temperature"] = "0";
    sensorStatus["door"] = "close";
    while (true) {
        //Initialize winsock
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);

        int wsOk = WSAStartup(ver, &wsData);

        if (wsOk != 0) {
            cerr << "Cant Initialize Winsock! Exiting" << endl;
            return;
        }
        else
        {
            cout << "Initialized Winsoc\n";
        }
        //Creating socket

        SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

        if (listening == INVALID_SOCKET) {
            cerr << "Cant Create a Socket! Exiting" << endl;
            return;
        }
        else {
            cout << "....=====Created Socket=====....\n";
        }
        //Binding the socket to IP and port

        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(54000);
        hint.sin_addr.S_un.S_addr = INADDR_ANY;

        bind(listening, (sockaddr*)&hint, sizeof(hint));
        cout << "Bind IP and PORT to SOCKET\n";
        //telling winsock the socket is for listening
        listen(listening, SOMAXCONN);
        cout << "SOCKET in Listening mode\n";
        //wait for a connection
        sockaddr_in client;
        int clientSize = sizeof(client);

        SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Invalid Client Connection" << endl;
            return;
        }

        char host[NI_MAXHOST];  //Clients remote name
        char service[NI_MAXHOST];//port number the client is connected on

        ZeroMemory(host, NI_MAXHOST);
        ZeroMemory(service, NI_MAXHOST);

        if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0)
        {
            cout << host << "Connected on port " << service << endl;
        }
        else
        {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on port " <<
                ntohs(client.sin_port) << endl;
        }
        //close listening socket
        closesocket(listening);
        //while loop:accept and echo message back to client
        char buf[4096];
 
        ZeroMemory(buf, 4096);

        //Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error in rev() Exiting!" << endl;
            break;
        }
        if (bytesReceived == 0)
        {
            cout << "Client Disconnected " << endl;
            break;
        }
        string sensor = string(buf, 0, bytesReceived);

        ZeroMemory(buf, 4096);
        bytesReceived = recv(clientSocket, buf, 4096, 0);

        string value = string(buf, 0, bytesReceived);

        
        if(sensor=="temperature") {

            sensorStatus[sensor] = value;
        }
        else {
            sensorStatus[sensor] = value;
        }


        //Closing the socket
        closesocket(clientSocket);
        //Cleaning up winsock
        WSACleanup();


        printEnvironmentState(sensorStatus);


        //Automation

        if (stof(sensorStatus["temperature"]) > 22) {
            cout << "IOT Central Automation - Turning on Fan due to high temperature\n";
            sensorStatus["fan"] = "on";
        }
        cout << endl << endl;
    }
   
}