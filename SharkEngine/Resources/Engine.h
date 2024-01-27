#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
class Engine
{
public:
	GLFWwindow* getWindow();
	void update();
	void terminate();
	Engine();
};

