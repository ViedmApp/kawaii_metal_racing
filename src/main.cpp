#include "Game.hpp"

int g_gl_width = 800;
int g_gl_height = 600;
GLFWwindow* g_window = NULL;

int main()
{
	Game* game = new Game();
	
	game -> main_loop();
	
	glfwTerminate();
	
	return 0;
}

