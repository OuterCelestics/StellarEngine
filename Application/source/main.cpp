#include <engine.h>
#include <iostream>
#include <Windows.h>
#include <glad/glad.h>

using namespace std;

class Source : public Engine::Application
{
public:
    Source() : Application()
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