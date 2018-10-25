#include "GameObject.hpp"

GameObject::GameObject(){}

GameObject::GameObject(const char* path, GLuint shaderprog, btScalar masa, btVector3 startPosition, btQuaternion startRotation,btCollisionShape* coll,btDiscreteDynamicsWorld* dynamicsWorld)
{
    this->mass = masa;
    this->position = startPosition;
    this->rotation = startRotation;
    if(load_mesh(path, vao, this->vertNumber)==false){
        printf("Error loading %s", path);
    }
    btTransform startTransform;
    startTransform.setIdentity();
    
    bool isDynamic = (this->mass != 0.f); 
    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        coll->calculateLocalInertia(this->mass, localInertia);

    startTransform.setOrigin(this->position);
    startTransform.setRotation(this->rotation);
    
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(this->mass, myMotionState, coll, localInertia);
    this->rigidBody = new btRigidBody(rbInfo);
    dynamicsWorld->addRigidBody(this->rigidBody);
}

GameObject::~GameObject(){
    delete this->rigidBody->getMotionState();
    delete this->rigidBody->getCollisionShape();
    delete this->rigidBody;
}

bool GameObject::load_mesh (const char* file_name, GLuint& vao, int& vert_no) {
    const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate);
    if (!scene) {
        fprintf (stderr, "ERROR: reading mesh %s\n", file_name);
        return false;
    }
    printf ("  %i animations\n", scene->mNumAnimations);
    printf ("  %i cameras\n", scene->mNumCameras);
    printf ("  %i lights\n", scene->mNumLights);
    printf ("  %i materials\n", scene->mNumMaterials);
    printf ("  %i meshes\n", scene->mNumMeshes);
    printf ("  %i textures\n", scene->mNumTextures);
    
    const aiMesh* mesh = scene->mMeshes[0];
    printf ("    %i vertices in %s\n", mesh->mNumVertices, file_name);
    
    vert_no = mesh->mNumVertices;

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    GLfloat* points = NULL;                                 
    GLfloat* normals = NULL;                                
    GLfloat* texcoords = NULL;                              

    if (mesh->HasPositions ()) {
        points = (GLfloat*)malloc (vert_no * 3 * sizeof (GLfloat));
        for (int i = 0; i < vert_no; i++) {
            const aiVector3D* vp = &(mesh->mVertices[i]);
            points[i * 3] = (GLfloat)vp->x;
            points[i * 3 + 1] = (GLfloat)vp->y;
            points[i * 3 + 2] = (GLfloat)vp->z;
        }
    }
    if (mesh->HasNormals ()) {
        normals = (GLfloat*)malloc (vert_no * 3 * sizeof (GLfloat));
        for (int i = 0; i < vert_no; i++) {
            const aiVector3D* vn = &(mesh->mNormals[i]);
            normals[i * 3] = (GLfloat)vn->x;
            normals[i * 3 + 1] = (GLfloat)vn->y;
            normals[i * 3 + 2] = (GLfloat)vn->z;
        }
    }
    if (mesh->HasTextureCoords (0)) {
        texcoords = (GLfloat*)malloc (vert_no * 2 * sizeof (GLfloat));
        for (int i = 0; i < vert_no; i++) {
            const aiVector3D* vt = &(mesh->mTextureCoords[0][i]);
            texcoords[i * 2] = (GLfloat)vt->x;
            texcoords[i * 2 + 1] = (GLfloat)vt->y;
        }
    }
    
    if (mesh->HasPositions ()) {
        GLuint vbo;
        glGenBuffers (1, &vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        glBufferData (
            GL_ARRAY_BUFFER,
            3 * vert_no * sizeof (GLfloat),
            points,
            GL_STATIC_DRAW
        );
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (0);
        free (points);
    }
    if (mesh->HasNormals ()) {
        GLuint vbo;
        glGenBuffers (1, &vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        glBufferData (
            GL_ARRAY_BUFFER,
            3 * vert_no * sizeof (GLfloat),
            normals,
            GL_STATIC_DRAW
        );
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (1);
        free (normals);
    }
    if (mesh->HasTextureCoords (0)) {
        GLuint vbo;
        glGenBuffers (1, &vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        glBufferData (
            GL_ARRAY_BUFFER,
            2 * vert_no * sizeof (GLfloat),
            texcoords,
            GL_STATIC_DRAW
        );
        glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (2);
        free (texcoords);
    }
    if (mesh->HasTangentsAndBitangents ()) {
        // NB: could store/print tangents here
    }
    
    aiReleaseImport (scene);
    printf ("mesh loaded\n");
    
    return true;
}

btRigidBody* GameObject::getRigidBody(){
    return this->rigidBody;
}

void GameObject::setMass(btScalar masa)
{
    this->mass = masa;
}

btScalar GameObject::getMass()
{
    return this->mass;
}

btVector3 GameObject::getPosition()
{
    return this->position;
}

void GameObject::setPosition(btVector3 posicion)
{
    this->position = posicion;
}

btQuaternion GameObject::getRotation()
{
    return this->rotation;
}
void GameObject::setRotation(btQuaternion rotacion)
{
    this->rotation = rotation;
}

GLuint GameObject::getVao(){
    return this->vao;
}

int GameObject::getNumVertices(){
    return this->vertNumber;
}

void GameObject::setModelMatrix(glm::mat4 model){
    this->modelMatrix = model;
}

void GameObject::draw(int matloc){
        glUniformMatrix4fv(matloc, 1, GL_FALSE, &this->modelMatrix[0][0]);
        glBindVertexArray(this->getVao());
        glDrawArrays(GL_TRIANGLES, 0, this->getNumVertices());
}

