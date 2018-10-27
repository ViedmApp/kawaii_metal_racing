#include "Input.hpp"
Input::Input(GLFWwindow* window, Vehicle* firstPlayer, Vehicle* secondPlayer)
{
  this->window = window;
  this->firstPlayer = firstPlayer;
  this->secondPlayer=secondPlayer;
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

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
      secondPlayer ->accelerate();
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
      secondPlayer -> turnRight();
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
      secondPlayer -> turnLeft();
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
      secondPlayer -> brake();
}




Input::~Input(){}
