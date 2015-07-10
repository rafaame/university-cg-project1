#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "common.h"

using namespace std;
using namespace glm;

class ShadowMap
{

public:

	ShadowMap();
	~ShadowMap();

	bool init(unsigned int width, unsigned int height);

	void bindForWriting();
	void bindForReading(GLenum textureUnit);

protected:

	GLuint fboId;
	GLuint shadowMapId;

};

#endif