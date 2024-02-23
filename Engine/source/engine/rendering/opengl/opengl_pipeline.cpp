#include "opengl_pipeline.h"

namespace Engine
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	void OpenGLRenderPipeline::Initialize()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		shaderProgram = new Shaders("shaders/default.vs", "shaders/default.frag");
		VAO1 = new VAO();

		VBO1 = new VBO(vertices, sizeof(vertices));

		VAO1->Bind();	
		VAO1->LinkVBO(VBO1, 0);
		VAO1->Unbind();
		VBO1->Unbind();
	}

	void OpenGLRenderPipeline::Render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram->Activate();
		VAO1->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void OpenGLRenderPipeline::Terminate()
	{
		
	}
}