#pragma once
#include "..\..\Core\Src\Window.h"
#include <glew-2.1.0/include/GL/glew.h>
#include <glfw-3.2.1.bin.WIN64/include/GLFW/glfw3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment(lib,"glew32.lib")

class OpenGlWindow : public Window
{
	GLFWwindow* m_window{};
public:
	int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	int32 Update() override;
};