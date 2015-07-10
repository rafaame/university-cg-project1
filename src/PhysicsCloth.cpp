#include "PhysicsCloth.h"

#include "Model.h"

using namespace std;
using namespace glm;
using namespace physx;

PhysicsCloth::PhysicsCloth()
{

	mesh = NULL;
	model = new Model();
	collisionCloth = new CollisionCloth();

}

PhysicsCloth::~PhysicsCloth()
{

	//delete model;
	//delete collisionCloth;

}

#include "Shader.h"

void PhysicsCloth::init(uint16_t dimension, string textureFilename, vec3 position, quat rotation, vec3 collisionClothPositionDisplacement, vec3 collisionClothRotationDisplacement)
{

	collisionCloth->init(dimension, position, rotation, collisionClothPositionDisplacement, collisionClothRotationDisplacement);

	vector<Vertex> vertices;
	vector<unsigned int> indices;

	PxClothMeshDesc *meshDesc = collisionCloth->getMeshDesc();
	unsigned int numberVertices = meshDesc->points.count;
	unsigned int numberIndices = meshDesc->triangles.count * 3;

	PxClothParticle *particles = (PxClothParticle *) meshDesc->points.data;
	PxU32 *clothIndices = (PxU32 *) meshDesc->triangles.data;

	for(unsigned int i = 0; i < numberVertices; i++)
	{

		uint32_t x = i / dimension;
		uint32_t y = i % dimension;

		PxClothParticle clothParticle = particles[i];
		vec2 textureCoordinate((float) x / dimension, (float) y / dimension);

		Vertex vertex
		(

			vec3(clothParticle.pos.x, clothParticle.pos.y, clothParticle.pos.z),
			textureCoordinate,
			vec3(1, 0, 0),
			vec3(0, 0, 0)

		);

		vertices.push_back(vertex);

	}

	for(unsigned int i = 0; i < numberIndices; i++)
	{

		unsigned int indice = clothIndices[i];

		indices.push_back(indice);

	}

	mesh = new Model::Mesh();
	mesh->init(vertices, indices);

	model->loadFromMesh(mesh, textureFilename);

}

vec3 PhysicsCloth::getPosition()
{

	return collisionCloth->getPosition();

}

quat PhysicsCloth::getRotation()
{

	return collisionCloth->getRotation();

}

void PhysicsCloth::setPosition(vec3 position)
{

	collisionCloth->setPosition(position);

}

void PhysicsCloth::setRotation(quat rotation)
{

	collisionCloth->setRotation(rotation);

}

void PhysicsCloth::simulate()
{

	vec3 collisionClothPosition = collisionCloth->getPosition();
	quat collisionClothRotation = collisionCloth->getRotation();

	//cout << "Rot: " << collisionClothRotation.x << " " << collisionClothRotation.y << " " << collisionClothRotation.z << endl;
	//cout << "Pos: " << collisionClothPosition.x << " " << collisionClothPosition.y << " " << collisionClothPosition.z << endl;

	model->setPosition(collisionClothPosition);
	model->setRotation(collisionClothRotation);

	PxClothParticleData* data = collisionCloth->getCloth()->lockParticleData();

	for(unsigned int i = 0; i < mesh->vertices.size(); i++)
		mesh->vertices[i].position = vec3(data->particles[i].pos.x, data->particles[i].pos.y, data->particles[i].pos.z);

	data->unlock();

	mesh->updateVertices();

}

void PhysicsCloth::render()
{

	model->render();

}