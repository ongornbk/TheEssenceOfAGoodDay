#include "OpenGlWindow.h"

int32 OpenGlWindow::Initialize(int32 width, int32 height,String title,bool fullscreen)
{

	if (!glfwInit()) return 1;


	m_window = glfwCreateWindow(width, height, title.c_str(),NULL,NULL);
	if (!m_window)
	{
		glfwTerminate();
		return 2;
	}

	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK) return 3;

	return 0;
}

int32 OpenGlWindow::Update()
{

	int32 result{};

	result = glfwWindowShouldClose(m_window);
	if(!result)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	
		glfwSwapBuffers(m_window);
	
		glfwPollEvents();
	}
	else
	{
		glfwTerminate();
	}
	return result;

}

int32 OpenGlWindow::GetWidth() const noexcept
{
	return m_screenWidth;
}
int32 OpenGlWindow::GetHeight() const noexcept
{
	return m_screenHeight;
}
