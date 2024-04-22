#include "application.h"
#include "iostream"

namespace Engine 
{
	Application::Application()
	{
		std::cout << "Stellar Engine is initialized" << std::endl;

		config = new ConfigLoader("config", "BaseEngine.ini");
		
		m_window_height = config->GetInteger("general", "window_height");
		m_window_width = config->GetInteger("general", "window_width");
		m_aspect_ratio = config->GetFloat("general", "window_aspect_ratio");
		
		m_Window = new WindowManager(&m_window_width, &m_window_height, &m_aspect_ratio, config->getString("general", "window_title").c_str(), config);

		glfwSetWindowUserPointer(m_Window->getWindow(), &m_Input);

		if (config->GetInteger("general", "window_maximized") == GLFW_TRUE) 
		{
			glfwMaximizeWindow(m_Window->getWindow());
		}
		else {
			config->SetInt("general", "window_maximized", 0);
		}
		
		api->Initialize();

		m_Input->BindAction("escape", [this]()
		{
			glfwDestroyWindow(m_Window->getWindow());
			glfwTerminate();
			exit(0);
		});
		
		m_Input->BindAction("forward", [this]()
		{
				m_MainCamera.cameraPos += cameraSpeed * m_MainCamera.cameraFront;
		});
		
		m_Input->BindAction("backwards", [this]()
		{
				m_MainCamera.cameraPos -= cameraSpeed * m_MainCamera.cameraFront;
		});

		m_Input->BindAction("left", [this]()
		{
				m_MainCamera.cameraPos -= glm::normalize(glm::cross(m_MainCamera.cameraFront, m_MainCamera.cameraUp)) * cameraSpeed;
		});
		
		m_Input->BindAction("right", [this]()
		{
				m_MainCamera.cameraPos += glm::normalize(glm::cross(m_MainCamera.cameraFront, m_MainCamera.cameraUp)) * cameraSpeed\;
		});
	}

	// Termination of the application
	Application::~Application()
	{
		api->Terminate();
		m_Window->Terminate(config);
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window->getWindow())) {
			// process input
			m_Input->processInput(m_Window->getWindow());

			// render
			api->Render(config, &m_aspect_ratio, &m_MainCamera);

			// Swap front and back buffers
			glfwSwapBuffers(m_Window->getWindow());

			// Poll for and process events
			glfwPollEvents();
		};
	}
}