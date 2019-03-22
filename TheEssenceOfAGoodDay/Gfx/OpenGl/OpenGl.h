#pragma once
#include "..\..\Core\Src\String.h"

#include <glew-2.1.0/include/GL/glew.h>
#include <glfw-3.2.1.bin.WIN64/include/GLFW/glfw3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment(lib,"glew32.lib")



class OpenGL
{
public:
	inline static const GLubyte* GetString(GLenum name)
	{
		return glGetString(name);
	}

};