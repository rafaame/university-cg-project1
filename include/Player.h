#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

using namespace std;
using namespace glm;
using namespace physx;

class Camera;
class Application;

struct SpotLight;

class Player
{

public:

	Player();
	~Player();

	void spawn(vec3 position);

	vec3 getPosition();
	Camera *getCamera() { return camera; }

	void setPosition(vec3 position);

	void move(vec3 direction, float speed);
	void jump();
	void toggleFlashlight();

	void simulate();

protected:

	vec3 dispVector;
	vec3 velocity;

	PxCapsuleController *capsuleController;
	Camera *camera;
	SpotLight *flashlight;

};

#endif