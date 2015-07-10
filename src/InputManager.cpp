#include "InputManager.h"
#include "TimeManager.h"

InputEvent::InputEvent(InputEvent_t type, void *data)
{

	this->type = type;
	this->data = data;

}

InputManager::InputManager()
{



}

InputManager::~InputManager()
{



}

void InputManager::keyPressed(InputCode_t code)
{

	switch(code)
	{

		case arrowUp:
		case W:
		case w:

			scheduleEvent(INPUT_EVENT_PLAYER_FORWARD);

			break;

		case arrowDown:
		case S:
		case s:

			scheduleEvent(INPUT_EVENT_PLAYER_BACKWARD);

			break;

		case arrowLeft:
		case A:
		case a:

			scheduleEvent(INPUT_EVENT_PLAYER_LEFT);

			break;

		case arrowRight:
		case D:
		case d:

			scheduleEvent(INPUT_EVENT_PLAYER_RIGHT);

			break;

	}

}

void InputManager::keyPressedOnce(InputCode_t code)
{

	switch(code)
	{

		case space:

			scheduleEvent(INPUT_EVENT_PLAYER_JUMP);

			break;

		case F:
		case f:

			scheduleEvent(INPUT_EVENT_PLAYER_FLASHLIGHT);

			break;

		case Q:
		case q:

			scheduleEvent(INPUT_EVENT_SPAWN_CUBE);

			break;

		case P:
		case p:
		{

			float *data = new float();
			*data = 1.0f;

			scheduleEvent(INPUT_EVENT_PARAM_TESSELLATION_LEVEL, data);

			break;

		}

		case L:
		case l:
		{

			float *data = new float();
			*data = -1.0f;

			scheduleEvent(INPUT_EVENT_PARAM_TESSELLATION_LEVEL, data);

			break;

		}

		case O:
		case o:
		{

			float *data = new float();
			*data = 0.1f;

			scheduleEvent(INPUT_EVENT_PARAM_DISPLACEMENT_FACTOR, data);

			break;

		}

		case K:
		case k:
		{

			float *data = new float();
			*data = -0.1f;

			scheduleEvent(INPUT_EVENT_PARAM_DISPLACEMENT_FACTOR, data);

			break;

		}

		case I:
		case i:

			scheduleEvent(INPUT_EVENT_PARAM_NORMAL_MAPS);

			break;

		case J:
		case j:

			scheduleEvent(INPUT_EVENT_PARAM_SPECULAR_MAPS);

			break;

		case U:
		case u:

			scheduleEvent(INPUT_EVENT_PARAM_DIFFUSE_LIGHTING);

			break;

		case H:
		case h:

			scheduleEvent(INPUT_EVENT_PARAM_SPECULAR_LIGHTING);

			break;

	}

}

void InputManager::mouseMoved(vec2 mousePosition)
{

	vec2 *data = new vec2(mousePosition);

	scheduleEvent(INPUT_EVENT_CAMERA_UPDATE, data);

}