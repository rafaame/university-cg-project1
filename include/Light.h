#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"

#include "Shader.h"

using namespace std;
using namespace glm;

class Scene;
class Model;

struct BaseLight
{

    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;

    BaseLight()
    {

        color = vec3(0.0f, 0.0f, 0.0f);
        ambientIntensity = 0.0f;
        diffuseIntensity = 0.0f;

    }

};

struct DirectionalLight : public BaseLight
{

    vec3 direction;

    DirectionalLight()
    {

        direction = vec3(0.0f, 0.0f, 0.0f);

    }

};

struct PointLight : public BaseLight
{

    vec3 position;

    struct
    {

        float constant;
        float linear;
        float exp;

    } attenuation;

    PointLight()
    {

        position = vec3(0.0f, 0.0f, 0.0f);

        attenuation.constant = 1.0f;
        attenuation.linear = 0.0f;
        attenuation.exp = 0.0f;

    }

};

struct SpotLight : public PointLight
{

    vec3 direction;
    float cutoff;

    SpotLight()
    {

        direction = vec3(0.0f, 0.0f, 0.0f);
        cutoff = 0.0f;

    }

};

class LightingShader : public Shader
{

public:

    static const unsigned int MAX_POINT_LIGHTS = 8;
    static const unsigned int MAX_SPOT_LIGHTS = 8;

    LightingShader();

    virtual bool init();
    virtual void update(Scene *scene);
    virtual void update(Model *model);
    virtual void updatePointLights();
    virtual void updateSpotLights();

    //void setLightMatrix(const mat4& lightMatrix);
    void setColorTextureUnit(unsigned int colorTextureUnit);
    void setNormalMapTextureUnit(unsigned int normalMapTextureUnit);
    void setSpecularMapTextureUnit(unsigned int specularMapTextureUnit);
    void setDisplacementMapTextureUnit(unsigned int displacementMapTextureUnit);
    void setShadowMapTextureUnit(unsigned int shadowMapTextureUnit);
    void setDirectionalLight(const DirectionalLight& light);
    void setCameraPosition(const vec3& cameraPosition);
    void setSpecularIntensity(float intensity);
    void setSpecularPower(float power);
    void setTessellationLevel(float tessellationLevel);
    void setDisplacementFactor(float displacementFactor);
    void setUseNormalMaps(bool useNormalMaps);
    void setUseSpecularMaps(bool useSpecularMaps);
    void setSpecularLighting(bool specularLighting);
    void setDiffuseLighting(bool diffuseLighting);

    void addPointLight(PointLight *pointLight) { pointLights.push_back(pointLight); }
    void addSpotLight(SpotLight *spotLight) { spotLights.push_back(spotLight); }

    float getTessellationLevelParam() { return tessellationLevel; }
    float getDisplacementFactorParam() { return displacementFactor; }

    void setTessellationLevelParam(float param) { tessellationLevel = param; }
    void setDisplacementFactorParam(float param) { displacementFactor = param; }
    void setUseNormalMapsParam(bool param) { useNormalMaps = param; }
    void setUseSpecularMapsParam(bool param) { useSpecularMaps = param; }
    void setSpecularLightingParam(bool param) { specularLighting = param; }
    void setDiffuseLightingParam(bool param) { diffuseLighting = param; }

    virtual void setActive(bool active);

protected:

    float tessellationLevel;
    float displacementFactor;
    bool useNormalMaps;
    bool useSpecularMaps;
    bool specularLighting;
    bool diffuseLighting;

    //GLuint lightMatrixId;
    GLuint colorTextureId;
    GLuint normalMapId;
    GLuint specularMapId;
    GLuint displacementMapId;
    GLuint shadowMapId;
    GLuint cameraPositionId;
    GLuint specularIntensityId;
    GLuint specularPowerId;
    GLuint numberPointLightsId;
    GLuint numberSpotLightsId;
    GLuint tessellationLevelId;
    GLuint displacementFactorId;
    GLuint useNormalMapsId;
    GLuint useSpecularMapsId;
    GLuint specularLightingId;
    GLuint diffuseLightingId;

    vector <PointLight *> pointLights;
    vector <SpotLight *> spotLights;

    struct
    {

        GLuint color;
        GLuint ambientIntensity;
        GLuint diffuseIntensity;
        GLuint direction;

    } directionalLightId;

    struct
    {

        GLuint color;
        GLuint ambientIntensity;
        GLuint diffuseIntensity;
        GLuint position;

        struct
        {

            GLuint constant;
            GLuint linear;
            GLuint exp;

        } attenuation;

    } pointLightsId[MAX_POINT_LIGHTS];

    struct
    {

        GLuint color;
        GLuint ambientIntensity;
        GLuint diffuseIntensity;
        GLuint position;
        GLuint direction;
        GLuint cutoff;

        struct
        {

            GLuint constant;
            GLuint linear;
            GLuint exp;

        } attenuation;

    } spotLightsId[MAX_SPOT_LIGHTS];

};

#endif