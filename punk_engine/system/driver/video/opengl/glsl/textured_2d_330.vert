#version 330

uniform mat4 uProjViewWorld;


layout(location = 0) in vec2 rm_Vertex;
layout(location = 2) in vec2 rm_Texcoord;

out vec2 texCoord;

void main(void)
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex, 0.5, 1.0);
	texCoord = rm_Texcoord;
}