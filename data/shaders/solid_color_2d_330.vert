#version 330

uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;

out vec2 pos;
out vec2 topLeft;
out vec2 bottomRight;

void main(void)
{
	vec4 p = uProjViewWorld * vec4(rm_Vertex.xyz,1);
	topLeft = (uProjViewWorld * vec4(0,1,0,1)).xy; 
	bottomRight = (uProjViewWorld * vec4(1,0,0,1)).xy;
	gl_Position = p;
	pos = p.xy;
}