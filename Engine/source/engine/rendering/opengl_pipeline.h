#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm.hpp" 
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "shaders/shaderClass.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "../components/config/config_loader.h"
#include "../components/camera/camera.h"
#include "../components/time/time.h"

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
