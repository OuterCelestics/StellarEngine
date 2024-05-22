#pragma once

// Engine includes
#include "core.h"
#include "components/input/input.h"
#include "rendering/opengl_pipeline.h"
#include "components/WindowManger/WindowManager.h"
#include "components/config/config_loader.h"
#include "components/camera/camera.h"
#include "layers/layer.h"
#include "layers/layer_stack.h"

namespace Engine 
{
    using namespace Input;

    class ENGINE_API Application 
    {
    public:
        Application(ConfigLoader* config);
        virtual ~Application(); // Destructor to clean up allocated resources
        void Run();
		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
    public: 
        ConfigLoader* config = nullptr;
        Camera* m_MainCamera = new Camera;
        InputEvent* m_Input = nullptr;
        WindowManager* m_Window = nullptr;
        Pipeline* api = new Pipeline();
		LayerStack* m_LayerStack = new LayerStack();

    private:
        int m_window_height;
        int m_window_width;
        float m_aspect_ratio;
        //const float cameraSpeed = 11.5f;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}