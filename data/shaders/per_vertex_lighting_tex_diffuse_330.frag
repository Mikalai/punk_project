#version 330

uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;

in vec4 vertex_color_transparent;
in vec4 vertex_color_opaque;
in vec2 tex_coord0;

out vec4 color;

void main()
{
	vec4 diffuse_color = texture(uDiffuseMap, tex_coord0);
	if (uDiffuseColor.w < 0.99)
	{
		color = vertex_color_transparent * diffuse_color * uDiffuseColor;
	}
	else
	{		
		color = vertex_color_opaque * diffuse_color * uDiffuseColor;	
	}	
}	
