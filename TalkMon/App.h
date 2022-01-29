#pragma once

#include <string>
#include <Windows.h>



class OUserInput;
using namespace std;

class App
{

public: 

	App()
	{

	}
	~App()
	{

	}

protected:

	bool lame;
	string username;
	SOCKET socket;
	OUserInput* input;


public:

	string testInit();
	void ConnectToServer(SOCKET sock, OUserInput* inputptr);

	void FuckYou(string kek);

	void sendMsg(string kek);

};