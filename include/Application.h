#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

using namespace std;

class WindowManager;
class PhysicsManager;
class Camera;
class Player;
class Model;
class PhysicsObject;

class Application
{
	
public:

	static const int screenWidth = 1024;
	static const int screenHeight = 768;

	Application(WindowManager *windowManager, Camera *camera, Player *player);
	~Application();

	WindowManager *getWindowManager() { return windowManager; }
	PhysicsManager *getPhysicsManager() { return physicsManager; }

	Camera *getCamera() { return camera; }
	Player *getPlayer() { return player; }

	bool init();
	void run();

protected:

	WindowManager *windowManager;
	PhysicsManager *physicsManager;

	Camera *camera;
	Player *player;
	vector<Model *> models;
	vector<PhysicsObject *> physicsObjects;

};

extern Application *gApplication;

#endif
