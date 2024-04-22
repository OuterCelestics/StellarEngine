#include "main.h"

namespace Editor
{
	// Constructor to initialize the application
	Source::Source()
	{
		std::cout << "Stellar Editor is initialized" << std::endl;
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