#pragma once

#include "StringHelpers.h"
#include <future>
#include <thread>
#include <chrono>
#include <atomic>

#include "App.h"

class App;

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

	App* caller;
	void (App::*CallbackFunc)(string);

	void TakeInput();

	std::thread th;

public:

	void InitializeInput(string startOfWord, int maxLength, App* Caller, void (App::*callback)(string));

	string FreezeInput();

};