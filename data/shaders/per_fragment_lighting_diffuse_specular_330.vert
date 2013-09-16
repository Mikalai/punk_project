#version 330

uniform mat3 uNormalMatrix;
uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;

out vec3 vViewVertexNormal;
out vec3 vViewVertexPosition;

void main()
{
    gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
    vViewVertexPosition = (uViewWorld * vec4(rm_Vertex.xyz, 1.0)).xyz;
    vViewVertexNormal = normalize(uNormalMatrix * rm_Normal.xyz);
}
