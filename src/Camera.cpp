//***********************************************************************															 
//	
//		Julio Trasferetti Nicolucci - 8517251 
//                                                                       
//		Trabalho CG - Labirinto									 																	 
//***********************************************************************

#include "Camera.h"

Camera::Camera()
{
	
	// Posição default da camera
	Position = vec3(0.0, 0.0, 0.0);

}

mat4 Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{

	ProjectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);

	return ProjectionMatrix;
	
}

void Camera::PositionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch)
{

	Position = vec3(positionX, positionY, positionZ);

	Yaw = yaw;
	Pitch = pitch;

}

mat4 Camera::GetRotationMatrix()
{

	mat4 rotationMatrix(1.0f);

	rotationMatrix = rotate(rotationMatrix, Pitch, vec3(1, 0, 0));
	rotationMatrix = rotate(rotationMatrix, Yaw, vec3(0, 1, 0));

	return rotationMatrix;

}

mat4 Camera::GetViewMatrix()
{

	return GetRotationMatrix() * inverse(translate(mat4(), Position));

}

vec3 Camera::GetView()
{

	vec4 viewVector = inverse(GetRotationMatrix()) * vec4(0, 0, -1, 1);

	return vec3(viewVector);

}

vec3 Camera::GetUp()
{

	vec4 upVector = inverse(GetRotationMatrix()) * vec4(0, 1, 0, 1);

	return vec3(upVector);

}

void Camera::MoveCamera(float speed)
{

	vec3 viewVector = GetView();

	Position.x += viewVector.x * speed;		
	Position.z += viewVector.z * speed;

}

void Camera::SetViewByMouse(float xOffset, float yOffset)
{

	Yaw += xOffset * MouseSpeed;
	Pitch += yOffset * MouseSpeed;

	if(Yaw > 2 * PI)
		Yaw = 0;

	// Cap the yaw between 0 and 360
	if(Yaw < 0)
		Yaw = 2 * PI;

	if(Pitch > radians(75.0f))
		Pitch = radians(75.0f);

	if(Pitch < radians(-75.0f))
		Pitch = radians(-75.0f);

}