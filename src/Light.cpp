#include "Light.h"

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Model.h"

using namespace std;
using namespace glm;

LightingShader::LightingShader() : Shader()
{

    tessellationLevel = 10.0f;
    displacementFactor = 0.5f;
    useNormalMaps = true;
    useSpecularMaps = true;
    specularLighting = true;
    diffuseLighting = true;

}

bool LightingShader::init()
{

	if(!Shader::init(

			"data/shaders/lighting/vertex.shader",
			"data/shaders/lighting/tessellation-control.shader",
			"data/shaders/lighting/tessellation-evaluation.shader",
			"data/shaders/lighting/fragment.shader"

	))
		return false;

    //lightMatrixId = getUniformLocation("lightMatrix");
    colorTextureId = getUniformLocation("colorMap");
    normalMapId = getUniformLocation("normalMap");
    specularMapId = getUniformLocation("specularMap");
    displacementMapId = getUniformLocation("displacementMap");
    shadowMapId = getUniformLocation("shadowMap");
    cameraPositionId = getUniformLocation("cameraPosition");

    directionalLightId.color = getUniformLocation("directionalLight.base.color");
    directionalLightId.ambientIntensity = getUniformLocation("directionalLight.base.ambientIntensity");
    directionalLightId.direction = getUniformLocation("directionalLight.direction");
    directionalLightId.diffuseIntensity = getUniformLocation("directionalLight.base.diffuseIntensity");

    specularIntensityId = getUniformLocation("specularIntensity");
    specularPowerId = getUniformLocation("specularPower");
    numberPointLightsId = getUniformLocation("numberPointLights");
    numberSpotLightsId = getUniformLocation("numberSpotLights");
    tessellationLevelId = getUniformLocation("tessellationLevel");
    displacementFactorId = getUniformLocation("displacementFactor");
    useNormalMapsId = getUniformLocation("useNormalMaps");
    useSpecularMapsId = getUniformLocation("useSpecularMaps");
    specularLightingId = getUniformLocation("specularLighting");
    diffuseLightingId = getUniformLocation("diffuseLighting");

    for(unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(pointLightsId) ; i++)
    {

        char buff[128];
        memset(buff, 0, sizeof(buff));
        snprintf(buff, sizeof(buff), "pointLights[%d].base.color", i);
        pointLightsId[i].color = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].base.ambientIntensity", i);
        pointLightsId[i].ambientIntensity = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].position", i);
        pointLightsId[i].position = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].base.diffuseIntensity", i);
        pointLightsId[i].diffuseIntensity = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].attenuation.constant", i);
        pointLightsId[i].attenuation.constant = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].attenuation.linear", i);
        pointLightsId[i].attenuation.linear = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "pointLights[%d].attenuation.exp", i);
        pointLightsId[i].attenuation.exp = getUniformLocation(buff);

    }

    for(unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(spotLightsId) ; i++)
    {

        char buff[128];
        memset(buff, 0, sizeof(buff));
        snprintf(buff, sizeof(buff), "spotLights[%d].base.base.color", i);
        spotLightsId[i].color = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.base.ambientIntensity", i);
        spotLightsId[i].ambientIntensity = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.position", i);
        spotLightsId[i].position = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].direction", i);
        spotLightsId[i].direction = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].cutoff", i);
        spotLightsId[i].cutoff = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.base.diffuseIntensity", i);
        spotLightsId[i].diffuseIntensity = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.attenuation.constant", i);
        spotLightsId[i].attenuation.constant = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.attenuation.linear", i);
        spotLightsId[i].attenuation.linear = getUniformLocation(buff);

        snprintf(buff, sizeof(buff), "spotLights[%d].base.attenuation.exp", i);
        spotLightsId[i].attenuation.exp = getUniformLocation(buff);

    }

    return true;

}

void LightingShader::update(Scene *scene)
{

    Shader::update(scene);

    Camera *camera = scene->getPlayer()->getCamera();

    setCameraPosition(camera->getPosition());

    updatePointLights();
    updateSpotLights();

}

void LightingShader::update(Model *model)
{

    Shader::update(model);

    setTessellationLevel(model->shouldTessellate() ? tessellationLevel : 1.0f);

}

void LightingShader::setColorTextureUnit(unsigned int colorTextureUnit)
{
    setInt(colorTextureId, colorTextureUnit);
}

void LightingShader::setNormalMapTextureUnit(unsigned int normalTextureUnit)
{

    setInt(normalMapId, normalTextureUnit);

}

void LightingShader::setSpecularMapTextureUnit(unsigned int specularTextureUnit)
{

    setInt(specularMapId, specularTextureUnit);

}

void LightingShader::setDisplacementMapTextureUnit(unsigned int displacementTextureUnit)
{

    setInt(displacementMapId, displacementTextureUnit);

}

void LightingShader::setShadowMapTextureUnit(unsigned int shadowTextureUnit)
{

    setInt(shadowMapId, shadowTextureUnit);

}

void LightingShader::setDirectionalLight(const DirectionalLight& light)
{

    vec3 direction = light.direction;
    direction = normalize(direction);

    glUniform3f(directionalLightId.color, light.color.x, light.color.y, light.color.z);
    glUniform1f(directionalLightId.ambientIntensity, light.ambientIntensity);
    glUniform1f(directionalLightId.diffuseIntensity, light.diffuseIntensity);
    glUniform3f(directionalLightId.direction, direction.x, direction.y, direction.z);

}

void LightingShader::setCameraPosition(const vec3& cameraPosition)
{

    glUniform3f(cameraPositionId, cameraPosition.x, cameraPosition.y, cameraPosition.z);

}

void LightingShader::setSpecularIntensity(float intensity)
{

    glUniform1f(specularIntensityId, intensity);

}

void LightingShader::setSpecularPower(float power)
{

    glUniform1f(specularPowerId, power);

}

void LightingShader::updatePointLights()
{

    setInt(numberPointLightsId, pointLights.size());

    uint8_t i = 0;
    for(auto it = pointLights.begin(); it != pointLights.end(); it++, i++)
    {

        PointLight *pointLight = (*it);

        glUniform3f(pointLightsId[i].color, pointLight->color.x, pointLight->color.y, pointLight->color.z);
        glUniform1f(pointLightsId[i].ambientIntensity, pointLight->ambientIntensity);
        glUniform1f(pointLightsId[i].diffuseIntensity, pointLight->diffuseIntensity);
        glUniform3f(pointLightsId[i].position, pointLight->position.x, pointLight->position.y, pointLight->position.z);
        glUniform1f(pointLightsId[i].attenuation.constant, pointLight->attenuation.constant);
        glUniform1f(pointLightsId[i].attenuation.linear, pointLight->attenuation.linear);
        glUniform1f(pointLightsId[i].attenuation.exp, pointLight->attenuation.exp);

    }

}

void LightingShader::updateSpotLights()
{

    setInt(numberSpotLightsId, spotLights.size());

    uint8_t i = 0;
    for(auto it = spotLights.begin(); it != spotLights.end(); it++, i++)
    {

        SpotLight *spotLight = (*it);

        vec3 direction = spotLight->direction;
        direction = normalize(direction);

        glUniform3f(spotLightsId[i].color, spotLight->color.x, spotLight->color.y, spotLight->color.z);
        glUniform1f(spotLightsId[i].ambientIntensity, spotLight->ambientIntensity);
        glUniform1f(spotLightsId[i].diffuseIntensity, spotLight->diffuseIntensity);
        glUniform3f(spotLightsId[i].position,  spotLight->position.x, spotLight->position.y, spotLight->position.z);
        glUniform3f(spotLightsId[i].direction, direction.x, direction.y, direction.z);
        glUniform1f(spotLightsId[i].cutoff, cosf(ToRadian(spotLight->cutoff)));
        glUniform1f(spotLightsId[i].attenuation.constant, spotLight->attenuation.constant);
        glUniform1f(spotLightsId[i].attenuation.linear, spotLight->attenuation.linear);
        glUniform1f(spotLightsId[i].attenuation.exp, spotLight->attenuation.exp);

    }

}

void LightingShader::setTessellationLevel(float tessellationLevel)
{

    setFloat(tessellationLevelId, tessellationLevel);

}

void LightingShader::setDisplacementFactor(float displacementFactor)
{

    setFloat(displacementFactorId, displacementFactor);

}

void LightingShader::setUseNormalMaps(bool useNormalMaps)
{

    setInt(useNormalMapsId, useNormalMaps);

}

void LightingShader::setUseSpecularMaps(bool useSpecularMaps)
{

    setInt(useSpecularMapsId, useSpecularMaps);

}

void LightingShader::setSpecularLighting(bool specularLighting)
{

    setInt(specularLightingId, specularLighting);

}

void LightingShader::setDiffuseLighting(bool diffuseLighting)
{

    setInt(diffuseLightingId, diffuseLighting);

}

void LightingShader::setActive(bool active)
{

    Shader::setActive(active);

    if(active)
    {

        setColorTextureUnit(0);
        setNormalMapTextureUnit(1);
        setSpecularMapTextureUnit(2);
        setDisplacementMapTextureUnit(3);
        setShadowMapTextureUnit(4);

        setTessellationLevel(tessellationLevel);
        setDisplacementFactor(displacementFactor);
        setUseNormalMaps(useNormalMaps);
        setUseSpecularMaps(useSpecularMaps);
        setSpecularLighting(specularLighting);
        setDiffuseLighting(diffuseLighting);
        setSpecularIntensity(1);
        setSpecularPower(100);

    }

}