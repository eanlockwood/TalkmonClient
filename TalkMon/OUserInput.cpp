#include "OUserInput.h"

#include <Windows.h>
#include <WinUser.h>

void OUserInput::TakeInput()
{
	cout << "input username: ";

	char keyPressed;
	
	do
	{

		if (_kbhit())
		{
			keyPressed = _getch();

			if (keyPressed == '\r')
			{
				ejected = true;

				if (caller)
				{
					(caller->*CallbackFunc)(currentString);
				}
			}

			if (keyPressed == '\b')
			{
				if (!currentString.empty())
				{
					cout << "\b";
					cout << " ";
					cout << "\b";

					currentString.pop_back();

				}
			}
			else if (currentString.length() + 1 <= maxLen)
			{
				std::cout << keyPressed;
				currentString.push_back(keyPressed);
			}
		}

	} while (!ejected.load());

	cout << "thread ending...";
}

void OUserInput::InitializeInput(string startOfWord, int maxLength, App* Caller, void (App::*callback)(string))
{
	ejected = false;
	maxLen = maxLength;

	if (Caller != nullptr)
	{
		caller = Caller;
		CallbackFunc = callback;
	}
	else {
		
	}

	th = std::thread(&OUserInput::TakeInput, this);

}

string OUserInput::FreezeInput()
{
	return currentString;
}
