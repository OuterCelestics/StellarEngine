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
		Time::GetFramesPerSecond();
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

	int Time::GetFramesPerSecond(float delay)
	{
		Time::framesCount++;
		if (Time::currentTime - Time::previousTime >= delay)
		{
			m_tempFrameCount = framesCount;
			Time::framesCount = 0;
			Time::previousTime = Time::currentTime;
			return m_tempFrameCount;
		}
		return m_tempFrameCount;
	}

}
