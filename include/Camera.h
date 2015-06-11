#ifndef Camera_H
#define Camera_H

#define PI 3.14159265358979323846264338327950288		
#define GLM_FORCE_RADIANS								

#include <fstream>
#include <glm/glm.hpp>									
#include <glm/gtc/matrix_transform.hpp>					
#include <glm/gtx/transform2.hpp>						
using namespace glm;


class Camera 
{
public:

	Camera();
		
	mat4 SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
		
	mat4 GetRotationMatrix();
		
	mat4 GetProjectionMatrix() { return ProjectionMatrix; }
		
	mat4 GetViewMatrix();
		
	void SetPosition(vec3 position)	{ Position = position; }
	vec3 GetPosition()	{ return Position; }
		
	vec3 GetView();
		
	vec3 GetUp();

	
	float GetYaw() { return Yaw; }
	void SetYaw(float yaw)	{ Yaw = yaw; }
	float GetPitch() { return Pitch; }
	void SetPitch(float pitch) { Pitch = pitch; }
		
	void SetSpeed(double speed) { Speed = speed;  }
	double GetSpeed() { return Speed; }

	
	void SetRotationSpeed(double speed) { RotationSpeed = speed; }
	double GetRotationSpeed() { return RotationSpeed; }

	void SetViewByMouse(float mouseX, float mouseY);
			
	void PositionCamera(float positionX, float positionY, float positionZ, float yaw, float pitch);

	void MoveCamera(float speed);

protected:

	mat4 ProjectionMatrix;								
	vec3 Position;										

	float Speed = 5.0;									
	float RotationSpeed = 2;							
	
	double MouseSpeed = 0.001;							
	
	float Yaw = 0;										
	float Pitch = 0;									
};


#endif 














