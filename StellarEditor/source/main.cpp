#include <engine.h>
#include <engine/entry.h>
#include <iostream>

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
			reload = new ShaderReload(api->shaderProgram);

			// input bindings
			m_Input->BindAction("escape", [this]()
			{
				m_Window->CaptureMouse(false);
			});

			m_Input->BindAction("forward", [this]()
			{
				m_MainCamera->MoveCamera(FORWARD, speed);
			});

			m_Input->BindAction("backwards", [this]()
			{
				m_MainCamera->MoveCamera(BACKWARD, speed);
			});

			m_Input->BindAction("left", [this]()
			{
				m_MainCamera->MoveCamera(LEFT, speed);
			});

			m_Input->BindAction("right", [this]()
			{
				m_MainCamera->MoveCamera(RIGHT, speed);
			});

			m_Input->BindAction("e", [this]()
				{
				m_MainCamera->MoveCamera(UP, speed);
			});

			m_Input->BindAction("q", [this]()
				{
				m_MainCamera->MoveCamera(DOWN, speed);
			});
		}
	private:
		ShaderReload* reload = nullptr;
		float speed = 0.01f;

		void OnUpdate() override
		{
			try
			{
				reload->CheckForShaderUpdate("shaders/default.vs", "shaders/default.frag");
			}
			catch (const std::exception& e)
			{
				Debug::ErrorLog(e.what(), true);
			}
		}
	};
}

// extern entrypoint core loop
Engine::Application* Engine::CreateApplication()
{
	return new Editor::Source();
}