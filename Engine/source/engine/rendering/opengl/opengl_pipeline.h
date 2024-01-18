#ifndef OPENGL_PIPELINE_H
#define OPENGL_PIPELINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../graphics_api.h"
#include "shaders/shaderClass.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

namespace Engine
{
	class OpenGLRenderPipeline : GraphicsAPI 
	{
	public:
		void Initialize() override;

		void Render() override;

		void Terminate() override;

	private:
		Shaders* shaderProgram = nullptr;
		VAO* VAO1 = nullptr;
		VBO* VBO1 = nullptr;
	};

}

#endif // !OPENGL_PIPELINE_H
