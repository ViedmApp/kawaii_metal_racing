#ifndef Vehicle_H
#define Vehicle_H
#include <bullet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tools.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "GameObject.hpp"


class Vehicle: public GameObject{
private:
   btDiscreteDynamicsWorld* world;

protected:
 btRaycastVehicle* vehicle;
bool isAlive;
float health;
public:

    Vehicle(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btCollisionShape* coll,btDiscreteDynamicsWorld* dynamicsWorld);
    ~Vehicle();

    glm::mat4 model;




    btVector3 dirr;


    /*virtual void initialize(btDiscreteDynamicsWorld* world) = 0;
    virtual void updatePhysics() = 0;

    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual void reverse() = 0;
    virtual void turnLeft() = 0;
    virtual void turnRight() = 0;


    virtual void spawn() = 0;
    virtual void despawn(btDiscreteDynamicsWorld* world) = 0;
*/
    float getHealth();
    bool getIsAlive();
     bool getBrake();
    btRaycastVehicle* getVehicle();
    btDiscreteDynamicsWorld* getWorld();


    void setHealth(float vida);
    void setIsAlive(bool isAliv);
    void setBrake(bool brake);
    void setVehicle(btRaycastVehicle* vehicle);
    void setWorld(btDiscreteDynamicsWorld* world);


};

#endif
