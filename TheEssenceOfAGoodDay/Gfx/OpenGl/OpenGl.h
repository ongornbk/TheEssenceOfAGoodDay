#pragma once
#include "..\IGraphics.h"

#include <glew-2.1.0/include/GL/glew.h>
#include <glfw-3.2.1.bin.WIN64/include/GLFW/glfw3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment(lib,"glew32.lib")



class OpenGL : public IGraphics
{
public:

	int32 Initialize(const int32 screenWidth, const int32 screenHeight, const HWND hwnd, const uint8 flags) override;

	inline static const GLubyte* GetString(const GLenum name)
	{
		return glGetString(name);
	}

};