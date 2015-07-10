#ifndef MODEL_H
#define MODEL_H

#include "common.h"

using namespace std;
using namespace glm;

class Texture;
class Shader;

struct Vertex
{

    vec3 position;
    vec2 uv;
    vec3 normal;
    vec3 tangent;

    Vertex() {}

    Vertex(const vec3& position, const vec2& uv, const vec3& normal, const vec3& tangent)
    {

        this->position = position;
        this->uv = uv;
        this->normal = normal;
        this->tangent = tangent;

    }

};

class Model
{

public:

	struct Mesh
	{

        Mesh();
        ~Mesh();

        bool init(const vector<Vertex>& vertices, const vector<unsigned int>& indices);
        void updateVertices();

        GLuint vertexBufferId;
        GLuint indexBufferId;

        vector<Vertex> vertices;
        vector<unsigned int> indices;

    };

	Model();
	~Model();

	bool init(string textureFilename, Shader *shader = NULL);
	bool loadFromObj(string filename, string textureFilename, Shader *shader = NULL);
	bool loadFromMesh(Mesh *mesh, string textureFilename, Shader *shader = NULL);
	void initMesh(unsigned int index, const aiMesh* paiMesh);
	void render();

	vec3 getPosition() { return position; }
	quat getRotation() { return rotation; }
	vec3 getScale() { return scale; }
	Shader *getShader() { return shader; }
	bool shouldTessellate() { return displacementTexture; }

	void setPosition(vec3 position) { this->position = position; }
	void setRotation(quat rotation) { this->rotation = rotation; }
	void setScale(vec3 scale) { this->scale = scale; }
	void setColorTexture(Texture *colorTexture) { this->colorTexture = colorTexture; }
	void setDisplacementTexture(Texture *displacementTexture) { this->displacementTexture = displacementTexture; }

	void release();

protected:

    std::vector<Mesh> meshes;

	//vector<vec3> vertices;
	//vector<vec2> uvs;
	//vector<vec3> normals;

	//GLuint vertexBufferId;
	//GLuint uvBufferId;
	//GLuint normalBufferId;
	GLuint vertexArrayObjectId;

	Texture *colorTexture;
	Texture *normalTexture;
	Texture *specularTexture;
	Texture *displacementTexture;

	vec3 position;
	quat rotation;
	vec3 scale;

	Shader *shader;

};

#endif