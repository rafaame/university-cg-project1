#ifndef COLLISIONCLOTH_H
#define COLLISIONCLOTH_H

#include "common.h"

using namespace std;
using namespace glm;
using namespace physx;

class CollisionCloth
{

public:

	CollisionCloth();
	~CollisionCloth();

	void init(uint16_t dimension, vec3 position, quat rotation, vec3 positionDisplacement, vec3 rotationDisplacement);

	vec3 getPosition();
	quat getRotation();
	PxCloth *getCloth() { return cloth; }
	PxClothMeshDesc *getMeshDesc() { return &meshDesc; }

	void setPosition(vec3 position);
	void setRotation(quat rotation);

protected:

	PxCloth *cloth;
	PxClothMeshDesc meshDesc;

	vec3 positionDisplacement;
	vec3 rotationDisplacement;

};

#endif











