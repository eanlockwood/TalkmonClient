#include "./App.h"
#include <Windows.h>
#include <thread>

void App::testInit()
{
	lame = false;
	OUserInput* newInput = new OUserInput();
	newInput->InitializeInput("", 25, this, &App::FuckYou);
	

	do
	{

	} while (!lame); // await username input
	
	delete newInput; 

	cout << "out of loop!";

	//once callback, this is where I create socket + connect to server using the username blah blah blah
}

void App::FuckYou(string kek)
{
	cout << "fuck you " + kek << endl;
	lame = true;
}

