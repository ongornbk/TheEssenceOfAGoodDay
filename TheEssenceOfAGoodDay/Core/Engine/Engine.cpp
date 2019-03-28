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

	const float f[4]{};

	dx11.Begin(f[0],f[1],f[2],f[3]);
	dx11.End();
}

void Engine::Initialize(const Window* window)
{
	assert(window);
	hwnd = window->GetHWND();
	input->Initialize(window->GetHinstance(), hwnd, window->GetWidth(), window->GetHeight());
	dx11.Initialize(window->GetWidth(), window->GetHeight(), hwnd, 0);
}

ID3D11Device* Engine::GetDevice()
{
	return dx11.GetDevice();
}

ID3D11DeviceContext* Engine::GetDeviceContext()
{
	return dx11.GetDeviceContext();
}

HWND Engine::GetHWND() const noexcept
{
	return hwnd;
}