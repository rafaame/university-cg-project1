#version 410 core

const int MAX_POINT_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 8;

in vec3 vertexPos;
in vec2 textureCoordinate;
in vec3 normalVector;
in vec3 tangentVector;

out vec4 fragmentColor;

struct BaseLight
{

    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;

};

struct DirectionalLight
{

    BaseLight base;

    vec3 direction;

};

struct Attenuation
{

    float constant;
    float linear;
    float exp;

};

struct PointLight
{

    BaseLight base;

    vec3 position;
    Attenuation attenuation;

};

struct SpotLight
{

    PointLight base;

    vec3 direction;
    float cutoff;

};

uniform int numberPointLights;
uniform int numberSpotLights;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform vec3 cameraPosition;
uniform float specularIntensity;
uniform float specularPower;

uniform int useNormalMaps;
uniform int useSpecularMaps;
uniform int specularLighting;
uniform int diffuseLighting;

vec4 calculateLight(BaseLight light, vec3 lightDirection, vec3 normal)
{

    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    float diffuseFactor = dot(normal, -lightDirection);

    vec4 diffuseColor  = vec4(0, 0, 0, 0);
    vec4 specularColor = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0)
    {

        diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

        vec3 eyeVector = normalize(cameraPosition - vertexPos);
        vec3 lightReflection = normalize(reflect(lightDirection, normal));
        float specularFactor = dot(eyeVector, lightReflection);

        float power = specularPower;

        if(useSpecularMaps != 0)
            power = texture(specularMap, textureCoordinate).r * 255.0;

        specularFactor = pow(specularFactor, power);

        if (specularFactor > 0)
            specularColor = vec4(light.color, 1.0f) * specularIntensity * specularFactor;

    }

    return (ambientColor + diffuseLighting * diffuseColor + specularLighting * specularColor);

}

vec4 calculateDirectionalLight(vec3 normal)
{

    return calculateLight(directionalLight.base, directionalLight.direction, normal);

}

vec4 calculatePointLight(PointLight pointLight, vec3 normal)
{

    vec3 lightDirection = vertexPos - pointLight.position;
    float distance = length(lightDirection);
    lightDirection = normalize(lightDirection);

    vec4 color = calculateLight(pointLight.base, lightDirection, normal);
    float attenuation =
                 pointLight.attenuation.constant +
                 pointLight.attenuation.linear * distance +
                 pointLight.attenuation.exp * distance * distance;

    return color / attenuation;

}

vec4 calculateSpotLight(SpotLight spotLight, vec3 normal)
{

    vec3 lightDirection = normalize(vertexPos - spotLight.base.position);
    float spotFactor = dot(lightDirection, spotLight.direction);

    vec4 color = vec4(0, 0, 0, 0);

    if (spotFactor > spotLight.cutoff)
    {

        color = calculatePointLight(spotLight.base, normal);
        color = color * (1.0 - (1.0 - spotFactor) * 1.0/(1.0 - spotLight.cutoff));

    }

    return color;

}

vec3 getNormalFromMap()
{

    vec3 normal = normalize(normalVector);

    vec3 tangent = normalize(tangentVector);
    tangent = normalize(tangent - dot(tangent, normal) * normal);

    vec3 bitangent = cross(tangent, normal);

    vec3 mapNormal = texture(normalMap, textureCoordinate).xyz;
    mapNormal = 2.0 * mapNormal - vec3(1.0, 1.0, 1.0);

    mat3 TBN = mat3(tangent, bitangent, normal);
    normal = TBN * mapNormal;
    normal = normalize(normal);

    return normal;

}

void main()
{
    vec3 normal = vec3(0, 0, 0);

    if(useNormalMaps != 0)
        normal = getNormalFromMap();
    else
        normal = normalize(normalVector);

    vec4 light = calculateDirectionalLight(normal);

    for(int i = 0; i < numberSpotLights; i++)
        light += calculateSpotLight(spotLights[i], normal);

    for(int i = 0; i < numberPointLights; i++)
        light += calculatePointLight(pointLights[i], normal);

    fragmentColor = texture(colorMap, textureCoordinate.xy) * light;

}