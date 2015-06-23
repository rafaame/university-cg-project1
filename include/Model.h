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
	
	Model();
	~Model();

	bool init(string vertexShaderFilename, string fragmentShaderFilename, string textureFilename);
	bool loadFromObj(string filename, string vertexShaderFilename, string fragmentShaderFilename, string textureFilename);
	GLuint loadDDSTexture(string filename);
	void render();

	vec3 getPosition() { return position; }
	quat getRotation() { return rotation; }
	vec3 getScale() { return scale; }
	vector<vec3> getVertices() { return vertices; }

	void setPosition(vec3 position) { this->position = position; };
	void setRotation(quat rotation) { this->rotation = rotation; };
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
	quat rotation;
	vec3 scale;
	
	Shader *shader;
	Camera *camera;

};

#endif











