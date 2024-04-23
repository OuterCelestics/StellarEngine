#include <engine.h>
#include <engine/entry.h>

#include "utils/shader_reload.h"

namespace Editor
{
	using namespace Utils;

	class Source : public Engine::Application
	{
	public:
		// Constructor to initialize the application
		Source()
		{
			std::cout << "Stellar Editor is initialized" << std::endl;

			// Create a reference to the shader hot reload
			ShaderReload* reload = new ShaderReload(api->shaderProgram);

			// input bindings
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
	};
}

// extern entrypoint core loop
Engine::Application* Engine::CreateApplication()
{
	return new Editor::Source();
}