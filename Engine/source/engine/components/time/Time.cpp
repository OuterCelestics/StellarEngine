#include "Time.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

	float Time::deltaTime = 0.0f;
	float Time::lastFrame = 0.0f;
	double Time::currentTime = 0.0f;
	double	Time::previousTime = glfwGetTime();
	int Time::framesCount = 0;

	void Time::UpdateTime()
	{
		Time::UpdateDeltaTime();
		Time::GetFramesPerSecond();
	}

	void Time::UpdateDeltaTime()
	{
		Time::currentTime = glfwGetTime();
		deltaTime = (Time::currentTime - Time::lastFrame) * 1000;
		lastFrame = Time::currentTime;
	}

	void Time::GetFramesPerSecond()
	{
		Time::framesCount++;
		if (Time::currentTime - Time::previousTime >= 1.0)
		{
			std::cout << framesCount << std::endl;
			Time::framesCount = 0;
			Time::previousTime = Time::currentTime;
			
		}
	}
}
