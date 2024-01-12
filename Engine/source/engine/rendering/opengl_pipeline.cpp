#include "opengl_pipeline.h"

namespace Engine
{
	void OpenGLRenderPipeline::Initialize()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
	}

	void OpenGLRenderPipeline::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	}

	void OpenGLRenderPipeline::Terminate()
	{
		
	}
}