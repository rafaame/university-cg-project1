#include "InputManager.h"
#include "TimeManager.h"
#include "Camera.h"
#include "Player.h"

InputManager::InputManager(Camera *camera, Player *player)
{

	this->camera = camera;
	this->player = player;

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

			//camera->move(camera->getSpeed() * TimeManager::instance()->getDelta());
			player->move(camera->getSpeed());

			break;
		
		case Down:
		case S:
		case s:

			//camera->move(-1 * camera->getSpeed() * TimeManager::instance()->getDelta());
			player->move(-camera->getSpeed());

			break;

		case Space:

			player->jump();

			break;		

	}

}

void InputManager::mouseMoved(float mouseX, float mouseY)
{
	
	camera->setViewByMouse(mouseX, mouseY);

}