#include "WindowManager.h"
#include "../camera/camera.h"
#include <stdio.h>

namespace Engine
{
	// Initialise static members
	ConfigLoader* WindowManager::m_Config = nullptr;
	int* WindowManager::m_window_height = 0;
	int* WindowManager::m_window_width = 0;
	float* WindowManager::m_aspect_ratio = 0;

	void error_Callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	WindowManager::WindowManager(int* width, int* height, float* aspect_ratio, const char* name, ConfigLoader* config)
	{
		m_window_height = height;
		m_window_width = width;
		m_aspect_ratio = aspect_ratio;
		glfwSetErrorCallback(error_Callback);
		// Set config
		m_Config = config;
		//Init GLFW
		glfwInit();
		// uncomment for (borderless) fullscreen mode 
		//GLFWmonitor* primary = glfwGetPrimaryMonitor(); 
		//const GLFWvidmode* mode = glfwGetVideoMode(primary);
		//
		//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		//
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core profile
		//Create window
		//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGLgamin", primary, NULL);
		m_window = glfwCreateWindow(*width, *height, name, NULL, NULL);
	
		if (m_window == NULL)
		{
			printf("Failed to create GLFW window \n");
			glfwTerminate();
			//return -1;
		}
		glfwMakeContextCurrent(m_window);

		// set callbacks
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		glfwSwapInterval(0);
	}

	void WindowManager::CaptureMouse(bool capture)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, capture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

	void WindowManager::Terminate(ConfigLoader* config)
	{
		// Write the final window dimentsions to the config file
		config->SetInt("general", "window_height", *m_window_height);
		config->SetInt("general", "window_width", *m_window_width);
		config->SetFloat ("general", "window_aspect_ratio", *m_aspect_ratio);

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void WindowManager::SetMouseCallback(void(*MouseCallback)(GLFWwindow* window, double xposIn, double yposIn))
	{
		glfwSetCursorPosCallback(m_window, MouseCallback);
	}

	// Callbacks
	void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		if (m_Config != nullptr) {
			*m_window_height = height;
			*m_window_width = width;
			*m_aspect_ratio = (float)width / (float)height;

			int maximized = glfwGetWindowAttrib(window, GLFW_MAXIMIZED);

			if (maximized == GLFW_TRUE) {
				m_Config->SetInt("general", "window_maximized", 1);
			} 
			else {
				m_Config->SetInt("general", "window_maximized", 0);
			}
		}
		else {
			printf("Config is null");
			glfwSetWindowAspectRatio(window, width, height);
		}
		glViewport(0, 0, width, height);
	}
}
