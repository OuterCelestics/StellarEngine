#include "Time.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

	float Time::deltaTime = 0.0f;
	float Time::lastFrame = 0.0f;
	double Time::currentTime = 0.0f;
	double	Time::previousTime = glfwGetTime();
	int Time::framesCount = 0;
	int Time::m_tempFrameCount = 0;

	void Time::UpdateTime()
	{
		Time::UpdateDeltaTime();
	}

	void Time::UpdateDeltaTime()
	{
		Time::currentTime = glfwGetTime();
		deltaTime = (Time::currentTime - Time::lastFrame) * 1000;
		lastFrame = Time::currentTime;
	}

	int Time::GetFramesPerSecond()
	{
		return 1000 / Time::deltaTime;
	}

	float Time::GetFramesPerSecond(float delay)
	{
		Time::framesCount++;
		// Calculate the elapsed time since the last FPS print
		double elapsed = currentTime - previousTime;
		if (elapsed >= delay) 
		{
			float fps = framesCount / elapsed;

			// Reset frame count and update previous time
			framesCount = 0;
			previousTime = currentTime;

			return fps;
		}
		return -1;
	}

}
