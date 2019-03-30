#pragma once
#include "..\..\Input\DirectInput8\DirectInput8.h"
#include "ResourceManager.h"
#include "..\Src\Window.h"
#include "..\..\Gfx\DirectX11\DirectX11.h"

class Engine
{
public:

	Engine();
	~Engine();

	void Initialize(Window* window);
	void Update();

	static Engine*       GetInstance();
	ID3D11Device*        GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	int32                GetScreenWidth() const;
	int32                GetScreenHeight() const;
	float                GetAspectRatio() const;
	HWND                 GetHWND() const noexcept;
	DirectX11*           GetGraphics() const noexcept;

	void                 Exit();

	Input* GetInput();

private:

	HWND       m_hwnd;
	Input*     m_input;
	DirectX11* m_dx11;
	Window*    m_window;

	ResourceManager resources;
};