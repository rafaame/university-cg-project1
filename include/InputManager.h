#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "common.h"

#include "WindowManager.h"

using namespace std;
using namespace glm;

enum InputEvent_t
{

	INPUT_EVENT_PLAYER_FORWARD,
	INPUT_EVENT_PLAYER_BACKWARD,
	INPUT_EVENT_PLAYER_LEFT,
	INPUT_EVENT_PLAYER_RIGHT,
	INPUT_EVENT_PLAYER_JUMP,
	INPUT_EVENT_PLAYER_FLASHLIGHT,
	INPUT_EVENT_CAMERA_UPDATE,
	INPUT_EVENT_SPAWN_CUBE,
	INPUT_EVENT_PARAM_TESSELLATION_LEVEL,
	INPUT_EVENT_PARAM_DISPLACEMENT_FACTOR,
	INPUT_EVENT_PARAM_NORMAL_MAPS,
	INPUT_EVENT_PARAM_SPECULAR_MAPS,
	INPUT_EVENT_PARAM_SPECULAR_LIGHTING,
	INPUT_EVENT_PARAM_DIFFUSE_LIGHTING

};

struct InputEvent
{

	InputEvent(InputEvent_t type, void *data);

	InputEvent_t type;
	void *data;

};

class InputManager
{

public:

	InputManager();
	~InputManager();

	void scheduleEvent(InputEvent_t type, void *data = NULL) { scheduledEvents.push_back(InputEvent(type, data)); }
	vector<InputEvent> fetchScheduledEvents() { return scheduledEvents; }
	void flushScheduledEvents() { scheduledEvents.clear(); }

	void keyPressed(InputCode_t code);
	void keyPressedOnce(InputCode_t code);
	void mouseMoved(vec2 mousePosition);

protected:

	vector<InputEvent> scheduledEvents;

};

#endif