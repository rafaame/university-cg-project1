#include "Camera.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Application.h"

int main()
{

	Camera *camera = new Camera();
	InputManager *inputManager = new InputManager(camera);
	WindowManager *windowManager = new WindowManager(inputManager);

	Application *application = new Application(windowManager, camera);

	if(!application->init())
		return -1;

	application->run();

	return 0;

}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}