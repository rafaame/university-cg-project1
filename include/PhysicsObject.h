#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "common.h"	

#include "CollisionModel.h"							

using namespace std;
using namespace glm;
using namespace physx;

class Model;
class Camera;

class PhysicsObject
{

public:
	
	PhysicsObject(CollisionModel_t type, Camera *camera);
	~PhysicsObject();

	bool loadFromObj(string filename, string vertexShaderFilename, string fragmentShaderFilename, string textureFilename);
	void initCollisionModel();

	vec3 getPosition();
	quat getRotation();

	void setPosition(vec3 position);
	void setRotation(quat rotation);

	void simulate();
	void render();
	
protected:

	CollisionModel_t type;
	Model *model;
	CollisionModel *collisionModel;
	Camera *camera;

};

#endif











