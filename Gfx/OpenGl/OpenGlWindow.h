#pragma once
#include "..\..\Core\Src\Window.h"
#include "OpenGL.h"

class OpenGlWindow : public Window
{
	GLFWwindow* m_window{};
public:
	int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	int32 Update() override;
};