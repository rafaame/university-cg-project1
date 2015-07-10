#ifndef PHYSICSCLOTH_H
#define PHYSICSCLOTH_H

#include "common.h"

#include "Model.h"
#include "CollisionCloth.h"

using namespace std;
using namespace glm;
using namespace physx;

class Shader;

class PhysicsCloth
{

public:

	PhysicsCloth();
	~PhysicsCloth();

	void init(uint16_t dimension, string textureFilename, vec3 position, quat rotation, vec3 collisionClothPositionDisplacement, vec3 collisionClothRotationDisplacement);

	vec3 getPosition();
	quat getRotation();
	Model *getModel() { return model; }

	void setPosition(vec3 position);
	void setRotation(quat rotation);

	void simulate();
	void render();

protected:

	Model::Mesh *mesh;
	Model *model;

	CollisionCloth *collisionCloth;

};

#endif











