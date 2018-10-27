
#include "Vehicle.hpp"


Vehicle::Vehicle(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btCollisionShape* coll,btDiscreteDynamicsWorld* dynamicsWorld)
: GameObject(path,shaderprog,masa,startPosition,startRotation,coll,dynamicsWorld)
{
    initialize();
    assert(load_mesh((char*)"mallas/tire_20.obj",this -> wheel_vao,this -> wheel_num_verts));
}




Vehicle::~Vehicle(){}

void Vehicle::initialize()
{
    btRaycastVehicle::btVehicleTuning *tuning = new btRaycastVehicle::btVehicleTuning();
    btVehicleRaycaster *defvehicle = new btDefaultVehicleRaycaster(this->getWorld());
    this -> getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
    this -> getRigidBody()->setUserPointer(this);
    this -> setVehicle(new btRaycastVehicle(*tuning, this->getRigidBody(), defvehicle));
    this -> getVehicle()->setCoordinateSystem(0, 1, 2);

    this -> getWorld() -> addAction(this -> getVehicle());

    btVector3 wheelDirection(0.0f, -1.0f, 0.0f);
    btVector3 wheelAxis(-1.0f, 0.0f, 0.0f);
    btScalar suspensionRestLength(0.2f);                                                                                                                 //TODO: PARAM
    btScalar wheelRadius(0.790165f);
<<<<<<< HEAD
    this -> getVehicle() -> addWheel(btVector3(-1.45459f, -0.777563f,2.2f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false);  //TODO: PARAM
    this -> getVehicle() -> addWheel(btVector3(1.45459f, -0.777563, 2.2f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false); //TODO: PARAM
=======
    this -> getVehicle() -> addWheel(btVector3(-1.45459f, -1.177563f,2.2f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false);  //TODO: PARAM
    this -> getVehicle() -> addWheel(btVector3(1.45459f, -1.177563, 2.2f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, false); //TODO: PARAM
>>>>>>> 678bd582a64738688653e0aad2e30bfbba1e0608
                                                                                                                        //TOCO: PARAM
    this -> getVehicle() -> addWheel(btVector3(-1.45459f, -0.777563, -2.87147), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, true);   //TODO: PARAM
    this -> getVehicle() -> addWheel(btVector3(1.45459, -0.777563,-2.827147f), wheelDirection, wheelAxis, suspensionRestLength, wheelRadius, *tuning, true);    //TODO: PARAM


    for (int i = 0; i < this -> getVehicle()-> getNumWheels(); i++)
    {
        btWheelInfo &wheel = this -> getVehicle() -> getWheelInfo(i);
        //wheel.m_wheelsDampingRelaxation = 1.7f;    //TODO: PARAM
        //wheel.m_wheelsDampingCompression = -1.7f;   //TODO: PARAM
        wheel.m_frictionSlip = btScalar(10000.); //TODO: PARAM
        wheel.m_rollInfluence = btScalar(0.f);   //TODO: PARAM
        wheel.m_maxSuspensionTravelCm = 150.f;   //TODO: PARAM
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
 if (vehicle->getCurrentSpeedKmHour() < 150.f)    {
        this->vehicle->applyEngineForce(40.f, 0); //TODO: Param
        this->vehicle->applyEngineForce(40.f, 1);
    }
    this->vehicle->setBrake(btScalar(0), 0); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 1); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 2); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 3); //TODO: PARAM
}
void Vehicle::brake()
{
    this->vehicle->setBrake(btScalar(1.15), 0); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.15), 1); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.15), 2); //TODO: PARAM
    this->vehicle->setBrake(btScalar(1.15), 3); //TODO: PARAM

}
void Vehicle::reverse()
{
    //TODO: ADD LIMIT
    this->vehicle->applyEngineForce(-50, 0); //TODO: Param
    this->vehicle->applyEngineForce(-50, 1); //TODO: 
    this->vehicle->setBrake(btScalar(0), 0); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 1); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 2); //TODO: PARAM
    this->vehicle->setBrake(btScalar(0), 3); //TODO: PARAM
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
    if (!this -> getTurned())
    {
        if (this -> getVehicle()->getSteeringValue(0) > 0)
        {
            this -> getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(0) - 0.030f, 0); //TODO: PARAM
            this -> getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(1) - 0.030f, 1); //TODO: PARAM
            if (this -> getVehicle()->getSteeringValue(0) < 0)
            {
                this -> getVehicle()->setSteeringValue(0, 0);
                this -> getVehicle()->setSteeringValue(0, 1);
            }
        }
        else if (this -> getVehicle()->getSteeringValue(0) < 0)
        {
            this -> getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(0) + 0.03f, 0); //TODO: PARAM
            this -> getVehicle()->setSteeringValue(getVehicle()->getSteeringValue(1) + 0.03f, 1); //TODO: PARAM
            if (this -> getVehicle()->getSteeringValue(0) > 0)
            {
                this -> getVehicle()->setSteeringValue(0, 0);
                this -> getVehicle()->setSteeringValue(0, 1);
            }
        }
    }
    else
    {
        this -> setTurned(false);
    }
    this -> getVehicle()->setBrake(0, 0);
    this -> getVehicle()->setBrake(0, 1);
    this -> getVehicle()->setBrake(0, 2);
    this -> getVehicle()->setBrake(0, 3);

    this->getVehicle()->applyEngineForce(0, 0); //TODO: Param
    this->getVehicle()->applyEngineForce(0, 1);
}

GLuint Vehicle::getWheelVao()
{
    return this -> wheel_vao;
}

int Vehicle::getWheelNumVerts()
{
    return this -> wheel_num_verts;
}

void Vehicle::draw(GLuint model_mat_location)
{
    btTransform trans;
    this -> getRigidBody()->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(&model[0][0]);
    this -> setModelMatrix(this->model);
    glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &modelMatrix[0][0]);
    glBindVertexArray(this->getVao());
    glDrawArrays(GL_TRIANGLES, 0, this -> getNumVertices());
    for (int i = 0; i < this -> getVehicle() -> getNumWheels(); i++)
    {
        trans = this->getVehicle()->getWheelInfo(i).m_worldTransform;
        trans.getOpenGLMatrix(&model[0][0]);
        this -> setModelMatrix(this->model);
        glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &this->modelMatrix[0][0]);
        glBindVertexArray(this->getWheelVao());
        glDrawArrays(GL_TRIANGLES, 0, this->getWheelNumVerts());
    }
}
