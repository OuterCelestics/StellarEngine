#include "opengl_pipeline.h"
#include <iostream>
#include "../components/error/debug.h"
#include "../components/time/time.h"

namespace Engine
{
	void Pipeline::Initialize()
	{
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
		}
		else
		{
			Debug::ErrorLog("Failed to initialize GLAD", true);
		}

		// Enable depth testing & multisampling
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);

		// TODO: Implement shader class and buffer class as static classes
	}

	void Pipeline::Render(ConfigLoader* config, float* aspect_ratio, Camera* camera)
	{
		Time::UpdateTime();

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Pipeline::Terminate()
	{

	}
}