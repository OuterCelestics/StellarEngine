#include "application.h"

namespace Engine {
	Application::Application()
	{
		std::cout << "Stellar Engine is initialized" << std::endl;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(800, 600, "Stellar Engine", NULL, NULL);
		if (m_Window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		// Make the window's context current
		glfwMakeContextCurrent(m_Window);

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window)) {
			// Render here

			// Swap front and back buffers
			glfwSwapBuffers(m_Window);

			// Poll for and process events
			glfwPollEvents();
		};
	}
}