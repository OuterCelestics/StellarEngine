#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "components/input/input.h"
#include "rendering/layer.h"
#include "components/WindowManger/WindowManager.h"
#include "components/config/config_loader.h"


namespace Engine 
{
    using namespace Input;

    class ENGINE_API Application 
    {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        void Run();

    public: 
        ConfigLoader* config = nullptr;
    private:
        WindowManager* m_Window = nullptr;
        InputEvent* m_Input = new InputEvent("config", "BaseInput.ini");

        GraphicsAPIFactory factory;
    public:
        GraphicsAPI* api =  factory.CreateGraphicsAPI(GraphicsAPIType::OpenGL);
    private:
        int m_window_height;
        int m_window_width;
        float m_aspect_ratio;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}