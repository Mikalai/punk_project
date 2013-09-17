#version 330

uniform mat3 uWorldTransposedInversed;
uniform mat4 uWorld;
uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;

out vec3 vWorldVertexNormal;
out vec3 vWorldVertexPosition;

void main()
{
    gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
    vWorldVertexPosition = (uWorld * vec4(rm_Vertex.xyz, 1.0)).xyz;
    vWorldVertexNormal = normalize(uWorldTransposedInversed * rm_Normal.xyz);
}
