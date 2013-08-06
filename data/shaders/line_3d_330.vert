#version 330

uniform mat4 uProjViewWorld;
uniform vec3 uStart;
uniform vec3 uEnd;

layout(location = 0) in vec4 rm_Vertex;


void main()
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);
}