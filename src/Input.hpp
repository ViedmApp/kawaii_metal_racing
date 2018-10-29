#include "tools.h"
#include "Vehicle.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

class Input{
private:
GLFWwindow* window;
Camera*camara;
float prevPlayerX;
float prevPlayerZ;


public:
  Vehicle* firstPlayer;
  Vehicle* secondPlayer;
    Input(GLFWwindow* window, Vehicle* firstPlayer, Vehicle* second, Camera* camara);
   ~Input();
   void initialiceInput();
};
