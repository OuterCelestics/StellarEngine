#pragma once
namespace Engine {
	
	class Time
	{
	public:
		/**
			Holds the time between the frames in seconds
		*/
		static float deltaTime;
		static float lastFrame;
		static double currentTime;
		static double previousTime;
	
		/**
			Holds the frames rendered past second
		*/
		static int framesCount;
	public:
		/**
			Updates all the timings of the engine
		*/
		static void UpdateTime();
		static int GetFramesPerSecond();
		static float  GetFramesPerSecond(float delay);

	private:
		static void UpdateDeltaTime();
		static int m_tempFrameCount;
	};
	
}
