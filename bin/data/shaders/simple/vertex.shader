#version 410 core

layout (location = 0) in vec3 vertexPosIn;
layout (location = 1) in vec2 textureCoordinateIn;
layout (location = 2) in vec3 normalVectorIn;
layout (location = 3) in vec3 tangentVectorIn;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

void main()
{

    gl_Position = viewProjectionMatrix * modelMatrix * vec4(vertexPosIn, 1.0);

}