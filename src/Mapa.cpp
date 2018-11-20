#include "Mapa.hpp"

Mapa::Mapa(btDiscreteDynamicsWorld* dynamicsWorld,GLuint shader_programme)
{
    this -> dynamicsWorld = dynamicsWorld;
    this -> shader_programme = shader_programme;
    init();
}
Mapa::~Mapa()
{

}

void Mapa::init()
{
    N = 24;
    int cont = 0;
    p1_Start_Position = btVector3(-3,1,70);
    p2_Start_Position = btVector3(4,1,70);
    mapa = (GameObject**)malloc((N)*sizeof(GameObject));
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn.obj",shader_programme,btScalar(0),
        btVector3(0,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld,(char*)"textures/map_track_turn_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_T.obj",shader_programme,btScalar(0),
        btVector3(0,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_R.obj",shader_programme,btScalar(0),
        btVector3(0,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_L.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_R.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,10),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat.obj",shader_programme,btScalar(0),
        btVector3(0,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_L.obj",shader_programme,btScalar(0),
        btVector3(0,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_R.obj",shader_programme,btScalar(0),
        btVector3(0,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn.obj",shader_programme,btScalar(0),
        btVector3(0,-10,170),btQuaternion(0,1,0,sin(0)),dynamicsWorld,(char*)"textures/map_track_turn_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_T.obj",shader_programme,btScalar(0),
        btVector3(0,-10,170),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_R.obj",shader_programme,btScalar(0),
        btVector3(0,-10,170),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,170),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_L.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,170),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_R.obj",shader_programme,btScalar(0),
        btVector3( 80,-10,170),btQuaternion(0,1,0,cos(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn.obj",shader_programme,btScalar(0),
        btVector3(160,-10,170),btQuaternion(3*PI/2,0,0),dynamicsWorld,(char*)"textures/map_track_turn_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_T.obj",shader_programme,btScalar(0),
        btVector3(160,-10,170),btQuaternion(3*PI/2,0,0),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_R.obj",shader_programme,btScalar(0),
        btVector3(160,-10,170),btQuaternion(3*PI/2,0,0),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn.obj",shader_programme,btScalar(0),
        btVector3(160,-10,10),btQuaternion(-2*PI,0,0),dynamicsWorld,(char*)"textures/map_track_turn_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_T.obj",shader_programme,btScalar(0),
        btVector3(160,-10,10),btQuaternion(-2*PI,0,0),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_turn_border_R.obj",shader_programme,btScalar(0),
        btVector3(160,-10,10),btQuaternion(-2*PI,0,0),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat.obj",shader_programme,btScalar(0),
        btVector3(160,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_L.obj",shader_programme,btScalar(0),
        btVector3(160,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");
    mapa[cont++] = new GameObject((char*)"mallas/map_track_flat_border_R.obj",shader_programme,btScalar(0),
        btVector3(160,-10,90),btQuaternion(0,1,0,sin(0)),dynamicsWorld, (char*)"textures/map_track_flat_border_t.png");

}

btVector3 Mapa::getP1StartPosition()
{
    return p1_Start_Position;
}

btVector3 Mapa::getP2StartPosition()
{
    return p2_Start_Position;
}

void Mapa::draw(GLuint model_mat_location)
{
    for (int i = 0; i < N; ++i)
    {
        btTransform trans;
        mapa[i]->getRigidBody()->getMotionState()->getWorldTransform(trans);
        trans.getOpenGLMatrix(&mapa[i]->model[0][0]);
        mapa[i]->setModelMatrix(mapa[i]->model);
        glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &mapa[i]->modelMatrix[0][0]);

        glActiveTexture (GL_TEXTURE0);
    	glBindTexture (GL_TEXTURE_2D, mapa[i]->texture);
        glUniform1i (mapa[i]->tex_location, 0);

        glActiveTexture (GL_TEXTURE1);
    	glBindTexture (GL_TEXTURE_2D, mapa[i]->normalMap);
        //glUniform1i (normalMapLocation, 1);

        glBindVertexArray(mapa[i]->getVao());
        glDrawArrays(GL_TRIANGLES, 0, mapa[i]->getNumVertices());
    }
}
