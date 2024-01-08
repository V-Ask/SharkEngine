#include <GLFW/glfw3.h>
class InputManager {

public:
	InputManager(GLFWwindow* window) {
		engineWindow = window;
	}
	bool GetKey(int key) {
		return glfwGetKey(engineWindow, key) == GLFW_PRESS;
	}

private:
	GLFWwindow* engineWindow;
};