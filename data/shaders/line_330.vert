#version 330

uniform mat4 uProjViewWorld;
uniform vec3 uStart;
uniform vec3 uEnd;

layout(location = 0) in vec4 rm_Vertex;

void main()
{
	if (rm_Vertex.x < 0.5)
		gl_Position = uProjViewWorld * vec4(uStart, 1.0);
	else
		gl_Position = uProjViewWorld * vec4(uEnd, 1.0);
}