#include "Model.h"
#include "RenderingManager.h"
#include "Application.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

using namespace std;
using namespace glm;

Model::Mesh::Mesh()
{

    vertexBufferId = 0;
    indexBufferId = 0;

};

Model::Mesh::~Mesh()
{
   /* if (VB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &VB);
    }

    if (IB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &IB);
    }*/
}

bool Model::Mesh::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{

    this->vertices = vertices;
    this->indices = indices;

    glGenBuffers(1, &vertexBufferId);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    return glGetError() == GL_NO_ERROR;

}

void Model::Mesh::updateVertices()
{

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

}

Model::Model()
{

	scale = vec3(1.0, 1.0, 1.0);
	position = vec3(0, 0, 0);
	rotation = quat(1, 0, 0, 0);

	colorTexture = NULL;
	normalTexture = NULL;
    specularTexture = NULL;
	displacementTexture = NULL;

	shader = static_cast<Shader *>(Application::instance()->getRenderingManager()->getLightingShader());

}

Model::~Model()
{

	/*if(vertexBufferId)
	{

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vertexBufferId);
		vertexBufferId = 0;

	}

	if(vertexArrayObjectId)
	{

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vertexArrayObjectId);
		vertexArrayObjectId = 0;

	}*/

	//delete shader;

}

bool Model::init(string textureFilename, Shader *shader)
{

	if(shader)
	   this->shader = shader;

	stringstream colorMapFilename;
	colorMapFilename << textureFilename << "/color.jpg";

	stringstream normalMapFilename;
	normalMapFilename << textureFilename << "/normal.jpg";

    stringstream specularMapFilename;
    specularMapFilename << textureFilename << "/specular.jpg";

	stringstream heightMapFilename;
	heightMapFilename << textureFilename << "/height.jpg";

	glActiveTexture(GL_TEXTURE0);
	colorTexture = Texture::create(GL_TEXTURE_2D, colorMapFilename.str());

	glActiveTexture(GL_TEXTURE1);
	normalTexture = Texture::create(GL_TEXTURE_2D, normalMapFilename.str());

    glActiveTexture(GL_TEXTURE2);
    specularTexture = Texture::create(GL_TEXTURE_2D, specularMapFilename.str());

	glActiveTexture(GL_TEXTURE3);
	displacementTexture = Texture::create(GL_TEXTURE_2D, heightMapFilename.str());

	return true;

}

bool Model::loadFromMesh(Mesh *mesh, string textureFilename, Shader *shader)
{

    init(textureFilename, shader);

    meshes.push_back(*mesh);

    return true;

}

bool Model::loadFromObj(string filename, string textureFilename, Shader *shader)
{

	//cout << "Loading" << endl;

    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!pScene)
    {

    	cout << "Error parsing '" << filename.c_str() << "': '" << Importer.GetErrorString() << endl;

    	return false;

    }

    init(textureFilename, shader);

    meshes.resize(pScene->mNumMeshes);
    //materials.resize(pScene->mNumMaterials);

    for(unsigned int i = 0 ; i < meshes.size(); i++)
    {

        const aiMesh* paiMesh = pScene->mMeshes[i];
        initMesh(i, paiMesh);

    }

    return true;
	//return init(textureFilename, shader);

}

void Model::initMesh(unsigned int index, const aiMesh* paiMesh)
{

    vector<Vertex> vertices;
    vector<unsigned int> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for(unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++)
    {

        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        const aiVector3D* pTangent = &(paiMesh->mTangents[i]);

        Vertex v(vec3(pPos->x, pPos->y, pPos->z),
                 vec2(pTexCoord->x, pTexCoord->y),
                 vec3(pNormal->x, pNormal->y, pNormal->z),
                 vec3(pTangent->x, pTangent->y, pTangent->z));

        vertices.push_back(v);

    }

    for(unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
    {

        const aiFace& face = paiMesh->mFaces[i];

        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);

    }

    meshes[index].init(vertices, indices);

}

void Model::render()
{

    Shader *shader = Application::instance()->getRenderingManager()->getActiveShader();

    shader->update(this);

    if(colorTexture)
	   colorTexture->bind(GL_TEXTURE0);

    if(normalTexture)
	   normalTexture->bind(GL_TEXTURE1);

    if(specularTexture)
        specularTexture->bind(GL_TEXTURE2);

    if(displacementTexture)
	   displacementTexture->bind(GL_TEXTURE3);

	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    for(unsigned int i = 0 ; i < meshes.size() ; i++)
    {

        glBindBuffer(GL_ARRAY_BUFFER, meshes[i].vertexBufferId);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) 12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) 20);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) 32);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].indexBufferId);

        if(shader->hasTessellation())
            glDrawElements(GL_PATCHES, meshes[i].indices.size(), GL_UNSIGNED_INT, 0);
        else
            glDrawElements(GL_TRIANGLES, meshes[i].indices.size(), GL_UNSIGNED_INT, 0);

    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

}