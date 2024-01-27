#include "Engine.h"

int main() {
	Engine engine;
	GLFWwindow* window = engine.getWindow();
	while (!glfwWindowShouldClose(window)) {
		engine.update();
	}
	engine.terminate();
}