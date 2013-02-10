#version 330

uniform sampler2D uNormalMapUniform;
uniform sampler2D uDiffuseMapUniform1;
uniform sampler2D uDiffuseMapUniform2;
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
	vec4 diffuse1 = vec4(texture(uDiffuseMapUniform1, map_coord).rgb, 1.0);
	vec4 diffuse2 = vec4(texture(uDiffuseMapUniform2, map_coord).rgb, 1.0);
	vec3 n = normalize(normal);
	float cosa = max(0, sqrt(n.y*n.y));
	vec4 diffuse = vec4(1,0,0,1);
	if (cosa > 0.9)
		diffuse = diffuse1;
	else if (cosa <= 0.9 && cosa >= 0.1)
		diffuse = mix(diffuse1, diffuse2, (0.9 - cosa) / (0.9 - 0.1));
	else
		diffuse = diffuse2;

	float s = max(0, dot(normalize(vec3(uLightDirection)), n));
	diffuse *= s;
	diffuse.w = 1.0;

	if (cosa > 1)
		diffuse = vec4(1,1,1,1);

	//vec4 n = vec4(1,1,1,1);//texture2D(uNormalMapUniform, tex_coord);	

	if (map_coord.x < 0)
		color  = vec4(0,1,0,1);
	else if (map_coord.y < 0)
		color  = vec4(0,0,1,1);
	else
		color = diffuse;	
}