#pragma once
#include "..\..\Input\DirectInput8\DirectInput8.h"

class Engine
{
public:

	Engine();
	~Engine();

	static Engine* GetInstance();

	Input* GetInput();

private:

	Input* input;
};