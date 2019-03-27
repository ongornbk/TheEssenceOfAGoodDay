#pragma once
#include "..\..\Core\Src\Window.h"
#include "OpenGL.h"

class OpenGlWindow : public Window
{
	GLFWwindow* m_window{};
public:
	int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	int32 Update() override;

	virtual int32 GetWidth() const noexcept override;
	virtual int32 GetHeight() const noexcept override;

protected:

	int32 m_screenWidth;
	int32 m_screenHeight;

};