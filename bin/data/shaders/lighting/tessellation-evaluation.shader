#version 410 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 viewProjectionMatrix;
//uniform mat4 lightMatrix;
uniform float tessellationLevel;
uniform sampler2D displacementMap;
uniform float displacementFactor;

in vec3 vertexPosTessEvalIn[];
in vec2 textureCoordinateTessEvalIn[];
in vec3 normalVectorTessEvalIn[];
in vec3 tangentVectorTessEvalIn[];

out vec3 vertexPos;
out vec2 textureCoordinate;
out vec3 normalVector;
out vec3 tangentVector;
//out vec4 lightPos;

vec2 interpolate2d(vec2 v0, vec2 v1, vec2 v2)
{

    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;

}

vec3 interpolate3d(vec3 v0, vec3 v1, vec3 v2)
{

    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;

}

void main()
{

    // Interpolate the attributes of the output vertex using the barycentric coordinates
    vertexPos = interpolate3d(vertexPosTessEvalIn[0], vertexPosTessEvalIn[1], vertexPosTessEvalIn[2]);
    textureCoordinate = interpolate2d(textureCoordinateTessEvalIn[0], textureCoordinateTessEvalIn[1], textureCoordinateTessEvalIn[2]);
    normalVector = interpolate3d(normalVectorTessEvalIn[0], normalVectorTessEvalIn[1], normalVectorTessEvalIn[2]);
    normalVector = normalize(normalVector);
    tangentVector = interpolate3d(tangentVectorTessEvalIn[0], tangentVectorTessEvalIn[1], tangentVectorTessEvalIn[2]);

    // Displace the vertex along the normal
    if(tessellationLevel > 1)
    {

        float displacement = texture(displacementMap, textureCoordinate.xy).x;
        vertexPos += normalVector * displacement * displacementFactor;

    }

    //lightPos = lightMatrix * vec4(vertexPos, 1.0);
    gl_Position = viewProjectionMatrix * vec4(vertexPos, 1.0);

}