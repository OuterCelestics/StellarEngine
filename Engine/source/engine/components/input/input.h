#include <map>
#include <functional>
#include "mapping.h"
#include <string>
#include <GLFW/glfw3.h>

#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

namespace Engine::Input {
	class InputEvent {
	public:
		std::map<InputAction, std::function<void()>> actionMappings;
	public:
		void BindAction(InputAction actionName, std::function<void()> action);
		void processInput(GLFWwindow* window);

	private:
		int GetKeyState(InputAction action);
	};
}

#endif // !INPUT_CLASS_H
