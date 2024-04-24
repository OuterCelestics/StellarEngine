#pragma once

// c++ includes
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Engine includes
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
        virtual void OnUpdate() = 0;
    public: 
        ConfigLoader* config = nullptr;
        Camera* m_MainCamera = new Camera;
        InputEvent* m_Input = nullptr;
        WindowManager* m_Window = nullptr;
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