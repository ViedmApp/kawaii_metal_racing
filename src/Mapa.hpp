#ifndef MAPA_H
#define MAPA_H
#include "tools.h"
#include "GameObject.hpp"

class Mapa{

protected:
	btVector3 p1_Start_Position;
	btVector3 p2_Start_Position;
	GameObject** mapa;
	btDiscreteDynamicsWorld* dynamicsWorld;
	GLuint shader_programme;
	void init();
	int N;

public:
    Mapa(btDiscreteDynamicsWorld* dynamicsWorld,GLuint shader_programme);
    ~Mapa();
    btVector3 checkpoints[8];
    void draw(GLuint model_mat_location);
    btVector3 getP1StartPosition();
    btVector3 getP2StartPosition();



};


#endif
