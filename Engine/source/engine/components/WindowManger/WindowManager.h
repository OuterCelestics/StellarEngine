#pragma once
#include <GLFW/glfw3.h>
#include "../config/config_loader.h" 

namespace Engine 
{
	class WindowManager
	{
	private:
		GLFWwindow* m_window;
		static ConfigLoader* m_config;

	public:
		WindowManager(int width, int height, const char* name, ConfigLoader* config);
	
		GLFWwindow* getWindow() { return m_window; }
		void Terminate();

	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
}

