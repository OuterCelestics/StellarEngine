#pragma once
#include <GLFW/glfw3.h>
#include "../config/config_loader.h" 
#include "../../core.h"

namespace Engine 
{
	class ENGINE_API WindowManager
	{
	private:
		GLFWwindow* m_window;
	public:
		WindowManager(int* width, int* height, float* aspect_ratio, const char* name, ConfigLoader* config);
		static ConfigLoader* m_Config;
		GLFWwindow* getWindow() { return m_window; }
		void CaptureMouse(bool capture);
		void Terminate(ConfigLoader* config);
		void SetMouseCallback(void(*MouseCallback)(GLFWwindow* window, double xposIn, double yposIn));

	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		
		// Store refference to window dimensions coming form the application
		static int* m_window_height;
		static int* m_window_width;
		static float* m_aspect_ratio;
	};
}

