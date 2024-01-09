#include <engine.h>

class Source : public Engine::Application
{
public:
	Source()
	{
	
	}

	~Source()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Source();
}