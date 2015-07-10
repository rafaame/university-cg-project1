#ifndef SHADOWMAPSHADER_H
#define SHADOWMAPSHADER_H

#include "common.h"

#include "Shader.h"

using namespace std;
using namespace glm;

class ShadowMapShader : public Shader
{

public:

    ShadowMapShader();

    virtual bool init();

    void setTextureUnit(unsigned int textureUnit);

protected:

    GLuint textureId;

};

#endif