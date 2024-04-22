#pragma once
namespace Engine {
	
	class Time
	{
	public:
		static float deltaTime;
		static float lastFrame;
		static float currentFrame;
	
	public:
		static void UpdateDeltaTime();
	};
	
}
