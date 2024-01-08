#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void setupGLFW(int majorVer, int minorVer) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(int width, int height, const char * title) {
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Error while creating GLFW window" << std::endl;
		glfwTerminate();
	}
	return window;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* setupWindow(int majorVer, int minorVer, int winWidth, int winHeight, const char* winName) {
	setupGLFW(majorVer, minorVer);
	GLFWwindow* window = createWindow(winWidth, winHeight, winName);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error initializing GLAD" << std::endl;
		return NULL;
	}
	glViewport(0, 0, winWidth, winHeight);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	return window;
}

bool getKeyDown(GLFWwindow* window, int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void processInput(GLFWwindow* window) {
	if (getKeyDown(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
}

int main() {
	GLFWwindow* window = setupWindow(4, 6, 1920, 1080, "SharkEngineTest");
	while (!glfwWindowShouldClose(window))
	{
		//Checks input
		processInput(window);
		//Rendering commands
		glClearColor(34.0f / 255.0f, 63.0f / 255.0f, 150.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Swaps the color buffer
		glfwSwapBuffers(window);
		//Checks if events are triggered
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}