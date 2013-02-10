#version 330

uniform mat3 uNormalMatrix;
uniform mat4 uView;
uniform mat4 uWorld;
uniform mat4 uProj;

uniform vec3 uLightPosition;
uniform vec4 uDiffuse;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec3 rm_Normal;

out vec4 vertex_color;

void main()
{
	gl_Position = uProj * uView * uWorld * vec4(rm_Vertex.xyz, 1.0);
	vec4 ObjectPosition = uView * uWorld * vec4(rm_Vertex.xyz, 1.0);
	vec3 normal = normalize(uNormalMatrix * rm_Normal);
	vec3 lightDir = normalize((uView * vec4(uLightPosition.xyz, 1.0)).xyz - ObjectPosition.xyz);
	vertex_color = uDiffuse * max(0.0, dot(lightDir, normal));
}