//Rafael Andreatta Martins #USP 7564019
//Rafael Silva de Milha #USP 8139701

#include "Camera.h"
#include "Player.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Application.h"

Application *gApplication = NULL;

int main()
{

	Camera *camera = new Camera();
	Player *player = new Player(camera);
	InputManager *inputManager = new InputManager(camera, player);
	WindowManager *windowManager = new WindowManager(inputManager);

	gApplication = new Application(windowManager, camera, player);

	if(!gApplication->init())
		return -1;

	gApplication->run();

	return 0;

}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}