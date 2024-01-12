#ifndef OPENGL_PIPELINE_H
#define OPENGL_PIPELINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/rendering/graphics_api.h"

namespace Engine
{
	class OpenGLRenderPipeline : GraphicsAPI {
	public:
		void Initialize() override;

		void Render() override;

		void Terminate() override;

	private:


	};

}

#endif // !OPENGL_PIPELINE_H
