#include "opengl_pipeline.h"
#include "../../components/camera/camera.h"

namespace Engine
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	void OpenGLRenderPipeline::Initialize()
	{
		// Load gladGLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
		
		glm::vec3 camera = glm::vec3(0, 0, 0);

		// Enable depth test so we have proper ordening
		glEnable(GL_DEPTH_TEST);

		// Section
		shaderProgram = new Shaders;
		shaderProgram->Compile("shaders/default.vs", "shaders/default.frag");

		size_t size = sizeof(vertices) / sizeof(vertices[0]);

		VAO1 = new VAO();
		VBO1 = new VBO();
		VAO1->Bind();	
		VAO1->LinkVBO(VBO1, vertices, size);
		VAO1->Unbind();
		VBO1->Unbind();
		textureID.TextureInit();
	}

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

//	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
//	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	
	void OpenGLRenderPipeline::Render(ConfigLoader* config, float* aspect_ratio)
	{
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// create transformations
		//glm::mat4 model = glm::mat4(1.0f);
		// make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		float radius = 10.0f;
		glm::mat4 projection = glm::mat4(1.0f);

		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);

		//std::cout << "camX: " << camX << "camZ" << camZ << std::endl;

		// Simple projection
		projection = glm::perspective(glm::radians(45.0f), *aspect_ratio, 0.1f, 100.0f);

		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		//Camera projection

		/// Rotate cam 
		//	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		// Walk around cam
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		shaderProgram->Activate();
		shaderProgram->setMat4("projection", projection);
		shaderProgram->setMat4("view", view);
		textureID.Bind();
		VAO1->Bind();

		glActiveTexture(GL_TEXTURE0);
		textureID.Bind();

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 3 == 0)
				angle = glfwGetTime() * 25.0f;

			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shaderProgram->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(0);
	}

	void OpenGLRenderPipeline::Terminate()
	{
		
	}

	Shaders* OpenGLRenderPipeline::getShaderProgram()
	{
		if (shaderProgram != nullptr) 
		{
			std::cout << "Shader program is not null" << std::endl;
			return shaderProgram;
		}
		else
		{
			std::cout << "Shader program is null" << std::endl;
			return nullptr;
		}			
	}
}