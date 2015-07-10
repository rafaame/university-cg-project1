#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

using namespace std;

class Camera;
class Shader;

class Texture
{

public:

	Texture(GLenum textureTarget, string filename);
	~Texture();

	bool load();
	void bind(GLenum textureUnit);

	static Texture *create(GLenum textureTarget, string filename);

public:

	GLuint textureId;
	GLenum textureTarget;
	Magick::Image *image;
	Magick::Blob *blob;
	string filename;

	static map<string, Texture *> loadedTextures;

};

#endif