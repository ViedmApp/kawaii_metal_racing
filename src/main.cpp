#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "gl_utils.h"
#include "tools.h"
#include "malla.h"
#include "GLDebugDrawer.hpp"
#include <bullet/btBulletDynamicsCommon.h>

#define GL_LOG_FILE "log/gl.log"
#define VERTEX_SHADER_FILE "shaders/test_vs.glsl"
#define FRAGMENT_SHADER_FILE "shaders/test_fs.glsl"


int g_gl_width = 800;
int g_gl_height = 600;
GLFWwindow* g_window = NULL;

//VARIABLES GLOBALES
btDiscreteDynamicsWorld* dynamicsWorld;

//FUNCIONES
btRigidBody* crear_Objeto(btVector3 posicion, btCollisionShape *objetoShape,btQuaternion rotacion, float masa);



int main()
{
	return 0;
}

btRigidBody* crear_Objeto(btVector3 posicion, btCollisionShape *objetoShape,btQuaternion rotacion, float masa)
{
	btTransform objetoTransform;
	objetoTransform.setIdentity();
	objetoTransform.setRotation(rotacion);
	objetoTransform.setOrigin(posicion); // Posicion incial
	btScalar objetoMass(masa); // Masa
	bool isDynamicobjeto = (objetoMass != 0.f);
	btVector3 localInertiaobjeto(1, 0, 0);
	if (isDynamicobjeto)
		objetoShape->calculateLocalInertia(objetoMass, localInertiaobjeto);
	btDefaultMotionState* objetoMotionState = new btDefaultMotionState(objetoTransform);
	btRigidBody::btRigidBodyConstructionInfo objetoRbInfo(objetoMass, objetoMotionState, objetoShape, localInertiaobjeto);
	btRigidBody* objeto;
	objeto = new btRigidBody(objetoRbInfo);
    objeto->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(objeto); 
	return objeto;
}
