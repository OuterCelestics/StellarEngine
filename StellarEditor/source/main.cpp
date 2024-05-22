#include <engine.h>
#include <engine/entry.h>
#include <iostream>

#include "utils/shader_reload.h"
#include "editor/editor.h"

namespace Editor
{
	using namespace Utils;

	class Source : public Engine::Application
	{
	public:
		// Constructor to initialize the application
		Source() : Application(new Engine::ConfigLoader("config", "BaseEngine.ini"))
		{
			std::cout << "Editor Application Initialized" << std::endl;
			pushLayer(new Editor(this));
		}

		// Destructor to clean up allocated resources
		~Source()
		{
			std::cout << "Editor Application Terminated" << std::endl;
			popLayer(m_LayerStack->m_Layers[0]);
		}
	};
}

// extern entrypoint core loop
Engine::Application* Engine::CreateApplication()
{
	return new Editor::Source();
}