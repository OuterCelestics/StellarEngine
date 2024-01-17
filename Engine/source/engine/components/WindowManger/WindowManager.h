#pragma once
#include <GLFW/glfw3.h>

namespace Engine 
{
	class WindowManager
	{
	public:
		WindowManager(int width, int height, const char* name);
	
		GLFWwindow* m_window;
		GLFWwindow* getWindow() { return m_window; }
		void KillWindow();
	};
}

