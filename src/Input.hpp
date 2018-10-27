#include "tools.h"
#include "Vehicle.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input{
private:
GLFWwindow* window;


public:
  Vehicle* firstPlayer;
  Vehicle* secondPlayer;
    Input(GLFWwindow* window, Vehicle* firstPlayer);
   ~Input();
   void initialiceInput();
};
