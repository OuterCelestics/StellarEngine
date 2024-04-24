#pragma once
#include <GLFW/glfw3.h>

#include "shaders/shaderClass.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "../components/config/config_loader.h"
#include "../components/camera/camera.h"
#include "textures/textures.h"

namespace Engine
{
	class Pipeline  
	{
	public:
		void Initialize();
		void Render(ConfigLoader* config, float* aspect_ratio, Camera* camera);
		void Terminate();

	public:
		Shaders* shaderProgram = nullptr;

	private:
		VAO* VAO1 = nullptr;
		VBO* VBO1 = nullptr;
		Texture textureID;
	};

}
