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
#include "RenderingManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Light.h"
#include "PhysicsObject.h"

using namespace std;
using namespace glm;

Application::Application()
{

	physicsManager = new PhysicsManager();
	inputManager = new InputManager();
	windowManager = new WindowManager();
	renderingManager = new RenderingManager();

}

/*Application::~Application()
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

}*/

bool Application::init()
{

	vec2 windowSize(1280, 720);

	if(!windowManager || !windowManager->init(windowSize, "CG -  T1 - Maze", false))
		return false;

	if(!renderingManager->init())
		return false;

	if(!physicsManager->init())
		return false;

	scene = new Scene();
	scene->init();

	return true;

}

void Application::run()
{

	while(windowManager->processInput(true))
	{

		TimeManager::instance()->getFrameRate(true);

		{

			vector<InputEvent> inputEvents = inputManager->fetchScheduledEvents();
			Player *player = scene->getPlayer();
			Camera *camera = player->getCamera();

			for(auto it = inputEvents.begin(); it != inputEvents.end(); it++)
			{

				InputEvent inputEvent = (*it);

				switch(inputEvent.type)
				{

					case INPUT_EVENT_PLAYER_FORWARD:

						player->move(camera->getView(), 1.0f);

						break;

					case INPUT_EVENT_PLAYER_BACKWARD:

						player->move(-camera->getView(), 1.0f);

						break;

					case INPUT_EVENT_PLAYER_LEFT:

						player->move(camera->getView(), 1.0f);

						break;

						case INPUT_EVENT_PLAYER_RIGHT:

						player->move(camera->getView(), 1.0f);

						break;


					case INPUT_EVENT_PLAYER_JUMP:

						player->jump();

						break;

					case INPUT_EVENT_PLAYER_FLASHLIGHT:

						player->toggleFlashlight();

						break;

					case INPUT_EVENT_SPAWN_CUBE:
					{

						PhysicsObject *cube = new PhysicsObject(COLLISION_MODEL_DYNAMIC);
						cube->loadFromObj("data/models/block.obj", "data/textures/wooden-crate");
						cube->init(COLLISION_SHAPE_BOX, vec3(1, 1, 1), player->getPosition() + player->getCamera()->getView() * vec3(5, 2, 0), quat_cast(rotate(mat4(), radians(30.0f), vec3(1.0f, 0.0f, 0.0f))), vec3(), vec3());

						scene->addPhysicsObject(cube);

						break;

					}

					case INPUT_EVENT_CAMERA_UPDATE:
					{

						vec2 *mousePosition = (vec2 *) inputEvent.data;

						camera->setViewByMouse(*mousePosition);

						break;

					}

					case INPUT_EVENT_PARAM_TESSELLATION_LEVEL:
					{

						float *data = (float *) inputEvent.data;

						float tessellationLevel = renderingManager->getLightingShader()->getTessellationLevelParam();
						tessellationLevel += *data;

						if(tessellationLevel < 0.0f)
							tessellationLevel = 0.0f;

						renderingManager->getLightingShader()->setTessellationLevelParam(tessellationLevel);

						break;

					}

					case INPUT_EVENT_PARAM_DISPLACEMENT_FACTOR:
					{

						float *data = (float *) inputEvent.data;

						float dispFactor = renderingManager->getLightingShader()->getDisplacementFactorParam();
						dispFactor += *data;

						if(dispFactor < 0.0f)
							dispFactor = 0.0f;

						renderingManager->getLightingShader()->setDisplacementFactorParam(dispFactor);

						break;

					}

					case INPUT_EVENT_PARAM_NORMAL_MAPS:
					{

						static bool useNormalMaps = true;

						useNormalMaps = !useNormalMaps;

						renderingManager->getLightingShader()->setUseNormalMapsParam(useNormalMaps);

						break;

					}

					case INPUT_EVENT_PARAM_SPECULAR_MAPS:
					{

						static bool useSpecularMaps = true;

						useSpecularMaps = !useSpecularMaps;

						renderingManager->getLightingShader()->setUseSpecularMapsParam(useSpecularMaps);

						break;

					}

					case INPUT_EVENT_PARAM_DIFFUSE_LIGHTING:
					{

						static bool diffuseLighting = true;

						diffuseLighting = !diffuseLighting;

						renderingManager->getLightingShader()->setDiffuseLightingParam(diffuseLighting);

						break;

					}

					case INPUT_EVENT_PARAM_SPECULAR_LIGHTING:
					{

						static bool specularLighting = true;

						specularLighting = !specularLighting;

						renderingManager->getLightingShader()->setSpecularLightingParam(specularLighting);

						break;

					}

				}

			}

			inputManager->flushScheduledEvents();

		}

		physicsManager->simulate();

		scene->update();
		renderingManager->renderScene(scene);

		/*pointLights[0].Color = vec3(1.0f, 0.0f, 0.0f);
	    pointLights[0].AmbientIntensity = 10.0f;
	    pointLights[0].DiffuseIntensity = 10.0f;
	    pointLights[0].Position = camera->getPosition();
	    //pointLights[0].Attenuation.Constant = 2.0f;
	    //pointLights[0].Attenuation.Linear = 1.0f;
	    pointLights[0].Attenuation.Exp = 1;*/

	    /*spotLights[0].Color = vec3(1.0f, 1.0f, 1.0f);
	    spotLights[0].AmbientIntensity = 2.0f;
	    spotLights[0].DiffuseIntensity = 2.0f;
	    spotLights[0].Position = camera->getPosition();
	    spotLights[0].Direction = camera->getView();
	    //spotLights[0].Position = vec3(6, 0, 5.5);
	    //spotLights[0].Direction = vec3(0, 0, 1);
	    spotLights[0].Cutoff = 30;
	    //spotLights[0].Attenuation.Constant = 2.0f;
	    //spotLights[0].Attenuation.Linear = 1.0f;
	    spotLights[0].Attenuation.Exp = 1;

		lightingShader->SetSpotLights(1, spotLights);

		//cout << "error: " << glGetError() << endl;
		//cout << "CameraPos: " << camera->getPosition().x << " " << camera->getPosition().y << " " << camera->getPosition().z << endl;

		windowManager->swapBuffers();*/

		//cout << "error: " << glGetError() << endl;
		//exit(1);

	}

}