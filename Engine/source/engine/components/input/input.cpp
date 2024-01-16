#include "input.h"

namespace Engine::Input {
	void InputEvent::BindAction(InputAction actionName, std::function<void()> action)
	{
		actionMappings[actionName] = action;
	}

	void InputEvent::processInput(GLFWwindow* window)
	{
		for (const auto& action : actionMappings)
		{
			if (glfwGetKey(window, GetKeyState(action.first)) == GLFW_PRESS) {
				action.second();
			}
		}
	}

	int InputEvent::GetKeyState(InputAction action)
	{
		switch(action)
		{
			case InputAction::FORWARD:
				return GLFW_KEY_W;
			case InputAction::BACKWARD:
				return GLFW_KEY_S;
			case InputAction::LEFT:
				return GLFW_KEY_A;
			case InputAction::RIGHT:
				return GLFW_KEY_D;
			case InputAction::JUMP:
				return GLFW_KEY_SPACE;
		}
	}
}