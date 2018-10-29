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

protected:
    GLuint wheel_vao;
    int wheel_num_verts;
    btRaycastVehicle* vehicle;
    bool isAlive;
    float health;
    bool turned;
public:

    Vehicle(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btDiscreteDynamicsWorld* dynamicsWorld);
    ~Vehicle();

    glm::mat4 model;




    btVector3 dirr;
    void initialize();

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

    float getX();
    float getY();
    float getZ();
    float getHealth();
    bool getIsAlive();
    bool getBrake();
    bool getTurned();
    btRaycastVehicle* getVehicle();
    void accelerate();
    void brake();
    void reverse();
    void turnLeft();
    void turnRight();
    void updatePhysics();
    void fire();
    void setTurned(bool turn);    //void spawn();
    //void despawn(btDiscreteDynamicsWorld *world);

    void setHealth(float vida);
    void setIsAlive(bool isAliv);
    void setBrake(bool brake);
    void setVehicle(btRaycastVehicle* vehicle);
    void draw(GLuint model_mat_location);

    GLuint getWheelVao();
    int getWheelNumVerts();



};

#endif
