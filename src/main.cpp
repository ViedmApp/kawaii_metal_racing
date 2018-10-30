#include "Game.hpp"

int g_gl_width = 1366;
int g_gl_height = 768;
GLFWwindow* g_window = NULL;

int main()
{
	Game* game = new Game();
	
	game -> main_loop();
	
	return 0;
}

