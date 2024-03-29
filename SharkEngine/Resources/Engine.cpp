#include "Engine.h"
#include <iostream>
#include <vector>
#include "Managers/InputManager.h"
#include "Utils/FileUtils.h"

unsigned int VAO, VBO, EBO, shaderProg;
GLsizei indiceSize = 0;
SharkUtils::InputManager inputManager = NULL;
GLFWwindow* window;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, SharkUtils::InputManager& inputManager);
unsigned int buildShader();
GLFWwindow* setupWindow(int majorVer, int minorVer, int winWidth, int winHeight, const char* winName);

Engine::Engine()
{
	window = setupWindow(4, 6, 800, 600, "SharkEngineTest");
	inputManager = SharkUtils::InputManager(window);


	float vertices[] = {
		//diamond
		0.0f, 0.5f, 0.0f,
		-0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f,
	};

	unsigned int indices[] = {
		//diamond
		0, 1, 2,
		1, 2, 3,
	};
	indiceSize = sizeof(indices);

	shaderProg = buildShader();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLFWwindow* Engine::getWindow()
{
	return window;
}

void Engine::update() {
	//Checks input
	processInput(window, inputManager);
	//Rendering commands
	glClearColor(34.0f / 255.0f, 63.0f / 255.0f, 150.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProg);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);
	//Swaps the color buffer
	glfwSwapBuffers(window);
	//Checks if events are triggered
	glfwPollEvents();
}

void Engine::terminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProg);
	glfwTerminate();
}

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.82f, 0.21f, 222.0f/255.0f, 1.0f);\n"
"}\n\0";

static void setupGLFW(int majorVer, int minorVer) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(int width, int height, const char* title) {
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Error while creating GLFW window" << std::endl;
		glfwTerminate();
	}
	return window;
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

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, SharkUtils::InputManager& inputManager) {
	if (inputManager.GetKeyUp(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
}

unsigned int compileShader(int shaderType, const char* source, char* infoLog) {
	int success;
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int createShaderProgram(std::vector<unsigned int> shaders, char* infoLog) {
	unsigned int shaderProgram = glCreateProgram();
	for (unsigned int& shader : shaders) {
		glAttachShader(shaderProgram, shader);
	}
	glLinkProgram(shaderProgram);
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	for (unsigned int& shader : shaders) {
		glDeleteShader(shader);
	}
	return shaderProgram;
}

unsigned int buildShader() {
	char infoLog[512];
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource, infoLog);

	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, infoLog);

	unsigned int shaderProgram = createShaderProgram({ vertexShader, fragmentShader }, infoLog);

	return shaderProgram;
}