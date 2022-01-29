#include "./App.h"
#include "OUserInput.h"


#include <string>
#include <thread>




string App::testInit()
{
	lame = false;
	OUserInput* newInput = new OUserInput();
	cout << "Input username: ";
	newInput->InitializeInput(25, this, &App::FuckYou);
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));

	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	} while (!lame); // await username input
	
	delete newInput; 

	return username;
	//once callback, this is where I create socket + connect to server using the username blah blah blah
}

void App::ConnectToServer(SOCKET sock, OUserInput* inputptr)
{
	socket = sock;
	input = inputptr;
}

void App::FuckYou(string kek)
{
	cout << "Hello " + kek << endl;
	username = kek;
	lame = true;
}

void App::sendMsg(string kek)
{
	int stringLength = kek.length() + 2;

	for (int c = 0; c < stringLength; c++)
	{
		cout << "\b";
		cout << "";
		cout << "\b";
	}

	if (socket)
	{
		send(socket, kek.c_str(), kek.length() + 1, 0);

		if (input)
		{
			input->InitializeInput(200, this, &App::sendMsg);
			cout << endl;
			cout << ">>";

		}
	}
}

