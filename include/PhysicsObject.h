#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "common.h"

#include "CollisionModel.h"

using namespace std;
using namespace glm;
using namespace physx;

class Model;
class Shader;

class PhysicsObject
{

public:

	PhysicsObject(CollisionModel_t type);
	~PhysicsObject();

	bool loadFromObj(string filename, string textureFilename, Shader *shader = NULL);
	void init(CollisionShape_t shape, vec3 dimensions, vec3 position, quat rotation, vec3 collisionModelPositionDisplacement, vec3 collisionModelRotationDisplacement);

	Model *getModel() { return model; }
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

};

#endif











