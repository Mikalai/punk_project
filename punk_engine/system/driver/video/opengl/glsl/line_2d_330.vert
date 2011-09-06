#version 330

uniform mat4 uProjViewWorld;
uniform vec2 uP1;
uniform vec2 uP2;
uniform float uWidth;
uniform float uHeight;

in vec2 rm_Vertex;

void main(void)
{
	if (rm_Vertex.x < 0.1)
		//gl_Position = vec4(0.5, 0, -0.5, 1.0);
		gl_Position = vec4(-1 + 2*uP1.x/uWidth, -1 + 2*uP1.y/uHeight, -0.5, 1.0);
	else
		gl_Position = vec4(-1 + 2*uP2.x/uWidth, -1 + 2*uP2.y/uHeight, -0.5, 1.0);
		//gl_Position = vec4(0, 0, -0.5, 1.0);
}