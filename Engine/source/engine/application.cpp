#include "application.h"
#include "iostream"
#include "components/time/Time.h"

namespace Engine 
{
	Application::Application()
	{
		// Load the configuration file
		config = new ConfigLoader("config", "BaseEngine.ini");
		m_Input = new InputEvent("config", "BaseInput.ini");
	    // Set the window properties
		m_window_height = config->GetInteger("general", "window_height");
		m_window_width = config->GetInteger("general", "window_width");
		m_aspect_ratio = config->GetFloat("general", "window_aspect_ratio");
		
		// Initialize the window
		m_Window = new WindowManager(&m_window_width, &m_window_height, &m_aspect_ratio, config->getString("general", "window_title").c_str(), config);
		// Set the input event to the window
		if (config->GetInteger("general", "window_maximized") == GLFW_TRUE)
		{
			glfwMaximizeWindow(m_Window->getWindow());
		}
		else {
			config->SetInt("general", "window_maximized", 0);
		}

		// Initialize the rendering pipeline
		api->Initialize();

		// Set the input event to the window
		glfwSetWindowUserPointer(m_Window->getWindow(), &m_Input);

		// Capture mouse input
		m_Window->CaptureMouse(true);
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
			api->Render(config, &m_aspect_ratio, m_MainCamera);

			// Swap front and back buffers
			glfwSwapBuffers(m_Window->getWindow());

			// Poll for and process events
			glfwPollEvents();
		};
	}
}