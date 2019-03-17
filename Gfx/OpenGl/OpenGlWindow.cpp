#include "OpenGlWindow.h"

int32 OpenGlWindow::Initialize(int32 width, int32 height, const char* title)
{
	if (!glfwInit()) return 1;

	m_window = glfwCreateWindow(width, height, title,NULL,NULL);
	if (!m_window) return 2;

	glfwMakeContextCurrent(m_window);

	return 0;
}

int32 OpenGlWindow::Update()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		glfwSwapBuffers(m_window);
	
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;

}