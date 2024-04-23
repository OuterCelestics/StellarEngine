#include "main.h"

namespace Editor
{
	// Constructor to initialize the application
	Source::Source()
	{
		std::cout << "Stellar Editor is initialized" << std::endl;

		m_Input->BindAction("escape", [this]()
		{
			m_Window->CaptureMouse(false);
		});

		m_Input->BindAction("forward", [this]()
		{
			m_MainCamera->cameraPos += (0.005f * Engine::Time::deltaTime) * m_MainCamera->cameraFront;
		});

		m_Input->BindAction("backwards", [this]()
		{
			m_MainCamera->cameraPos -= (0.005f * Engine::Time::deltaTime) * m_MainCamera->cameraFront;
		});

		m_Input->BindAction("left", [this]()
		{
			m_MainCamera->cameraPos -= glm::normalize(glm::cross(m_MainCamera->cameraFront, m_MainCamera->cameraUp)) * (0.005f * Engine::Time::deltaTime);	
		});

		m_Input->BindAction("right", [this]()
		{
			m_MainCamera->cameraPos += glm::normalize(glm::cross(m_MainCamera->cameraFront, m_MainCamera->cameraUp)) * (0.005f * Engine::Time::deltaTime);
		});
	}

	// Destructor to clean up allocated resources
	Source::~Source()
	{
		
	}
}

// extern entrypoint core loop
Engine::Application* Engine::CreateApplication()
{
	return new Editor::Source();
}