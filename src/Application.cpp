//***********************************************************************															 
//	
//		Rafael Andreatta Martins - 7564019
//		Rafael Silva de Milha - 8139701
//
//		Trabalho CG - Labirinto									 																	 
//***********************************************************************

#include "Application.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "PhysicsManager.h"
#include "Camera.h"
#include "Player.h"
#include "Model.h"
#include "PhysicsObject.h"					

using namespace std;
using namespace glm;

Application::Application(WindowManager *windowManager, Camera *camera, Player *player)
{

	this->windowManager = windowManager;
	this->physicsManager = new PhysicsManager();
	this->camera = camera;
	this->player = player;

}

Application::~Application()
{

	if(windowManager)
	{

		delete windowManager;
		windowManager = NULL;
		
	}
	
	if(camera)
	{

		delete camera;
		camera = NULL;

	}

}

bool Application::init()
{

	if(!windowManager || !windowManager->init(screenWidth, screenHeight, "CG -  T1 - Maze", false))
		return false;

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	glEnable(GL_CULL_FACE);

	physicsManager->init();

	camera->setPerspective(radians(60.0), screenWidth / (float) screenHeight, 0.01, 1000);
	camera->positionCamera(0, 0, 6,	0, 0);

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

 	double playerX = 0, playerY = 0, playerZ = 0;

 	int i = 0;
 	char mazeChar = maze[i];
 	while(mazeChar != '\0')
 	{

 		int planeX = (i % 66) / 3;
		int planeY = i / 66;

		int x = planeX * 2;
		int y = planeY * 2;

 		if(mazeChar == '.')
 		{

 			PhysicsObject *way = new PhysicsObject(COLLISION_MODEL_STATIC, camera);
 			way->loadFromObj("block.obj", "Shaders/Shader.vertex", "Shaders/Shader.fragment", "uvmap.dds");
 			way->initCollisionModel();
 			way->setPosition(vec3(x, 0, y));
 			physicsObjects.push_back(way);

 			//vec3 pos(x, 0, y);
 			//cout << "Pos: (" << i << ") " << planeX << " " << planeY << endl;

 		}
 		else if(mazeChar == ' ')
 		{

 			if(rand() % 100 > 95)
 			{

	 			PhysicsObject *physicsObject = new PhysicsObject(COLLISION_MODEL_DYNAMIC, camera);
			 	physicsObject->loadFromObj("test.obj", "Shaders/Shader.vertex", "Shaders/Shader.fragment", "uvmap.dds");
			 	physicsObject->initCollisionModel();
			 	physicsObject->setPosition(vec3(x, 10, y));
			 	//physicsObject->setRotation(quat(0, 1, 1, 0));
			 	physicsObjects.push_back(physicsObject);

		 	}

 		}
 		else if(mazeChar == 'X')
 		{

 			static bool createdFlag = false;

 			if(!createdFlag)
 			{

 				createdFlag = true;

	 			PhysicsObject *way = new PhysicsObject(COLLISION_MODEL_STATIC, camera);
				way->loadFromObj("flag.obj", "Shaders/Shader.vertex", "Shaders/Flag.fragment", "uvmap.dds");
				way->initCollisionModel();
				way->setPosition(vec3(x, -1, y));
				physicsObjects.push_back(way);

			}

 		}
 		else if(mazeChar == '*')
 		{

 			static bool foundStart = false;

 			if(!foundStart)
 			{

 				foundStart = true;

 				playerX = x;
 				playerY = 5;
 				playerZ = y;

 			}

 		}

 		/*PhysicsObject *physicsObject = new PhysicsObject(COLLISION_MODEL_DYNAMIC, camera);
	 	physicsObject->loadFromObj("test.obj", "Shaders/Shader.vertex", "Shaders/Shader.fragment", "uvmap.dds");
	 	physicsObject->initCollisionModel();
	 	physicsObject->setPosition(vec3(0, 10, 0));
	 	//physicsObject->setRotation(quat(0, 1, 1, 0));
	 	physicsObjects.push_back(physicsObject);*/

 		i += 3;
 		mazeChar = maze[i];

 	}

 	player->spawn(vec3(playerX, playerY, playerZ));
	
	return true;

}

void Application::run()
{

	while(windowManager->processInput(true))
	{

		TimeManager::instance()->getFrameRate(true);

		physicsManager->simulate();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		for(auto it = models.begin(); it != models.end(); it++)
		{

			Model *model = (*it);

			model->render();

		}

		for(auto it = physicsObjects.begin(); it != physicsObjects.end(); it++)
		{

			PhysicsObject *physicsObject = (*it);

			physicsObject->simulate();
			physicsObject->render();

		}

		player->simulate();

		windowManager->swapBuffers();

	}

}