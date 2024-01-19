#include "application.h"

namespace Engine 
{
	Application::Application()
	{

		std::cout << "Stellar Engine is initialized" << std::endl;
		glfwSetWindowUserPointer(m_Window->getWindow(), &m_Input);

		ConfigLoader config("config", "BaseEngine.ini");

		std::map<std::string, std::map<std::string, std::string>> configData;
		configData["general"] = { {"window_width", "500"}, {"window_height", "500"} };
		configData["graphics"] = { {"bUseOpenGL", "yes"} };

		config.writeConfig(configData);

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
			api->Render();

			// Swap front and back buffers
			glfwSwapBuffers(m_Window->getWindow());

			// Poll for and process events
			glfwPollEvents();
		};
	}
}