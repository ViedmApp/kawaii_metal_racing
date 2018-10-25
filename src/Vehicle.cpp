
#include "Vehicle.hpp"


Vehicle::Vehicle(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btCollisionShape* coll,btDiscreteDynamicsWorld* dynamicsWorld)
: GameObject(path,shaderprog,masa,startPosition,startRotation,coll,dynamicsWorld){}




Vehicle::~Vehicle(){}

float Vehicle::getHealth(){
    return this->health;
}

bool Vehicle::getIsAlive(){
    return this->isAlive;
}

btRaycastVehicle* Vehicle::getVehicle(){
    return this->vehicle;
}
btDiscreteDynamicsWorld* Vehicle::getWorld(){
    return this->world;
}

void Vehicle::setHealth(float vida){
    this->health = vida;
}

void Vehicle::setIsAlive(bool isAliv){
    this->isAlive = isAliv;
}

void Vehicle::setVehicle(btRaycastVehicle* vehicle){
    this->vehicle = vehicle;
}
void Vehicle::setWorld(btDiscreteDynamicsWorld* world){
    this->world = world;
}
