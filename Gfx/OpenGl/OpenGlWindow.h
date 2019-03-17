#pragma once
#include "..\..\Core\Src\Window.h"
#include <glfw-3.2.1.bin.WIN64/include/GLFW/glfw3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")

class OpenGlWindow : public Window
{
	GLFWwindow* m_window{};
public:
	int32 Initialize(int32 width, int32 height, const char* title) override;
	int32 Update() override;
};