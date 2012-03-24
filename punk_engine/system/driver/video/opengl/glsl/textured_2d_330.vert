#version 330

uniform mat4 uProjViewWorld;


layout(location = 0) in vec4 rm_Vertex;
layout(location = 2) in vec4 rm_Texcoord;

out vec2 texCoord;

void main(void)
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex.xy, 0, 1.0);
	texCoord = rm_Texcoord.xy;
}