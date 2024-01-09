#pragma once
#include <GLFW/glfw3.h>
#include <set>
namespace SharkUtils {
	class InputManager {
	public:
		InputManager(GLFWwindow* window);
		bool GetKey(int key);
		bool GetKeyDown(int key);
		bool GetKeyUp(int key);
	private:
		GLFWwindow* engineWindow;
		std::set<int> pressedKeys;
	};
}