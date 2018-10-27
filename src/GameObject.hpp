#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "tools.h"

class GameObject{

protected:
    GLuint vao;
    GLuint ebo;
    btVector3 position;
    btDiscreteDynamicsWorld* world;
    btQuaternion rotation;
    btScalar mass;
    int vertNumber;
    int indicesNumber;
    btRigidBody* rigidBody;
    glm::mat4 modelMatrix;

    bool load_mesh (const char* file_name, GLuint& vao, int& vert_no, btCollisionShape** col);
    bool load_mesh (const char* file_name, GLuint& vao, int& vert_no); 
    


public:
    GLuint tex_location;

    GameObject();
    GameObject(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btDiscreteDynamicsWorld* dynamicsWorld);

    ~GameObject();

    //getter
    GLuint getVao();
    btScalar getMass();
    void setMass(btScalar masa);
    btVector3 getPosition();
    void setPosition(btVector3 posicion);
    btQuaternion getRotation();
    void setRotation(btQuaternion rotacion);
    btRigidBody* getRigidBody();
    int getNumVertices();
    void setModelMatrix(glm::mat4 model);
    void draw(int matloc);
    void setWorld(btDiscreteDynamicsWorld* world);
    btDiscreteDynamicsWorld* getWorld();

};

#endif
