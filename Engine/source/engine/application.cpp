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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
	}

	Application::~Application()
	{
		glfwTerminate();
		glfwDestroyWindow(m_Window);
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window)) {
			// Render here
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			// Swap front and back buffers
			glfwSwapBuffers(m_Window);

			// Poll for and process events
			glfwPollEvents();
		};
	}
}