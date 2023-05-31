#include "./App.h"
#include "OUserInput.h"


#include <string>
#include <thread>




string App::testInit()
{
	awaitinginput = false;
	OUserInput* newInput = new OUserInput();
	cout << "Input username: ";
	newInput->InitializeInput(25, this, &App::Hello);
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));

	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	} while (!awaitinginput); // await username input
	
	delete newInput; 

	return username;
	//once callback, this is where I create socket + connect to server using the username
}

void App::ConnectToServer(SOCKET sock, OUserInput* inputptr)
{
	socket = sock;
	input = inputptr;
}

void App::Hello(string user)
{
	cout << "Hello " + user << endl;
	username = user;
	awaitinginput = true;
}

void App::sendMsg(string msg)
{
	int stringLength = msg.length() + 2;

	for (int c = 0; c < stringLength; c++)
	{
		cout << "\b";
		cout << "";
		cout << "\b";
	}

	if (socket)
	{
		send(socket, msg.c_str(), msg.length() + 1, 0);

		if (input)
		{
			input->InitializeInput(200, this, &App::sendMsg);
			cout << endl;
			cout << ">>";

		}
	}
}

