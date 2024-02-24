#include "application.h"

namespace Engine 
{
	Application::Application()
	{
		std::cout << "Stellar Engine is initialized" << std::endl;

		config = new ConfigLoader("config", "BaseEngine.ini");
		m_Window = new WindowManager(config->GetInteger("general", "window_width"), config->GetInteger("general", "window_height"), config->getString("general", "window_title").c_str());
		
		glfwSetWindowUserPointer(m_Window->getWindow(), &m_Input);
		api->Initialize();
	}

	// Termination of the application
	Application::~Application()
	{
		api->Terminate();
		m_Window->Terminate();
	}

	void Application::Run()
	{
		m_Input->BindAction(InputAction::FORWARD, []()
		{
			std::cout << "Forward" << std::endl;
		});

		while (!glfwWindowShouldClose(m_Window->getWindow())) {
			// process input
			m_Input->processInput(m_Window->getWindow());

			// render
			api->Render(config);

			// Swap front and back buffers
			glfwSwapBuffers(m_Window->getWindow());

			// Poll for and process events
			glfwPollEvents();
		};
	}
}