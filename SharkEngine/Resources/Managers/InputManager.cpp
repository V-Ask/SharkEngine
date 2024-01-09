#include <GLFW/glfw3.h>
#include "InputManager.h"
namespace SharkUtils {
	InputManager::InputManager(GLFWwindow* window) {
		engineWindow = window;
	}
	
	bool InputManager::GetKey(int key) {
		if (glfwGetKey(engineWindow, key) == GLFW_PRESS) {
			pressedKeys.insert(key);
			return true;
		}
		if (pressedKeys.find(key) != pressedKeys.end()) {
			pressedKeys.erase(key);
		}
		return false;
	}

	bool InputManager::GetKeyDown(int key) {
		bool existedBefore = pressedKeys.find(key) != pressedKeys.end();
		bool keyPressed = GetKey(key);
		return existedBefore && keyPressed;
	}

	bool InputManager::GetKeyUp(int key) {
		bool existedBefore = pressedKeys.find(key) != pressedKeys.end();
		bool keyPressed = GetKey(key);
		return existedBefore && !keyPressed;
	}
}
