#include "./StringHelpers.h"

string StringHelpers::AwaitWordInput(int inputLength)
{
	string word;
	char pressed;

	while (0 == 0)
	{
		pressed = _getch();

		if (pressed == '\r')
		{
			goto ReturnWord;
		}

		if (pressed == '\b')
		{
			if (!word.empty())
			{
				cout << "\b";
				cout << " ";
				cout << "\b";

				word.pop_back();

			}
		}
		else if (word.length() + 1 <= inputLength)
		{
			std::cout << pressed;
			word.push_back(pressed);
		}
	}

ReturnWord:
	
	cout << "\nEnter pressed";

	return word;
}
