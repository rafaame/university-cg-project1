#include "Texture.h"

using namespace std;

map<string, Texture *> Texture::loadedTextures;

Texture::Texture(GLenum textureTarget, string filename)
{

	this->textureTarget = textureTarget;
	this->filename = filename;
	this->image = NULL;
	this->blob = NULL;

}

Texture::~Texture()
{

	if(image)
		delete image;

	if(blob)
		delete blob;

}

bool Texture::load()
{

	try
	{

		image = new Magick::Image(filename);

		blob = new Magick::Blob();
		image->write(blob, "RGBA");

	}
	catch(Magick::Error &e)
	{

		return false;

	}

	glGenTextures(1, &textureId);
    glBindTexture(textureTarget, textureId);
    glTexImage2D(textureTarget, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob->data());
    glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;

}

void Texture::bind(GLenum textureUnit)
{

	glActiveTexture(textureUnit);
	glBindTexture(textureTarget, textureId);

}

Texture *Texture::create(GLenum textureTarget, string filename)
{

	if(Texture::loadedTextures.find(filename) != Texture::loadedTextures.end())
		return Texture::loadedTextures[filename];

	Texture *texture = new Texture(textureTarget, filename);

	if(!texture->load())
	{

		delete texture;

		return NULL;

	}

	Texture::loadedTextures.insert(pair<string, Texture *>(filename, texture));

	return texture;

}