#include "Time.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

	float Time::deltaTime = 0.0f;
	float Time::lastFrame = 0.0f;
	float Time::currentFrame = 0.0f;
	
	void Time::UpdateDeltaTime()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		std::cout << deltaTime << std::endl;
	}
}
