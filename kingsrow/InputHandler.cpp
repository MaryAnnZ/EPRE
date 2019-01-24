#include "InputHandler.h"
#include <iostream>


InputHandler::InputHandler()
{
	esc = false;
	renderMode = false;
	renderLights = false;
	intUp = false;
	intDown = false;
}


InputHandler::~InputHandler()
{
}

void InputHandler::update(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	esc = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	renderMode = glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS;
	renderLights = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
	intUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
	intDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		
}

