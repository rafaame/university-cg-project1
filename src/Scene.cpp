#include "Scene.h"

#include "TimeManager.h"
#include "WindowManager.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "Application.h"

#include "Player.h"
#include "PhysicsObject.h"
#include "PhysicsCloth.h"
#include "CollisionModel.h"
#include "Light.h"

using namespace std;
using namespace glm;

Scene::Scene()
{

	player = new Player();

}

Scene::~Scene()
{



}

bool Scene::init()
{

	/*const char *maze =
".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
 .  .  *  *                          .  .                    .  .
 .  .  *  *                          .  .                    .  .
 .  .  .  .  .  .  .  .  .  .        .  .        .  .        .  .
 .  .  .  .  .  .  .  .  .  .        .  .        .  .        .  .
 .  .                    .  .        .  .        .  .        .  .
 .  .                    .  .        .  .        .  .        .  .
 .  .        .  .        .  .        .  .        .  .        .  .
 .  .        .  .        .  .        .  .        .  .        .  .
 .  .        .  .        .  .        .  .        .  .        .  .
 .  .        .  .        .  .        .  .        .  .        .  .
 .  .        .  .  .  .  .  .        .  .        .  .  .  .  .  .
 .  .        .  .  .  .  .  .        .  .        .  .  .  .  .  .
 .  .                    .  .        .  .                    .  .
 .  .                    .  .        .  .                    .  .
 .  .        .  .        .  .        .  .  .  .  .  .        .  .
 .  .        .  .        .  .        .  .  .  .  .  .        .  .
 .  .        .  .                                      X  X  .  .
 .  .        .  .                                      X  X  .  .
 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .*/

 	const char *maze = ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .\n .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .\n .  .  *  *                          .  .                    .  .\n .  .  *  *                          .  .                    .  .\n .  .  .  .  .  .  .  .  .  .        .  .        .  .        .  .\n .  .  .  .  .  .  .  .  .  .        .  .        .  .        .  .\n .  .                    .  .        .  .        .  .        .  .\n .  .                    .  .        .  .        .  .        .  .\n .  .        .  .        .  .        .  .        .  .        .  .\n .  .        .  .        .  .        .  .        .  .        .  .\n .  .        .  .        .  .        .  .        .  .        .  .\n .  .        .  .        .  .        .  .        .  .        .  .\n .  .        .  .  .  .  .  .        .  .        .  .  .  .  .  .\n .  .        .  .  .  .  .  .        .  .        .  .  .  .  .  .\n .  .                    .  .        .  .                    .  .\n .  .                    .  .        .  .                    .  .\n .  .        .  .        .  .        .  .  .  .  .  .        .  .\n .  .        .  .        .  .        .  .  .  .  .  .        .  .\n .  .        .  .                                      X  X  .  .\n .  .        .  .                                      X  X  .  .\n .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .\n .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .";
 	//const char *maze = ".    .    .    .    .    .    .    .    .    .    .\n  .    *                        .                   .\n  .    .    .    .    .         .         .         .\n  .                   .         .         .         .\n  .         .         .         .         .         .\n  .         .         .         .         .         .\n  .         .    .    .         .         .    .    .\n  .                   .         .                   .\n  .         .         .         .    .    .         .\n  .         .                                  X    .\n  .    .    .    .    .    .    .    .    .    .    .";

 	//const char *maze = ".  .  .  .  .  .  .  .  .  .  .  .  *  .                       .  .     .     .  .  .  .  .     .  .           .     .           .  .  .  .  .  .     .     .  .  .  .           .           .     .  .     .     .     .  .  .     .  .     .     .     .           .  .     .     .     .     .     .  .     .                 .  X  .  .  .  .  .  .  .  .  .  .  .  .";

 	double playerX = 0, playerY = 0, playerZ = 0;

 	int i = 0;
 	char mazeChar = maze[i];
 	while(mazeChar != '\0')
 	{

 		int planeX = (i % 66) / 3;
		int planeY = i / 66;

		int x = planeX * 4;
		int y = planeY * 4;

		int iNorth = i - 66;
		int iSouth = i + 66;
		int iWest = i - 3;
		int iEast = i + 3;
		int iNorthWest = iNorth - 3;
		int iNorthEast = iNorth + 3;
		int iSouthWest = iSouth - 3;
		int iSouthEast = iSouth + 3;

 		if(mazeChar == '.' && !(planeX == 0 || planeX == 21 || planeY == 0 || planeY == 21))
 		{

 			string modelFilename;
 			vec3 modelTranslation;
 			float modelRotation;

 			CollisionShape_t collisionShape = COLLISION_SHAPE_BOX;
 			vec3 collisionModelDimension = vec3(1,1,1);
 			vec3 collisionModelPositionDisplacement;
 			vec3 collisionModelRotationDisplacement;

 			bool cNorth = maze[iNorth] == '.';
 			bool cSouth = maze[iSouth] == '.';
 			bool cWest = maze[iWest] == '.';
 			bool cEast = maze[iEast] == '.';
 			bool cNorthWest = maze[iNorthWest] == '.';
 			bool cNorthEast = maze[iNorthEast] == '.';
 			bool cSouthWest = maze[iSouthWest] == '.';
 			bool cSouthEast = maze[iSouthEast] == '.';

 			if(cNorth && cSouth && cWest && cEast &&
 				cNorthWest && cNorthEast && cSouthWest && !cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner.obj";
 				modelRotation = 0.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(4.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(1.0f, 2.0f, 1.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 45.0f, 0.0f);

 			}
 			else if(cNorth && cSouth && cWest && cEast &&
 				!cNorthWest && cNorthEast && cSouthWest && cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner.obj";
 				modelRotation = 180.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(4.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(-1.0f, 2.0f, -1.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 45.0f, 0.0f);

 			}
 			else if(cNorth && cSouth && cWest && cEast &&
 				cNorthWest && cNorthEast && !cSouthWest && cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner.obj";
 				modelRotation = -90.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(4.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(-1.0f, 2.0f, 1.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 45.0f, 0.0f);

 			}
 			else if(cNorth && cSouth && cWest && cEast &&
 				cNorthWest && !cNorthEast && cSouthWest && cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner.obj";
 				modelRotation = 90.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(4.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(1.0f, 2.0f, -1.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 45.0f, 0.0f);

 			}
 			else if(!cNorth && cSouth && cWest && !cEast &&
 				!cNorthWest && !cNorthEast && cSouthWest && !cSouthEast && maze[i - 6] != '.')
 			{

 				modelFilename = "data/models/wall-corner-inverse-double.obj";
 				modelRotation = -90.0f;

 				collisionShape = COLLISION_SHAPE_CAPSULE;
 				collisionModelDimension = vec3(2.0f, 2.0f, 0.0f);
 				collisionModelPositionDisplacement = vec3(-2.0f, 2.0f, 2.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 90.0f);

 			}
 			else if(cNorth && !cSouth && !cWest && cEast &&
 				!cNorthWest && cNorthEast && !cSouthWest && !cSouthEast && maze[i + 6] != '.')
 			{

 				modelFilename = "data/models/wall-corner-inverse-double.obj";
 				modelRotation = 90.0f;

 				collisionShape = COLLISION_SHAPE_CAPSULE;
 				collisionModelDimension = vec3(2.0f, 2.0f, 0.0f);
 				collisionModelPositionDisplacement = vec3(2.0f, 2.0f, -2.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 90.0f);

 			}
 			else if(!cNorth && cSouth && cWest && !cEast &&
 				!cNorthWest && !cNorthEast && cSouthWest && !cSouthEast && maze[i + 66 * 2] != '.')
 			{

 				modelFilename = "data/models/wall-corner-inverse-double.obj";
 				modelTranslation.z = 4.0f;
 				modelRotation = 180.0f;

 				collisionShape = COLLISION_SHAPE_CAPSULE;
 				collisionModelDimension = vec3(2.0f, 2.0f, 0.0f);
 				collisionModelPositionDisplacement = vec3(-2.0f, 2.0f, -2.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 90.0f);

 			}
 			else if(!cNorth && cSouth && cWest && !cEast &&
 				!cNorthWest && !cNorthEast && cSouthWest && !cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner-inverse.obj";
 				modelTranslation.x = 0.3f;
 				modelTranslation.z = -0.3f;
 				modelRotation = -90.0f;

 				collisionShape = COLLISION_SHAPE_CAPSULE;
 				collisionModelDimension = vec3(1.7f, 2.0f, 0.0f);
 				collisionModelPositionDisplacement = vec3(-2.0f, 2.0f, 2.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 90.0f);

 			}
 			else if(cNorth && !cSouth && !cWest && cEast &&
 				!cNorthWest && cNorthEast && !cSouthWest && !cSouthEast)
 			{

 				modelFilename = "data/models/wall-corner-inverse.obj";
 				modelTranslation.x = -0.3f;
 				modelTranslation.z = 0.3f;
 				modelRotation = 90.0f;

 				collisionShape = COLLISION_SHAPE_CAPSULE;
 				collisionModelDimension = vec3(1.7f, 2.0f, 0.0f);
 				collisionModelPositionDisplacement = vec3(2.0f, 2.0f, -2.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 90.0f);

 			}
 			else if(cNorth && !cSouth && cWest && cEast &&
 				cNorthWest && cNorthEast/* && !cSouthWest && !cSouthEast*/)
 			{

 				modelFilename = "data/models/wall.obj";
 				modelRotation = 0.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(2.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(0.0f, 2.0f, -0.5f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 0.0f);

 			}
 			else if(!cNorth && cSouth && cWest && cEast &&
 				/*!cNorthWest && !cNorthEast && */cSouthWest && cSouthEast)
 			{

 				modelFilename = "data/models/wall.obj";
 				modelRotation = 180.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(2.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(0.0f, 2.0f, 0.5f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 0.0f);

 			}
 			else if(cNorth && cSouth && cWest && !cEast &&
 				cNorthWest /*&& !cNorthEast*/ && cSouthWest/* && !cSouthEast*/)
 			{

 				modelFilename = "data/models/wall.obj";
 				modelRotation = 90.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(2.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(-0.5f, 2.0f, 0.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 0.0f);

 			}
 			else if(cNorth && cSouth && !cWest && cEast &&
 				/*!cNorthWest && */cNorthEast/* && !cSouthWest */&& cSouthEast)
 			{

 				modelFilename = "data/models/wall.obj";
 				modelRotation = -90.0f;

 				collisionShape = COLLISION_SHAPE_BOX;
 				collisionModelDimension = vec3(2.0f, 4.0f, 0.5f);
 				collisionModelPositionDisplacement = vec3(0.5f, 2.0f, 0.0f);
 				collisionModelRotationDisplacement = vec3(0.0f, 0.0f, 0.0f);

 			}

 			if(modelFilename.length())
 			{

	 			PhysicsObject *wall = new PhysicsObject(COLLISION_MODEL_STATIC);
				wall->loadFromObj(modelFilename, "data/textures/jagged-cave-wall");
				wall->init(collisionShape, collisionModelDimension, vec3(x, 0, y) + modelTranslation, quat_cast(rotate(mat4(), radians(modelRotation), vec3(0.0f, 1.0f, 0.0f))), collisionModelPositionDisplacement, collisionModelRotationDisplacement);

				addPhysicsObject(wall);

 			}

 		}
 		else if(mazeChar == ' ')
 		{

 			if(rand() % 100 > 60)
 			{

 				uint8_t textureProb = rand() % 100;

 				string textureFilename;
 				if(textureProb > 50 )
 					textureFilename = "data/textures/wooden-crate";
 				else
 					textureFilename = "data/textures/reinforced-metal-wall";

 				PhysicsObject *box = new PhysicsObject(COLLISION_MODEL_DYNAMIC);
				box->loadFromObj("data/models/block.obj", textureFilename);
				box->init(COLLISION_SHAPE_BOX, vec3(1, 1, 1), vec3(x, 5, y), quat_cast(rotate(mat4(), radians(45.0f), vec3(0.0f, 1.0f, 0.0f))), vec3(), vec3());

				addPhysicsObject(box);

		 	}

 		}
 		else if(mazeChar == 'X')
 		{

 			static bool createdFlag = false;

 			if(!createdFlag)
 			{

 				createdFlag = true;

	 			PhysicsCloth *cloth = new PhysicsCloth();
			    cloth->init(30, "data/textures/cloth", vec3(x, 5.5f, y), quat(), vec3(), vec3());
			    addPhysicsCloth(cloth);

			}

 		}
 		else if(mazeChar == '*')
 		{

 			static bool foundStart = false;

 			if(!foundStart)
 			{

 				foundStart = true;

 				playerX = x;
 				playerY = 3;
 				playerZ = y;

 			}

 		}

 		PhysicsObject *ground = new PhysicsObject(COLLISION_MODEL_STATIC);
		ground->loadFromObj("data/models/plane.obj", "data/textures/tiled-wood");
		ground->init(COLLISION_SHAPE_BOX, vec3(2, 0.5f, 2), vec3(x, 0, y), quat(), vec3(0, -0.5f, 0), vec3());
		addPhysicsObject(ground);

		PhysicsObject *roof = new PhysicsObject(COLLISION_MODEL_STATIC);
		roof->loadFromObj("data/models/plane.obj", "data/textures/flooded-mud-ground");
		roof->init(COLLISION_SHAPE_BOX, vec3(2, 0.5f, 2), vec3(x, 4, y), quat_cast(rotate(mat4(), radians(180.0f), vec3(1.0f, 0.0f, 0.0f))), vec3(0, 2, 0), vec3());
		addPhysicsObject(roof);

 		i += 3;
 		mazeChar = maze[i];

 	}

 	player->spawn(vec3(playerX, playerY, playerZ));

 	pointLight = new PointLight();
 	pointLight->position = vec3(playerX, 2, playerZ);
	pointLight->color = vec3(1, 1, 1);
	pointLight->ambientIntensity = 1;
	pointLight->diffuseIntensity = 1;
	pointLight->attenuation.linear = 0.1f;
	pointLight->attenuation.exp = 0.0f;
	Application::instance()->getRenderingManager()->getLightingShader()->addPointLight(pointLight);

    return true;

}

void Scene::addModel(Model *model)
{

	models.push_back(model);

}

void Scene::addPhysicsObject(PhysicsObject *physicsObject)
{

	physicsObjects.push_back(physicsObject);

	addModel(physicsObject->getModel());

}

void Scene::addPhysicsCloth(PhysicsCloth *physicsCloth)
{

	physicsClothes.push_back(physicsCloth);

	addModel(physicsCloth->getModel());

}

void Scene::update()
{

	updatePointLight();

	for(auto it = physicsObjects.begin(); it != physicsObjects.end(); it++)
		(*it)->simulate();

	for(auto it = physicsClothes.begin(); it != physicsClothes.end(); it++)
		(*it)->simulate();

	player->simulate();

}

void Scene::updatePointLight()
{

	double delta = TimeManager::instance()->getDelta();
	float displacement = pointLight->position.x > 50.0f ? -2.0f : 2.0f;

	pointLight->position += vec3(displacement, 0, 0) * (float) delta;

}