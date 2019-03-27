#include "Engine.h"

namespace
{
	static Engine* instance = nullptr;
}

Engine::Engine()
{
	instance = this;
	input = new DirectInput8();
}

Engine::~Engine()
{
	safe_delete(input);
}

Engine* Engine::GetInstance()
{
	assert(instance);
	return instance;
}

Input* Engine::GetInput()
{
	return input;
}

void Engine::Update()
{
	input->Update();
}

void Engine::Initialize(const Window* window)
{
	assert(window);
	input->Initialize(window->GetHinstance(), window->GetHWND(), window->GetWidth(), window->GetHeight());
}