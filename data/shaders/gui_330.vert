#version 330

uniform mat4 uProjViewWorld;
uniform mat2 uTextureMatrix;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 4) in vec4 rm_Texcoord;

out vec2 texCoord;
out vec2 diffuseMapTexcoord;
out vec2 pos;

void main(void)
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
	pos = rm_Vertex.xy;
	texCoord = uTextureMatrix * rm_Texcoord.xy;
	diffuseMapTexcoord = uTextureMatrix * rm_Texcoord.xy;
}