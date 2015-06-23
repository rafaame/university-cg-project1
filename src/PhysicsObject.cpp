#include "PhysicsObject.h"
#include "Model.h"
#include "CollisionModel.h"
#include "Camera.h"

PhysicsObject::PhysicsObject(CollisionModel_t type, Camera *camera)
{

	this->type = type;
	model = NULL;
	collisionModel = NULL;
	this->camera = camera;

}

PhysicsObject::~PhysicsObject()
{

	if(model)
		delete model;

}

bool PhysicsObject::loadFromObj(string filename, string vertexShaderFilename, string fragmentShaderFilename, string textureFilename)
{

	model = new Model();
	model->loadFromObj(filename, vertexShaderFilename, fragmentShaderFilename, textureFilename);
	model->setCamera(camera);

}

void PhysicsObject::initCollisionModel()
{

	collisionModel = new CollisionModel(type);
	collisionModel->initFromModel(model);
	
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

	//cout << "Rot: " << collisionModelRotation.x << " " << collisionModelRotation.y << " " << collisionModelRotation.z << endl;
	//cout << "Pos: " << collisionModelPosition.x << " " << collisionModelPosition.y << " " << collisionModelPosition.z << endl;

	model->setPosition(collisionModelPosition);
	model->setRotation(collisionModelRotation);

}

void PhysicsObject::render()
{

	model->render();

}