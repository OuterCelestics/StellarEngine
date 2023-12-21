// std
#include <iostream>

#include "core.h"

namespace Engine {
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application(); // Destructor to clean up allocated resources

        void Run();
    private:
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}