#version 410 core

in vec2 textureCoordinate;

uniform sampler2D shadowMap;

out vec4 fragmentColor;

void main()
{

    float depth = texture(shadowMap, textureCoordinate).x;
    depth = 1.0 - (1.0 - depth) * 25.0;

    fragmentColor = vec4(depth);

}