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

	void Initialize(const Window* window);
	void Update();

	static Engine* GetInstance();
	ID3D11Device* GetDevice();
	HWND          GetHWND() const noexcept;

	Input* GetInput();

private:

	HWND      hwnd;
	Input*    input;
	DirectX11 dx11;

	ResourceManager resources;
};