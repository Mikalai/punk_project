#version 330

uniform vec4 uDiffuseColor;

in vec4 vertex_color;

out vec4 color;

void main()
{
	color = vertex_color * uDiffuseColor;
}	