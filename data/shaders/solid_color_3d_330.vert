#version 330

uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;

void main()
{	
	gl_Position = uProjViewWorld*vec4(rm_Vertex.xyz, 1.0);
}
