#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H

#include "opengl_pipeline.h"

namespace Engine 
{
    enum class GraphicsAPIType 
    {
        OpenGL,
        D3D12
    };

    class GraphicsAPIFactory 
    {
    public:
        GraphicsAPI* CreateGraphicsAPI(GraphicsAPIType type) {
            switch (type) {
            case GraphicsAPIType::OpenGL:
                return reinterpret_cast<GraphicsAPI*>(new OpenGLRenderPipeline());
            case GraphicsAPIType::D3D12:
                // Create and return D3D12 implementation when needed
                // return new D3D12RenderPipeline();
                return nullptr;
            default:
                return nullptr;
            }
        }
    };
}

#endif // !GRAPHICS_API_H
