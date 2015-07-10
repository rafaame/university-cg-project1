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

		connection = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), "192.168.37.132", 5425, 10, PxVisualDebuggerExt::getAllConnectionFlags());
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

	return true;

}

void PhysicsManager::simulate()
{

	scene->simulate(std::max<double>(TimeManager::instance()->getDelta(), 1/200.0f));
	scene->fetchResults(true);

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

PxRigidStatic *PhysicsManager::createRigidStatic(PxTransform &transform, PxGeometry &geometry)
{

	PxRigidStatic *rigidStatic = physics->createRigidStatic(transform);
	PxShape *convexShape = rigidStatic->createShape(geometry, *material);

	scene->addActor(*rigidStatic);

	return rigidStatic;

}

PxRigidDynamic *PhysicsManager::createRigidDynamic(PxTransform &transform, PxGeometry &geometry)
{

	PxRigidDynamic *rigidDynamic = physics->createRigidDynamic(transform);
	PxShape *convexShape = rigidDynamic->createShape(geometry, *material);

	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 10.0f);
	scene->addActor(*rigidDynamic);

	return rigidDynamic;

}

PxCloth *PhysicsManager::createCloth(uint16_t dimension, vec3 position, quat rotation, PxClothMeshDesc &meshDesc)
{

	PxTransform pose = PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotation.w, rotation.x, rotation.y, rotation.z));

	//Create regular mesh
	PxU32 resolution = dimension;
	PxU32 numParticles = resolution*resolution;
	PxU32 numTriangles = 2*(resolution-1)*(resolution-1) * 2;

	//Create cloth particles
	PxClothParticle* particles = new PxClothParticle[numParticles];
	PxVec3 center(0.5f, 0.3f, 0.0f);
	PxVec3 delta = 1.0f/(resolution-1) * PxVec3(2.0f, 2.0f, 2.0f);
	PxClothParticle* pIt = particles;
	for(PxU32 i=0; i<resolution; ++i)
	{

		for(PxU32 j=0; j<resolution; ++j, ++pIt)
		{

			pIt->invWeight = j+1<resolution ? 1.0f : 0.0f;
			pIt->pos = delta.multiply(PxVec3(PxReal(i),
				PxReal(j), -PxReal(j))) - center;

		}

	}

	// create indices
	PxU32* indices = new PxU32[numTriangles * 3];
	PxU32* iIt = indices;
	for(PxU32 i = 0; i < resolution-1; i++)
		for(PxU32 j = 0; j < resolution-1; j++)
		{

			PxU32 odd = j&1u, even = 1-odd;

			*iIt++ = i*resolution + (j+odd);
			*iIt++ = (i+odd)*resolution + (j+1);
			*iIt++ = (i+1)*resolution + (j+even);
			*iIt++ = (i+1)*resolution + (j+even);
			*iIt++ = (i+even)*resolution + j;
			*iIt++ = i*resolution + (j+odd);

			*iIt++ = i*resolution + (j+odd);
			*iIt++ = (i+1)*resolution + (j+even);
			*iIt++ = (i+odd)*resolution + (j+1);

			*iIt++ = (i+1)*resolution + (j+even);
			*iIt++ = i*resolution + (j+odd);
			*iIt++ = (i+even)*resolution + j;

		}

	meshDesc.points.count = numParticles;
	meshDesc.points.stride = sizeof(PxClothParticle);
	meshDesc.points.data = particles;

	meshDesc.invMasses.count = numParticles;
	meshDesc.invMasses.stride = sizeof(PxClothParticle);
	meshDesc.invMasses.data = &particles->invWeight;

	meshDesc.triangles.count = numTriangles;
	meshDesc.triangles.stride = sizeof(PxU32) * 3;
	meshDesc.triangles.data = indices;

	PxClothFabric* fabric = PxClothFabricCreate(*physics, meshDesc, PxVec3(0, 1, 0));

	//delete[] indices;

	//Create cloth
	PxCloth *cloth = physics->createCloth(pose, *fabric, particles, PxClothFlags(0));

	fabric->release();
	//delete[] particles;

	cloth->setSolverFrequency(240.0f);
	cloth->addCollisionPlane(PxClothCollisionPlane(PxVec3(0, 1, 0), 0.0f));
	cloth->addCollisionConvex(1 << 0);

	scene->addActor(*cloth);

	return cloth;

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