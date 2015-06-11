#ifndef _ModelManager_H
#define _ModelManager_H

#define GLM_FORCE_RADIANS								

#include <stdio.h>										
#include <stdlib.h>	
#include <vector>									
#include <GL/glew.h>									
#include <glm/glm.hpp>									
#include <glm/gtc/matrix_transform.hpp>					
#include <glm/gtx/transform2.hpp>						
#include "Shader.h"										
#include "Camera.h"		

using namespace glm;

class Vertex3
{

public:
	
	vec3 xyz;											
	vec4 rgba;											

};

class Model
{

public:

	
	static const GLuint kVertexIndex = 0;
	static const GLuint kColorIndex = 1;
	static const GLuint kTextureIndex = 2;
	static const GLuint kNormalIndex = 3;
	
	Model() { Scale = vec3(1.0f, 1.0f, 1.0f); }
	~Model() { Destroy(); }

	void Initialize(std::string vertexShaderFilename, std::string fragmentShaderFilename, std::string textureFilename);
	void loadFromObj(std::string filename, std::string vertexShaderFilename, std::string fragmentShaderFilename, std::string textureFilename);
	GLuint loadDDSTexture(std::string filename);
	void Render();

	vec3 GetPosition() { return Position; }
	vec3 GetRotation() { return Rotation; }
	vec3 GetScale() { return Scale; }

	void SetPosition(vec3 position) { Position = position; }
	void SetRotation(vec3 rotation) { Rotation = rotation; }
	void SetScale(vec3 scale) { Scale = scale; }

	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *pCamera) { Camera = pCamera; }
	
	void Destroy();

protected:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint VertexBufferId;								
	GLuint uvBufferId;								
	GLuint VertexArrayObjectId;
	GLuint textureId;

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
	
	Shader Shader;
	
	Camera *Camera;

};

#endif











