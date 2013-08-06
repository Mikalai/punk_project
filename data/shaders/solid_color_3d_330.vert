#version 330

uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;

out vec4 Position;

void main()
{	
	Position = uViewWorld * vec4(rm_Vertex.xyz, 1.0);
	gl_Position = uProjViewWorld*vec4(rm_Vertex.xyz, 1.0);
}
