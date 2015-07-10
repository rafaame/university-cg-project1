#include "CollisionCloth.h"

#include "Application.h"
#include "PhysicsManager.h"

using namespace std;
using namespace glm;
using namespace physx;

CollisionCloth::CollisionCloth()
{

	cloth = NULL;

}

CollisionCloth::~CollisionCloth()
{



}

void CollisionCloth::init(uint16_t dimension, vec3 position, quat rotation, vec3 positionDisplacement, vec3 rotationDisplacement)
{

	cloth = Application::instance()->getPhysicsManager()->createCloth(dimension, position, rotation, meshDesc);

}

vec3 CollisionCloth::getPosition()
{

	PxTransform globalPose = cloth->getGlobalPose();
	PxVec3 position = globalPose.p;

	return vec3(position.x, position.y, position.z) - positionDisplacement;

}

quat CollisionCloth::getRotation()
{

	PxTransform globalPose = cloth->getGlobalPose();
	quat rotation = quat(globalPose.q.w, globalPose.q.x, globalPose.q.y, globalPose.q.z);

	rotation = rotate(rotation, radians(-rotationDisplacement.x), vec3(1, 0, 0));
	rotation = rotate(rotation, radians(-rotationDisplacement.y), vec3(0, 1, 0));
	rotation = rotate(rotation, radians(-rotationDisplacement.z), vec3(0, 0, 1));

	return quat(rotation.w, rotation.x, rotation.y, rotation.z);

}

void CollisionCloth::setPosition(vec3 position)
{

	PxTransform globalPose = cloth->getGlobalPose();
	globalPose.p.x = position.x;
	globalPose.p.y = position.y;
	globalPose.p.z = position.z;

	cloth->setGlobalPose(globalPose);

}

void CollisionCloth::setRotation(quat rotation)
{

	PxTransform globalPose = cloth->getGlobalPose();
	globalPose.q.w = rotation.w;
	globalPose.q.x = rotation.x;
	globalPose.q.y = rotation.y;
	globalPose.q.z = rotation.z;

	cloth->setGlobalPose(globalPose);

}