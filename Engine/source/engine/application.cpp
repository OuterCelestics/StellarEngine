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
		glfwSetWindowUserPointer(m_Window, &m_Input);

		api->Initialize();
	}

	Application::~Application()
	{
		api->Terminate();
		glfwTerminate();
		glfwDestroyWindow(m_Window);
	}

	void Application::Run()
	{
		m_Input->BindAction(InputAction::FORWARD, []()
		{
			std::cout << "Forward" << std::endl;
		});

		while (!glfwWindowShouldClose(m_Window)) {
			// process input
			m_Input->processInput(m_Window);

			// render
			api->Render();

			// Swap front and back buffers
			glfwSwapBuffers(m_Window);

			// Poll for and process events
			glfwPollEvents();
		};
	}
}