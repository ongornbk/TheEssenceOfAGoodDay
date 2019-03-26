#include "Engine.h"

namespace
{
	static Engine* instance = nullptr;
}

Engine::Engine()
{
	input = new DirectInput8();
}

Engine::~Engine()
{
	safe_delete(input);
}

Engine* Engine::GetInstance()
{
	if (!instance) instance = new Engine();

	return instance;
}

Input* Engine::GetInput()
{
	return input;
}