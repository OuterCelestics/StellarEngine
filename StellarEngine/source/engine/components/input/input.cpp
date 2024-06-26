#include "input.h"

namespace Engine::Input {

	InputEvent::InputEvent(std::string folder, std::string file)
	{
		config = new ConfigLoader(folder, file);
	}


	void InputEvent::BindAction(std::string action, std::function<void()> function)
	{
		actionMappings[config->getString("input", action)] = function;
	}

	void InputEvent::SetAction(const std::string map, const std::string action, const std::string value)
	{
		config->SetString(map, action, value);
	}

	void InputEvent::processInput(GLFWwindow* window)
	{
		for (const auto& action : actionMappings) {
			if (glfwGetKey(window, GetKeyState(action.first)) == GLFW_PRESS) {
				action.second();
			}
		}
	}

	int InputEvent::GetKeyState(std::string value)
	{
		if (value == "esc") {
			return GLFW_KEY_ESCAPE;
		}
		else if (value == "q") {
			return GLFW_KEY_Q;
		}
		else if (value == "w") {
			return GLFW_KEY_W;
		}
		else if (value == "e") {
			return GLFW_KEY_E;
		}
		else if (value == "a") {
			return GLFW_KEY_A;
		}
		else if (value == "s") {
			return GLFW_KEY_S;
		}
		else if (value == "d") {
			return GLFW_KEY_D;
		}
		else if (value == "r") {
			return GLFW_KEY_R;
		}
		else if (value == "ctrl") {
			return GLFW_KEY_LEFT_CONTROL;
		}
		else if (value == "shift") {
			return GLFW_KEY_LEFT_SHIFT;
		}
		else if (value == "space") {
			return GLFW_KEY_SPACE;
		}
		else {
			return -1;
		}
	}
}