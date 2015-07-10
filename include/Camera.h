#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

using namespace std;
using namespace glm;

class Camera
{

public:

	Camera();
	~Camera();

	vec3 getPosition()	{ return position; }
	double getSpeed() { return speed; }
	float getPitch() { return pitch; }
	float getYaw() { return yaw; }
	double getRotationSpeed() { return rotationSpeed; }
	mat4 getProjectionMatrix() { return projectionMatrix; }

	mat4 getRotationMatrix();
	mat4 getViewMatrix();
	vec3 getView();
	vec3 getUp();

	void setPosition(vec3 position)	{ this->position = position; }
	void setYaw(float yaw)	{ this->yaw = yaw; }
	void setPitch(float pitch) { this->pitch = pitch; }
	void setSpeed(double speed) { this->speed = speed;  }
	mat4 setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	void setRotationSpeed(double rotationSpeed) { this->rotationSpeed = rotationSpeed; }
	void setViewByMouse(vec2 mousePosition);
	void move(float speed);

protected:

	mat4 projectionMatrix;
	vec3 position;

	float speed;
	float rotationSpeed;
	double mouseSpeed;
	float yaw;
	float pitch;

};


#endif














