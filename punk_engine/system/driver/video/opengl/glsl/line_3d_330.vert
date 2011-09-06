#version 330

uniform mat4 uProjViewWorld;

in vec3 rm_Vertex;

void main()
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);
}