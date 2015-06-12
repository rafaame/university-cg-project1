#include "InputManager.h"
#include "TimeManager.h"
#include "Camera.h"

InputManager::InputManager(Camera *camera)
{

	this->camera = camera;

}

InputManager::~InputManager()
{



}

void InputManager::keyPressed(InputCode_t code)
{
	
	switch(code)
	{

		case Up:
		case W:
		case w:

			camera->move(camera->getSpeed() * TimeManager::instance()->getDelta());

			break;
		
		case Down:
		case S:
		case s:

			camera->move(-1 * camera->getSpeed() * TimeManager::instance()->getDelta());

			break;		

	}

}

void InputManager::mouseMoved(float mouseX, float mouseY)
{
	
	camera->setViewByMouse(mouseX, mouseY);

}