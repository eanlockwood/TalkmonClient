// TalkMon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StringHelpers.h"
#include <WS2tcpip.h>
#include <chrono>
#include <thread>
#include <stdlib.h>

#include "App.h"
#include "OUserInput.h"

#pragma comment(lib, "ws2_32.lib")


using namespace StringHelpers;

SOCKET socketG;

string ipAdress = "127.0.0.1";
int port = 5000;
string USERNAME;


BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	char msg[128];

	switch (CEvent)
	{
	case CTRL_C_EVENT:
		MessageBox(NULL,
			L"CTRL+C received!", L"CEvent", MB_OK);
		break;
	case CTRL_BREAK_EVENT:
		MessageBox(NULL,
			L"CTRL+BREAK received!", L"CEvent", MB_OK);
		break;
	case CTRL_CLOSE_EVENT:
		shutdown(socketG, SD_SEND);
		closesocket(socketG);
		WSACleanup();
		break;
	case CTRL_LOGOFF_EVENT:
		shutdown(socketG, SD_SEND);
		closesocket(socketG);
		WSACleanup();
		break;
	case CTRL_SHUTDOWN_EVENT:
		shutdown(socketG, SD_SEND);
		closesocket(socketG);
		WSACleanup();
		break;

	}
	return TRUE;
}

int main()
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE);
	std::cout << "Welcome to TalkMon!\n";

	App* newApp = new App();
	USERNAME = newApp->testInit();
	//string username = StringHelpers::AwaitWordInput(15);
	//std::cout << "\nfuck you " + username << endl;
	
	cout << "back to main";

	system("cls");

	//USERNAME = username;

	//Create socket data
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data); //A function that starts up winsock and copies data to the WSAData structure

	if (wsResult != 0) // 0 = running, if its not 0 we throw and error
	{
		cerr << "\nCannot start winsock, Error # " + wsResult;
		return 0;
	}

	//Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); //AF_INET is a reference to IPv4, for IPv6 just make it AF_INET6, SOCK_STREAM is TCP protocol, SOCK_DGRAM is for udp
	if (sock == INVALID_SOCKET)
	{
		cerr << "Cannot create socket!, error# " << WSAGetLastError();
		WSACleanup(); //Uninitializes WSA 
		return 0;
	}

	socketG = sock;

	//create hint
	sockaddr_in hint; //hint stores data for connecting. the _in refers to IPv4
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port); //htons = host to network short. Some kind of conversion code to grab ipv4 adress from any pc
	inet_pton(AF_INET, ipAdress.c_str(), &hint.sin_addr);//function that loads IP address string to numeric binary form, Takes in the protocal, IP address string as c string, and where to store the data

	//connect
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint)); //connection. Takes in the socket, a socket address which is made from hint and the size of the address. 
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Couldnt connect to socket, Error # " + connResult;
		closesocket(sock);
		WSACleanup();
		return 0;
	}


	string usertext = "/u " + USERNAME;
	int sendResult = send(sock, usertext.c_str(), usertext.size() + 1, 0);
	
	char buff[4090];
	//await string does not work because it pauses the program

	OUserInput* userInput = new OUserInput();
	newApp->ConnectToServer(sock, userInput); //completely throwaway method used to reference sock while im too lazy to 
	cout << ">>";
	userInput->InitializeInput(200, newApp, &App::sendMsg);


	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ZeroMemory(buff, 4090);
		int messageRevieved = recv(sock, buff, 4090, 0);

		if (messageRevieved > 0)
		{
			userInput->FreezeInput();
			cout << buff << endl;
			userInput->UnFreezeInput();
		}

	} while (0 == 0);

	int Iresult = shutdown(sock, SD_SEND);
	closesocket(sock);
	WSACleanup();

	return 0;
}

