#include "CollisionModel.h"
#include "Model.h"
#include "PhysicsManager.h"
#include "Application.h"

using namespace std;
using namespace glm;
using namespace physx;

CollisionModel::CollisionModel(CollisionModel_t type)
{

	this->type = type;
	this->rigidBody = NULL;

}

CollisionModel::~CollisionModel()
{

	//if(rigidBody)
	//	delete rigidBody;

}

void CollisionModel::init(vec3 position, CollisionShape_t shape)
{

	PxTransform transform(PxVec3(position.x, position.y, position.z));
	PxGeometry *geometry = NULL;

	switch(shape)
	{

		COLLISION_SHAPE_BOX:

			geometry = new PxBoxGeometry(1, 1, 1);

			break;

		COLLISION_SHAPE_CAPSULE:

			geometry = new PxCapsuleGeometry(1, 1);

	}

	switch(type)
	{

		case COLLISION_MODEL_STATIC:

			rigidBody = (PxRigidBody *) gApplication->getPhysicsManager()->createRigidStatic(transform, PxBoxGeometry(1, 1, 1));

			break;

		case COLLISION_MODEL_DYNAMIC:

			rigidBody = (PxRigidBody *) gApplication->getPhysicsManager()->createRigidDynamic(transform, PxBoxGeometry(1, 1, 1));

			break;

	}

}

void CollisionModel::initFromModel(Model *model)
{

	vec3 position = model->getPosition();
	quat rotation = model->getRotation();
	vector<vec3> tmpVertices = model->getVertices();
	vector<vec3> vertices;

	for(auto it = tmpVertices.begin(); it != tmpVertices.end(); it++)
	{

		bool add = true;
		vec3 tmpVertex = (*it);

		for(auto itt = vertices.begin(); itt != vertices.end(); itt++)
		{

			vec3 v = (*itt);

			if(v.x == tmpVertex.x && v.y == tmpVertex.y && v.z == tmpVertex.z)
			{

				add = false;

				break;

			}

		}

		if(add)
			vertices.push_back(tmpVertex);

	}

	PxTransform transform(PxVec3(position.x, position.y, position.z));

	switch(type)
	{

		case COLLISION_MODEL_STATIC:

			rigidBody = (PxRigidBody *) gApplication->getPhysicsManager()->createRigidStatic(transform, vertices);

			break;

		case COLLISION_MODEL_DYNAMIC:

			rigidBody = (PxRigidBody *) gApplication->getPhysicsManager()->createRigidDynamic(transform, vertices);

			break;

	}

}

vec3 CollisionModel::getPosition()
{

	PxTransform globalPose = rigidBody->getGlobalPose();
	PxVec3 position = globalPose.p;

	return vec3(position.x, position.y, position.z);

}

quat CollisionModel::getRotation()
{

	PxTransform globalPose = rigidBody->getGlobalPose();
	PxQuat rotation = globalPose.q;

	//vec3 euler = eulerAngles(quat(rotation.w, rotation.x, rotation.y, rotation.z));

	//return vec3(euler.x / PI * 180.0f, euler.y / PI * 180.0f, euler.z / PI * 180.0f);
	//
	
	return quat(rotation.w, rotation.x, rotation.y, rotation.z);

}

void CollisionModel::setPosition(vec3 position)
{

	PxTransform globalPose = rigidBody->getGlobalPose();
	globalPose.p.x = position.x;
	globalPose.p.y = position.y;
	globalPose.p.z = position.z;

	rigidBody->setGlobalPose(globalPose);

}

void CollisionModel::setRotation(quat rotation)
{

	PxTransform globalPose = rigidBody->getGlobalPose();
	globalPose.q.w = rotation.w;
	globalPose.q.x = rotation.x;
	globalPose.q.y = rotation.y;
	globalPose.q.z = rotation.z;

	rigidBody->setGlobalPose(globalPose);

}