#ifndef PHYSICAMANAGER_H
#define PHYSICAMANAGER_H

#include "common.h"

using namespace std;
using namespace glm;
using namespace physx;

class PhysicsManager
{

public:

	PhysicsManager();
	~PhysicsManager();

	bool init();
	void simulate();

	PxRigidStatic *createRigidStatic(PxTransform &transform, vector<vec3> vertices);
	PxRigidDynamic *createRigidDynamic(PxTransform &transform, vector<vec3> vertices);
	PxRigidStatic *createRigidStatic(PxTransform &transform, PxGeometry geometry);
	PxRigidDynamic *createRigidDynamic(PxTransform &transform, PxGeometry geometry);
	PxConvexMesh *createConvexMesh(vector<vec3> vertices);

	PxCapsuleController *createCapsuleController(vec3 position);

public:

	PxDefaultAllocator allocator;
	PxDefaultErrorCallback errorCallback;
	PxFoundation* foundation;
	PxPhysics* physics;
	PxDefaultCpuDispatcher*	dispatcher;
	PxScene* scene;
	PxMaterial* material;
	PxControllerManager *controllerManager;
	PxCooking *cooking;
	PxVisualDebuggerConnection* connection;

};

#endif