//Rafael Andreatta Martins #USP 7564019
//Rafael Silva de Milha #USP 8139701

#include "Camera.h"
#include "Player.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Application.h"

using namespace std;

int main(int argc, char** argv)
{

	Magick::InitializeMagick(*argv);
	Application *application = Application::instance();

	if(!application->init())
		return 1;

	application->run();

	return 0;

}