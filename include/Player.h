#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"	

using namespace std;
using namespace glm;
using namespace physx;

class Camera;
class Application;

class Player
{

public:
	
	Player(Camera *camera);
	~Player();

	void spawn(vec3 position);

	vec3 getPosition();

	void setPosition(vec3 position);

	void move(double speed);
	void jump();

	void simulate();
	
protected:

	vec3 dispVector;
	vec3 velocity;

	PxCapsuleController *capsuleController;
	Camera *camera;

};

extern Application *gApplication;

#endif











