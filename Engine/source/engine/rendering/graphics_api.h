#include "../components/config/config_loader.h"
#include "opengl/shaders/shaderClass.h"

using namespace Engine;
//#include "Engine/source/engine/components/config/config_loader.h"
class GraphicsAPI {
public:
    virtual void Initialize() = 0;
    virtual void Render(ConfigLoader* config, float* aspect_ratio) = 0;
    virtual void Terminate() = 0;
    virtual Shaders* getShaderProgram() = 0;
};