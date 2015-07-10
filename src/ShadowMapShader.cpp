#include "ShadowMapShader.h"

#include "Application.h"
#include "Camera.h"

using namespace std;
using namespace glm;

ShadowMapShader::ShadowMapShader() : Shader()
{

	textureId = 0;

}

bool ShadowMapShader::init()
{

	if(!Shader::init(

			"data/shaders/shadow-mapping/vertex.shader",
			"",
			"",
			"data/shaders/shadow-mapping/fragment.shader"

	))
		return false;

    textureId = getUniformLocation("shadowMap");

    return true;

}

void ShadowMapShader::setTextureUnit(unsigned int textureUnit)
{

	setInt(textureId, textureUnit);

}