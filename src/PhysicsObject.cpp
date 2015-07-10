#include "PhysicsObject.h"
#include "Model.h"
#include "CollisionModel.h"
#include "Shader.h"

PhysicsObject::PhysicsObject(CollisionModel_t type)
{

	this->type = type;
	model = new Model();;
	collisionModel = new CollisionModel(type);

}

PhysicsObject::~PhysicsObject()
{

	if(model)
		delete model;

}

bool PhysicsObject::loadFromObj(string filename, string textureFilename, Shader *shader)
{

	return model->loadFromObj(filename, textureFilename, shader);

}

void PhysicsObject::init(CollisionShape_t shape, vec3 dimensions, vec3 position, quat rotation, vec3 collisionModelPositionDisplacement, vec3 collisionModelRotationDisplacement)
{

	collisionModel->init(shape, dimensions, position, rotation, collisionModelPositionDisplacement, collisionModelRotationDisplacement);

}

vec3 PhysicsObject::getPosition()
{

	return collisionModel->getPosition();

}

quat PhysicsObject::getRotation()
{

	return collisionModel->getRotation();

}

void PhysicsObject::setPosition(vec3 position)
{

	collisionModel->setPosition(position);

}

void PhysicsObject::setRotation(quat rotation)
{

	collisionModel->setRotation(rotation);

}

void PhysicsObject::simulate()
{

	vec3 collisionModelPosition = collisionModel->getPosition();
	quat collisionModelRotation = collisionModel->getRotation();

	model->setPosition(collisionModelPosition);
	model->setRotation(collisionModelRotation);

}

void PhysicsObject::render()
{

	model->render();

}