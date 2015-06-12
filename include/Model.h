#ifndef MODEL_H
#define MODEL_H

#include "common.h"								

using namespace std;
using namespace glm;

class Camera;
class Shader;

class Model
{

public:

	//static const GLuint kVertexIndex = 0;
	//static const GLuint kColorIndex = 1;
	//static const GLuint kTextureIndex = 2;
	//static const GLuint kNormalIndex = 3;
	
	Model();
	~Model();

	bool init(string vertexShaderFilename, string fragmentShaderFilename, string textureFilename);
	bool loadFromObj(string filename, string vertexShaderFilename, string fragmentShaderFilename, string textureFilename);
	GLuint loadDDSTexture(string filename);
	void render();

	vec3 getPosition() { return position; }
	vec3 getRotation() { return rotation; }
	vec3 getScale() { return scale; }

	void setPosition(vec3 position) { this->position = position; };
	void setRotation(vec3 rotation) { this->rotation = rotation; };
	void setScale(vec3 scale) { this->scale = scale; };

	Camera *getCamera() { return camera; }
	void setCamera(Camera *camera) { this->camera = camera; }
	
	void release();

protected:

	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	GLuint vertexBufferId;								
	GLuint uvBufferId;								
	GLuint vertexArrayObjectId;
	GLuint textureId;

	vec3 position;
	vec3 rotation;
	vec3 scale;
	
	Shader *shader;
	Camera *camera;

};

#endif











