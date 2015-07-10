#include "Camera.h"

using namespace std;
using namespace glm;

Camera::Camera()
{

	position = vec3(0.0, 0.0, 0.0);
	speed = 1;
	rotationSpeed = 2;
	mouseSpeed = 0.001;
	yaw = 0;
	pitch = 0;

}

Camera::~Camera()
{



}

mat4 Camera::setPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{

	projectionMatrix = perspective(fieldOfView, aspectRatio, nearPlane, farPlane);

	return projectionMatrix;

}

mat4 Camera::getRotationMatrix()
{

	mat4 rotationMatrix(1.0);

	rotationMatrix = rotate(rotationMatrix, pitch, vec3(1, 0, 0));
	rotationMatrix = rotate(rotationMatrix, yaw, vec3(0, 1, 0));

	return rotationMatrix;

}

mat4 Camera::getViewMatrix()
{

	return getRotationMatrix() * inverse(translate(mat4(), position));

}

vec3 Camera::getView()
{

	vec4 viewVector = inverse(getRotationMatrix()) * vec4(0, 0, -1, 1);

	return vec3(viewVector);

}

vec3 Camera::getUp()
{

	vec4 upVector = inverse(getRotationMatrix()) * vec4(0, 1, 0, 1);

	return vec3(upVector);

}

void Camera::move(float speed)
{

	vec3 viewVector = getView();

	position.x += viewVector.x * speed;
	position.z += viewVector.z * speed;

}

void Camera::setViewByMouse(vec2 mousePosition)
{

	yaw += mousePosition.x * mouseSpeed;
	pitch += mousePosition.y * mouseSpeed;

	if(yaw > 2 * PI)
		yaw = 0;

	// Cap the yaw between 0 and 360
	if(yaw < 0)
		yaw = 2 * PI;

	if(pitch > radians(75.0))
		pitch = radians(75.0);

	if(pitch < radians(-75.0))
		pitch = radians(-75.0);

}