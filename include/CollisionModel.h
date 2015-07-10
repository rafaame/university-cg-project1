#ifndef COLLISIONMODEL_H
#define COLLISIONMODEL_H

#include "common.h"

using namespace std;
using namespace glm;
using namespace physx;

class Model;

enum CollisionModel_t
{

	COLLISION_MODEL_STATIC,
	COLLISION_MODEL_DYNAMIC

};

enum CollisionShape_t
{

	COLLISION_SHAPE_BOX,
	COLLISION_SHAPE_CAPSULE

};

class CollisionModel
{

public:

	CollisionModel(CollisionModel_t type);
	~CollisionModel();

	void init(CollisionShape_t shape, vec3 dimensions, vec3 position, quat rotation, vec3 positionDisplacement, vec3 rotationDisplacement);
	//void initFromModel(Model *model);

	vec3 getPosition();
	quat getRotation();
	PxRigidBody *getRigidBody() { return rigidBody; }

	void setPosition(vec3 position);
	void setRotation(quat rotation);

protected:

	CollisionModel_t type;
	PxRigidBody *rigidBody;

	vec3 positionDisplacement;
	vec3 rotationDisplacement;

};

#endif











