#version 410 core

layout (location = 0) in vec3 vertexPosIn;
layout (location = 1) in vec2 textureCoordinateIn;
layout (location = 2) in vec3 normalVectorIn;
layout (location = 3) in vec3 tangentVectorIn;

uniform mat4 modelMatrix;

out vec3 vertexPosTessControlIn;
out vec2 textureCoordinateTessControlIn;
out vec3 normalVectorTessControlIn;
out vec3 tangentVectorTessControlIn;

void main()
{

    vertexPosTessControlIn = (modelMatrix * vec4(vertexPosIn, 1.0)).xyz;
    textureCoordinateTessControlIn = textureCoordinateIn;
    normalVectorTessControlIn = (modelMatrix * vec4(normalVectorIn, 0.0)).xyz;
    tangentVectorTessControlIn = (modelMatrix * vec4(tangentVectorIn, 0.0)).xyz;

}