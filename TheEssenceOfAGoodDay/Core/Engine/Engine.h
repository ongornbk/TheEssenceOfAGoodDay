#pragma once
#include "..\..\Input\DirectInput8\DirectInput8.h"
#include "ResourceManager.h"
#include "..\Src\Window.h"

class Engine
{
public:

	Engine();
	~Engine();

	void Initialize(const Window* window);
	void Update();

	static Engine* GetInstance();

	Input* GetInput();

private:

	Input* input;

	ResourceManager resources;
};