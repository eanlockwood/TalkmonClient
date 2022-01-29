#pragma once

#include "StringHelpers.h"
#include <future>
#include <thread>
#include <chrono>
#include <atomic>

#include "App.h"


class OUserInput {

public:

	OUserInput()
	{

	}
	~OUserInput()
	{

	}

protected: 

	string currentString;
	int maxLen;
	std::atomic <bool> ejected;
	std::atomic <bool> paused;


	App* caller;
	void (App::*CallbackFunc)(string);

	void TakeInput();

	std::thread th;

public:

	void InitializeInput(int maxLength, App* Caller, void (App::*callback)(string));

	void FreezeInput();
	void UnFreezeInput();

};