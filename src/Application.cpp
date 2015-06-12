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
#include "Camera.h"
#include "Model.h"							

Model g_Model;

using namespace std;
using namespace glm;

Application::Application(WindowManager *windowManager, Camera *camera)
{

	this->windowManager = windowManager;
	this->camera = camera;

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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	glEnable(GL_CULL_FACE);

	g_Model.loadFromObj("test.obj", "Shaders/Shader.vertex", "Shaders/Shader.fragment", "uvmap.dds");
		
	camera->setPerspective(radians(60.0), screenWidth / (float) screenHeight, 0.01, 1000);
	camera->positionCamera(0, 0, 6,	0, 0);

	g_Model.setCamera(camera);
	
	g_Model.setPosition(vec3(0, 0, 0));

	return true;

}

void Application::run()
{

	while(windowManager->processInput(true))
	{

		TimeManager::instance()->getFrameRate(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		g_Model.render();

		windowManager->swapBuffers();

	}

}