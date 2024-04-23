#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "components/input/input.h"
#include "rendering/opengl_pipeline.h"
#include "components/WindowManger/WindowManager.h"
#include "components/config/config_loader.h"
#include "components/camera/camera.h"


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
        Camera m_MainCamera;

    public:
        Pipeline* api = new Pipeline();
    private:
        int m_window_height;
        int m_window_width;
        float m_aspect_ratio;
        const float cameraSpeed = 0.005f;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}