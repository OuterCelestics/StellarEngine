#include <engine.h>

class Source : public Engine::Application
{
public:
	
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}