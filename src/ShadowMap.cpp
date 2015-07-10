#include "ShadowMap.h"

using namespace std;

ShadowMap::ShadowMap()
{

	fboId = 0;
	shadowMapId = 0;

}

ShadowMap::~ShadowMap()
{

	if(fboId)
		glDeleteFramebuffers(1, &fboId);

	if(shadowMapId)
		glDeleteTextures(1, &shadowMapId);

}

bool ShadowMap::init(unsigned int width, unsigned int height)
{

	glGenFramebuffers(1, &fboId);

	glGenTextures(1, &shadowMapId);
    glBindTexture(GL_TEXTURE_2D, shadowMapId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapId, 0);

    glDrawBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(status != GL_FRAMEBUFFER_COMPLETE)
    {

        cout << "ShadowMap FBO error: 0x" << status << endl;

        return false;

    }

    return true;

}

void ShadowMap::bindForWriting()
{

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);

}

void ShadowMap::bindForReading(GLenum textureUnit)
{

	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, shadowMapId);

}