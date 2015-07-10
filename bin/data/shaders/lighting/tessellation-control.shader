#version 410 core

layout (vertices = 3) out;

uniform float tessellationLevel;

in vec3 vertexPosTessControlIn[];
in vec2 textureCoordinateTessControlIn[];
in vec3 normalVectorTessControlIn[];
in vec3 tangentVectorTessControlIn[];

out vec3 vertexPosTessEvalIn[];
out vec2 textureCoordinateTessEvalIn[];
out vec3 normalVectorTessEvalIn[];
out vec3 tangentVectorTessEvalIn[];

void main()
{

    vertexPosTessEvalIn[gl_InvocationID] = vertexPosTessControlIn[gl_InvocationID];
    textureCoordinateTessEvalIn[gl_InvocationID] = textureCoordinateTessControlIn[gl_InvocationID];
    normalVectorTessEvalIn[gl_InvocationID]   = normalVectorTessControlIn[gl_InvocationID];
    tangentVectorTessEvalIn[gl_InvocationID]   = tangentVectorTessControlIn[gl_InvocationID];

    gl_TessLevelOuter[0] = tessellationLevel;
    gl_TessLevelOuter[1] = tessellationLevel;
    gl_TessLevelOuter[2] = tessellationLevel;
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];

}