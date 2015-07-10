#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

using namespace std;

class WindowManager;
class RenderingManager;
class InputManager;
class PhysicsManager;

class Scene;

class Application
{

public:

	static Application* instance()
	{

		static Application instance;

		return &instance;

	}

	WindowManager *getWindowManager() { return windowManager; }
	RenderingManager *getRenderingManager() { return renderingManager; }
	InputManager *getInputManager() { return inputManager; }
	PhysicsManager *getPhysicsManager() { return physicsManager; }

	bool init();
	void run();

protected:

	WindowManager *windowManager;
	RenderingManager *renderingManager;
	InputManager *inputManager;
	PhysicsManager *physicsManager;

	Scene *scene;

private:

	Application();
	Application(Application const&);
	Application& operator= (Application const&);

};

#endif
