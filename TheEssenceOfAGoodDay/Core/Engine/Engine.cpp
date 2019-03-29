#include "Engine.h"
#include "..\..\Src\testclass.h"

namespace
{
	static Engine* m_instance{};
	static Testclass* tst{};
}

Engine::Engine()
{
	m_instance = this;
	m_input = new DirectInput8();
}


Engine::~Engine()
{
	safe_delete(m_input);
	safe_release(tst);
}

Engine* Engine::GetInstance()
{
	assert(m_instance);
	return m_instance;
}

Input* Engine::GetInput()
{
	return m_input;
}

void Engine::Update()
{
	m_input->Update();
	tst->Tick();

	const float f[4] = {0.1f,0.2f,0.3f,0.f};

	m_dx11.Begin(f[0],f[1],f[2],f[3]);
	tst->Render();
	m_dx11.End();
}

void Engine::Initialize(Window* window)
{
	assert(window);
	m_window = window;
	m_hwnd = window->GetHWND();
	m_input->Initialize(m_window->GetHinstance(), m_hwnd, m_window->GetWidth(), m_window->GetHeight());
	m_dx11.Initialize(m_window->GetWidth(), m_window->GetHeight(), m_hwnd,GRAPHICS_FLAG_VSYNC);

	tst = new Testclass();
	tst->BeginPlay();
}

ID3D11Device* Engine::GetDevice()
{
	return m_dx11.GetDevice();
}

ID3D11DeviceContext* Engine::GetDeviceContext()
{
	return m_dx11.GetDeviceContext();
}

HWND Engine::GetHWND() const noexcept
{
	return m_hwnd;
}

int32 Engine::GetScreenHeight() const
{
	assert(m_window);
	return m_window->GetHeight();
}

int32 Engine::GetScreenWidth() const
{
	assert(m_window);
	return m_window->GetWidth();
}

float Engine::GetAspectRatio() const
{
	assert(m_window);
	return ((float)m_window->GetWidth() / (float)m_window->GetHeight());
}

void Engine::Exit()
{
	PostQuitMessage(0);
}