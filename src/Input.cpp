#include "Input.hpp"
Input::Input(GLFWwindow* window, Vehicle* firstPlayer)
{
  this->window = window;
  this->firstPlayer = firstPlayer;
}

void Input::initialiceInput(){
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    firstPlayer ->accelerate();
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    firstPlayer -> turnRight();
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    firstPlayer -> turnLeft();
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    firstPlayer -> brake();
}


Input::~Input(){}
