#include "tools.h"
#include "Vehicle.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

class Input{
private:
GLFWwindow* window;
Camera*camara;
Camera*camara2;
float prevPlayerX;
float prevPlayerZ;
float prevPlayer2X;
float prevPlayer2Z;


public:
  Vehicle* firstPlayer;
  Vehicle* secondPlayer;
    Input(GLFWwindow* window, Vehicle* firstPlayer, Vehicle* second, Camera* camara, Camera* camara2);
   ~Input();
   void initialiceInput();
};
