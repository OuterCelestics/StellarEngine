#include "../components/config/config_loader.h"
using namespace Engine;
//#include "Engine/source/engine/components/config/config_loader.h"
class GraphicsAPI {
public:
    virtual void Initialize() = 0;
    virtual void Render(ConfigLoader* config) = 0;
    virtual void Terminate() = 0;
};