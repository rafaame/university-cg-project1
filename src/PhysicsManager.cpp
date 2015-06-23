#include "PhysicsManager.h"
#include "TimeManager.h"

using namespace std;
using namespace physx;

PxRigidDynamic* dynamic = NULL;

PhysicsManager::PhysicsManager()
{

	foundation = NULL;
	physics = NULL;
	dispatcher = NULL;
	material = NULL;
	controllerManager = NULL;
	cooking = NULL;
	connection = NULL;

}

PhysicsManager::~PhysicsManager()
{

	scene->release();
	dispatcher->release();
	PxProfileZoneManager* profileZoneManager = physics->getProfileZoneManager();

	if(connection)
		connection->release();

	cooking->release();
	physics->release();	
	profileZoneManager->release();
	foundation->release();

}

bool PhysicsManager::init()
{

	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(foundation);
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, profileZoneManager);
	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	
	if(physics->getPvdConnectionManager())
	{

		connection = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), "192.168.1.107", 5425, 10, (PxVisualDebuggerConnectionFlags) 7);
		physics->getVisualDebugger()->setVisualizeConstraints(true);
		physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		physics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);

	}

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	dispatcher = PxDefaultCpuDispatcherCreate(2);

	sceneDesc.cpuDispatcher	= dispatcher;
	sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
	scene = physics->createScene(sceneDesc);

	material = physics->createMaterial(0.5f, 0.5f, 0.6f);

	controllerManager = PxCreateControllerManager(*scene);

	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0,1,0,1), *material);
	scene->addActor(*groundPlane);

	//dynamic = PxCreateDynamic(*physics, PxTransform(PxVec3(0,40,100)), PxSphereGeometry(10), *material, 10.0f);
	//dynamic->setAngularDamping(0.5f);
	//dynamic->setLinearVelocity(velocity);
	//scene->addActor(*dynamic);

	//for(PxU32 i=0;i<5;i++)
	//	createStack(PxTransform(PxVec3(0,0,stackZ-=10.0f)), 10, 2.0f);

	//if(!interactive)
	//	createDynamic(PxTransform(PxVec3(0,40,100)), PxSphereGeometry(10), PxVec3(0,-50,-100));

}

void PhysicsManager::simulate()
{

	scene->simulate(std::max<double>(TimeManager::instance()->getDelta(), 1/200.0f));
	scene->fetchResults(true);

	//if(dynamic)
	//	cout << "Sphere pos: " << dynamic->getGlobalPose().p.x << " " << dynamic->getGlobalPose().p.y << " " << dynamic->getGlobalPose().p.z << endl;

}

PxRigidStatic *PhysicsManager::createRigidStatic(PxTransform &transform, vector<vec3> vertices)
{

	PxRigidStatic *rigidStatic = physics->createRigidStatic(transform);
	//PxConvexMesh *convexMesh = createConvexMesh(vertices);
	//PxShape *convexShape = rigidStatic->createShape(PxConvexMeshGeometry(convexMesh), *material);
	PxShape *convexShape = rigidStatic->createShape(PxBoxGeometry(1, 1, 1), *material);

	scene->addActor(*rigidStatic);

	return rigidStatic;

}

PxRigidDynamic *PhysicsManager::createRigidDynamic(PxTransform &transform, vector<vec3> vertices)
{

	PxRigidDynamic *rigidDynamic = physics->createRigidDynamic(transform);
	//PxConvexMesh *convexMesh = createConvexMesh(vertices);
	//PxShape *convexShape = rigidDynamic->createShape(PxConvexMeshGeometry(convexMesh), *material);
	PxShape *convexShape = rigidDynamic->createShape(PxBoxGeometry(1, 1, 1), *material);

	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1.0f);
	scene->addActor(*rigidDynamic);

	return rigidDynamic;

}

PxRigidStatic *PhysicsManager::createRigidStatic(PxTransform &transform, PxGeometry geometry)
{

	PxRigidStatic *rigidStatic = physics->createRigidStatic(transform);
	PxShape *convexShape = rigidStatic->createShape(geometry, *material);

	scene->addActor(*rigidStatic);

	return rigidStatic;

}

PxRigidDynamic *PhysicsManager::createRigidDynamic(PxTransform &transform, PxGeometry geometry)
{

	PxRigidDynamic *rigidDynamic = physics->createRigidDynamic(transform);
	PxShape *convexShape = rigidDynamic->createShape(PxBoxGeometry(1, 1, 1), *material);

	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 10.0f);
	scene->addActor(*rigidDynamic);

	return rigidDynamic;

}

PxConvexMesh *PhysicsManager::createConvexMesh(vector<vec3> vertices)
{

	PxVec3 *convexVerts = new PxVec3[vertices.size()];
	for(auto it = vertices.begin(); it != vertices.end(); it++)
	{

		vec3 modelVertex = (*it);

		cout << "(" << convexVerts->x << ") Vec3: " << modelVertex.x << " " << modelVertex.y << " " << modelVertex.z << endl;

		(*convexVerts).x = modelVertex.x;
		(*convexVerts).y = modelVertex.y;
		(*convexVerts).z = modelVertex.z;

		convexVerts++;

	}

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = vertices.size();
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = convexVerts;
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

	PxDefaultMemoryOutputStream buf;
	if(!cooking->cookConvexMesh(convexDesc, buf))
    {

    	cout << "Error cooking" << endl;
    	exit(1);

    }

	PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	
	return physics->createConvexMesh(input);

}

PxCapsuleController *PhysicsManager::createCapsuleController(vec3 position)
{

	PxCapsuleControllerDesc desc;
	desc.material = material;
	desc.position = PxExtendedVec3(position.x, position.y, position.z);
	desc.height = 3.0f;
	desc.radius = 0.5f;
	desc.slopeLimit = 0.0f;
	desc.contactOffset = 0.1f;
	desc.stepOffset = 0.02f;

	PxCapsuleController *controller = static_cast<PxCapsuleController *>(controllerManager->createController(desc));

	return controller;

}