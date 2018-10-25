
#include "Vehicle.hpp"


Vehicle::Vehicle(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btCollisionShape* coll,btDiscreteDynamicsWorld* dynamicsWorld)
: GameObject(path,shaderprog,masa,startPosition,startRotation,coll,dynamicsWorld){}




Vehicle::~Vehicle(){}

void Vehicle::initialize()
{
    btRaycastVehicle::btVehicleTuning *tuning = new btRaycastVehicle::btVehicleTuning();
    btVehicleRaycaster *defvehicle = new btDefaultVehicleRaycaster(this->world);
    getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
    getRigidBody()->setUserPointer(this);
    btRaycastVehicle *vehicle = new btRaycastVehicle(*tuning, getRigidBody(), defvehicle);
    vehicle->setCoordinateSystem(0, 1, 2);

    world->addAction(vehicle);

    btVector3 wheelDirection(0.0f, -1.0f, 0.0f);
    btVector3 wheelAxis(-1.0f, 0.0f, 0.0f);
    btScalar suspensionRestLength(0.2f);                                                                                                                 //TODO: PARAM
    btScalar wheelRadius(2.f);                                                                                                                           //TOCO: PARAM
    vehicle->addWheel(btVector3(-5.6f, 1.69f, 7.3), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, true);   //TODO: PARAM
    vehicle->addWheel(btVector3(3.f, 1.69f, 7.3), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, true);    //TODO: PARAM
    vehicle->addWheel(btVector3(-5.6f, 1.69f, -6.32f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false);  //TODO: PARAM
    vehicle->addWheel(btVector3(3.f, 1.69f, -6.32f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false); //TODO: PARAM

    this->setVehicle(vehicle);
    for (int i = 0; i < getVehicle()->getNumWheels(); i++)
    {
        btWheelInfo &wheel = getVehicle()->getWheelInfo(i);
        //wheel.m_wheelsDampingRelaxation = 1.7f;    //TODO: PARAM
        //wheel.m_wheelsDampingCompression = -1.7f;   //TODO: PARAM
        wheel.m_frictionSlip = btScalar(10000.); //TODO: PARAM
        wheel.m_rollInfluence = btScalar(0.f);   //TODO: PARAM
        wheel.m_maxSuspensionTravelCm = 100.f;   //TODO: PARAM
    }
    setIsAlive(true);

  }



float Vehicle::getHealth(){
    return this->health;
}

bool Vehicle::getIsAlive(){
    return this->isAlive;
}

btRaycastVehicle* Vehicle::getVehicle(){
    return this->vehicle;
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

void Vehicle::accelerate()
{
    if (this->vehicle->getCurrentSpeedKmHour() < 150.f)
    {
        this->vehicle->applyEngineForce(85, 0); //TODO: Param
        this->vehicle->applyEngineForce(85, 1);
    }
}
void Vehicle::brake()
{
    this->vehicle->setBrake(btScalar(1.5), 0); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.5), 1); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.5), 2); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.5), 3); //TODO: PARAM

}
void Vehicle::reverse()
{
    //TODO: ADD LIMIT
    this->vehicle->applyEngineForce(-50, 0); //TODO: Param
    this->vehicle->applyEngineForce(-50, 1); //TODO: PARAM
}

void Vehicle::turnRight()
{
    if (this->vehicle->getSteeringValue(0) > -0.4f && this->vehicle->getSteeringValue(1) > -0.4f)
    {
        this->vehicle->setSteeringValue(this->vehicle->getSteeringValue(0) - 0.02f, 0); //TODO: Param
        this->vehicle->setSteeringValue(this->vehicle->getSteeringValue(1) - 0.02f, 1); //TODO: PARAM
    }
    setTurned(true);
}
void Vehicle::turnLeft()
{
    if (this->vehicle->getSteeringValue(0) < 0.4f && this->vehicle->getSteeringValue(1) < 0.4f)
    {
        this->vehicle->setSteeringValue(this->vehicle->getSteeringValue(0) + 0.02f, 0); //TODO: PARAM
        this->vehicle->setSteeringValue(this->vehicle->getSteeringValue(1) + 0.02f, 1); //TODO: PARAM
    }
    setTurned(true);
}

bool Vehicle::getTurned(){
    return this->turned;
}

void Vehicle::setTurned(bool turn){
    this->turned = turn;
}


void Vehicle::updatePhysics()
{
    if (!getTurned())
    {
        if (getVehicle()->getSteeringValue(0) > 0)
        {
            getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(0) - 0.030f, 0); //TODO: PARAM
            getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(1) - 0.030f, 1); //TODO: PARAM
            if (getVehicle()->getSteeringValue(0) < 0)
            {
                getVehicle()->setSteeringValue(0, 0);
                getVehicle()->setSteeringValue(0, 1);
            }
        }
        else if (getVehicle()->getSteeringValue(0) < 0)
        {
            getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(0) + 0.03f, 0); //TODO: PARAM
            getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(1) + 0.03f, 1); //TODO: PARAM
            if (getVehicle()->getSteeringValue(0) > 0)
            {
                getVehicle()->setSteeringValue(0, 0);
                getVehicle()->setSteeringValue(0, 1);
            }
        }
    }
    else
    {
        setTurned(false);
    }
    getVehicle()->setBrake(0, 0);
    getVehicle()->setBrake(0, 1);
    getVehicle()->setBrake(0, 2);
    getVehicle()->setBrake(0, 3);

    this->getVehicle()->applyEngineForce(0, 0); //TODO: Param
    this->getVehicle()->applyEngineForce(0, 1);
}
/*
void Auto::draw(GLuint model_mat_location)
{
    btTransform trans;
    this->getRigidBody()->getMotionState()->getWorldTransform(trans);

    model = glm::translate(glm::mat4(), glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
    model = glm::rotate(model, trans.getRotation().getAngle(), glm::vec3(trans.getRotation().getAxis().getX(), trans.getRotation().getAxis().getY(), trans.getRotation().getAxis().getZ()));
    btVector3 escala = getRigidBody()->getCollisionShape()->getLocalScaling();
    model = glm::scale(model, glm::vec3(escala.getX(), escala.getY(), escala.getZ()));

    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &model[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->getTexture());
    glUniform1i(tex_location, 0);
glActiveTexture (GL_TEXTURE1);
	glBindTexture (GL_TEXTURE_2D, this->normalMap);
    glUniform1i (normalMapLocation, 1);

    glBindVertexArray(this->getVao());
    glDrawArrays(GL_TRIANGLES, 0, this->getVertNumber());

    for (int i = 0; i < this->getCar()->getNumWheels(); i++)
    {
        trans = this->getVehicle()->getWheelInfo(i).m_worldTransform;

        
        glUniformMatrix4fv(matloc, 1, GL_FALSE, &this->modelMatrix[0][0]);
        glBindVertexArray(this->getVao());
        glDrawArrays(GL_TRIANGLES, 0, this->getNumVertices());

        glUniform1i(wheel_texLocation, 0);


    }
}
*/
