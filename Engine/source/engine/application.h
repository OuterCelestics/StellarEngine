// std
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"

namespace Engine {
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        void Run();
    private:
        GLFWwindow* m_Window;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}