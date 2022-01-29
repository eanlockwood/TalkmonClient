#include "OUserInput.h"

#include <Windows.h>
#include <WinUser.h>



void OUserInput::TakeInput()
{
	char keyPressed;
	
	do
	{
		if (!paused)
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
		}
	} while (!ejected.load());
}

void OUserInput::InitializeInput(int maxLength, App* Caller, void (App::*callback)(string))
{
	ejected = false;
	maxLen = maxLength;
	currentString = "";

	if (Caller != nullptr)
	{
		caller = Caller;
		CallbackFunc = callback;
	}
	else {
		
	}

	std::thread t6(&OUserInput::TakeInput, this);

	t6.detach();

	paused = false;

}

void OUserInput::FreezeInput()
{
	int stringLength = currentString.length() + 2;
	paused = true;

	for (int c = 0; c < stringLength; c++)
	{
		cout << "\b";
		cout << "";
		cout << "\b";
	}
}

void OUserInput::UnFreezeInput()
{
	cout << ">>" + currentString;
	paused = false;
}
