#version 330

uniform mat4 uWorld;
uniform mat2 uTextureMatrix;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 4) in vec4 rm_Texcoord;
layout(location = 6) in vec4 rm_Flag;
layout(location = 7) in vec4 rm_Color;

out vec2 texCoord;
out vec2 diffuseMapTexcoord;
out vec2 pos;

void main(void)
{
	gl_Position = uWorld * vec4(rm_Vertex.xyz, 1.0);
	pos = rm_Vertex.xy;
	texCoord = uTextureMatrix * rm_Texcoord.xy;
	diffuseMapTexcoord = uTextureMatrix * rm_Texcoord.xy;
}