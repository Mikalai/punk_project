#version 330

uniform sampler2D uNormalMapUniform;
uniform sampler2D uDiffuseMapUniform;
uniform vec4 uDiffuseColor;

uniform vec3 uLightDirection;

in vec2 tex_coord;
in vec3 normal;
in vec2 map_coord;
out vec4 color;
in float level;
in vec4 t_color;
void main()
{
	vec4 diffuse = texture2D(uDiffuseMapUniform, map_coord);
	vec4 n = texture2D(uNormalMapUniform, tex_coord);	
	float s = abs(dot(normalize(vec3(uLightDirection)), normalize(normal)));

	color = diffuse * s;
}