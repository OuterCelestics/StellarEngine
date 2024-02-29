#include <map>
#include <functional>
#include <string>
#include <GLFW/glfw3.h>
#include "../config/config_loader.h"

#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

namespace Engine::Input {
	class InputEvent {
	public:
		std::map<std::string, std::function<void()>> actionMappings;

	public:
		InputEvent(std::string folder, std::string file);

		// Bind an action to a key
		void BindAction(std::string action, std::function<void()> function);
		void SetAction(const std::string map, const std::string action, const std::string value);
		void processInput(GLFWwindow* window);
		int GetKeyState(std::string value);
	private:
		ConfigLoader* config = nullptr;
	};
}

#endif // !INPUT_CLASS_H
