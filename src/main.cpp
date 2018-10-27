/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| This demo uses the Assimp library to load a mesh from a file, and supports   |
| many formats. The library is VERY big and complex. It's much easier to write |
| a simple Wavefront .obj loader. I have code for this in other demos. However,|
| Assimp will load animated meshes, which will we need to use later, so this   |
| demo is a starting point before doing skinning animation                     |
\******************************************************************************/
#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "GLDebugDrawer.hpp"
#include "Camera.hpp"

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "gl_utils.h"
#include "tools.h"
#include "Vehicle.hpp"
#include "GLDebugDrawer.hpp"
#include <bullet/btBulletDynamicsCommon.h>
#include "Input.hpp"

#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"


int g_gl_width = 800;
int g_gl_height = 600;
GLFWwindow* g_window = NULL;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


// camera
glm::vec3 cameraPos   = glm::vec3(3.0f, 5.0f, 30.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraLook = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  g_gl_width / 2.0;
float lastY =  g_gl_height / 2.0;
float fov   =  45.0f;
Camera* camara=new Camera(cameraPos,cameraFront,cameraUp,fov,pitch,yaw,g_gl_width,g_gl_height);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

btRigidBody* bodyBall;
btRigidBody* bodyBall2;

btDiscreteDynamicsWorld* dynamicsWorld;
Vehicle *ball;
Vehicle *ball2;


int main(int argc, char* argv[]){
	restart_gl_log ();
	start_gl ();
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
	glClearColor (0.2, 0.2, 0.2, 1.0); // grey background to help spot mistakes
	glViewport (0, 0, g_gl_width, g_gl_height);

    glfwSetFramebufferSizeCallback(g_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(g_window, mouse_callback);
    glfwSetScrollCallback(g_window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /*-------------------------------CREATE SHADERS-------------------------------*/
	GLuint shader_programme = create_programme_from_files (
		VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE
	);
    glm::mat4 projection = camara->getPerspectiva();
    glm::mat4 view = camara->getViewMatrix();

	int view_mat_location = glGetUniformLocation (shader_programme, "view");
	glUseProgram (shader_programme);
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, &view[0][0]);
	int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, &projection[0][0]);

	int model_mat_location = glGetUniformLocation (shader_programme, "model");

    // Configuracion inical del mundo fisico Bullet
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // Creacion del mundo fisico - Uno por aplicacion
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    // Vector de gravedad
	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	//Creacion de objetos del espacio (RigidBodys)
	
	ball = new Vehicle((char*)"mallas/ae86_body.obj",shader_programme,btScalar(10),btVector3(-3,3,0),btQuaternion(0,1,0,0),dynamicsWorld);
	bodyBall = ball->getRigidBody();

	
	ball2 = new Vehicle((char*)"mallas/ae86_body.obj",shader_programme,btScalar(10),btVector3(3,3,0),btQuaternion(0,1,0,0),dynamicsWorld);
	bodyBall2 = ball2->getRigidBody();



	
	GameObject* piso = new GameObject((char*)"mallas/test_map_flat.obj",shader_programme,btScalar(0),btVector3(0,-15,1),btQuaternion(0,1,0,0),dynamicsWorld);
	btRigidBody* pisoShape = piso->getRigidBody();
	GLDebugDrawer* debug = new GLDebugDrawer();


	debug->setDebugMode(btIDebugDraw::DBG_DrawWireframe );
	debug->setView(&view);
	debug->setProj(&projection);
	dynamicsWorld->setDebugDrawer(debug);


    glm::mat4 aux;

	Input* input=new Input(g_window,ball,ball2);

	while (!glfwWindowShouldClose(g_window)){

	       // Se aumenta en un paso la simulacion (calculo del dt)
	       float currentFrame = glfwGetTime();
	       deltaTime = currentFrame - lastFrame;
	       if (deltaTime < 0.016f){
	           continue;
	       }


	       lastFrame = currentFrame;
	        dynamicsWorld->stepSimulation(1.f / 60.f, 10);
					processInput(g_window);
	       input->initialiceInput();

	       glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        glUseProgram (shader_programme);

	       projection = camara->getPerspectiva();
	       glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, &projection[0][0]);

	       view = camara->getViewMatrix();
	        glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, &view[0][0]);

	   	   piso -> draw(model_mat_location);
	       ball->draw(model_mat_location);
				 ball2->draw(model_mat_location);


				 debug->setView(&view);
				 debug->setProj(&projection);
				 dynamicsWorld->debugDrawWorld();
				 debug->drawLines();

	       glfwSwapBuffers(g_window);
	       glfwPollEvents();
	   }
	   glfwTerminate();
	   return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
		glm::vec3 front=camara->getCameraFront();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camara->setCameraPos(camara->getCameraPos()+cameraSpeed*front);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camara->setCameraPos(camara->getCameraPos()-cameraSpeed*front);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camara->setCameraPos(camara->getCameraPos() -
					glm::normalize(glm::cross(front, camara->getCameraUp())) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camara->setCameraPos(camara->getCameraPos() +
			glm::normalize(glm::cross(front, camara->getCameraUp())) * cameraSpeed);
    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			ball ->accelerate();
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    	ball -> turnLeft();
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	    	ball -> turnRight();
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				ball -> brake();

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
					ball -> reverse();
			}
			*/
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
