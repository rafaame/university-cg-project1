#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "common.h"

using namespace std;

class InputManager;

class WindowManager
{

public:

	WindowManager(InputManager *inputManager);
	~WindowManager();

	bool init(int width, int height, std::string title, bool fullscreen = false);
	void swapBuffers();
	bool processInput(bool continueGame);

	InputManager *getInputManager() { return inputManager; }

private:

	GLFWwindow* window;
	InputManager *inputManager;

};

#endif