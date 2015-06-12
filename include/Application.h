#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

class WindowManager;
class Camera;

class Application
{
	
public:

	static const int screenWidth = 1024;
	static const int screenHeight = 768;

	Application(WindowManager *windowManager, Camera *camera);
	~Application();

	WindowManager *getWindowManager() { return windowManager; }

	Camera *getCamera() { return camera; }

	bool init();
	void run();

protected:

	WindowManager *windowManager;
	Camera *camera;

};

#endif
