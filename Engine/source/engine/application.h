// std
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "components/input/input.h"
#include "rendering/layer.h"
#include "components/WindowManger/WindowManager.h"
#include "components/config/config_loader.h"


namespace Engine {

    using namespace Input;

    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        void Run();
    private:
        WindowManager* m_Window = new WindowManager(900, 800, "StellarEngine");
        InputEvent* m_Input = new InputEvent;

        GraphicsAPIFactory factory;
        GraphicsAPI* api = factory.CreateGraphicsAPI(GraphicsAPIType::OpenGL); 
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}