#version 330

uniform vec4 uDiffuseColor;
uniform vec4 uTextColor;
uniform vec4 uUseTexture;
uniform sampler2D uDiffuseMap;
uniform sampler2D uTextMap;

in vec2 pos;
in vec2 texCoord;
in vec2 diffuseMapTexcoord;
out vec4 color;

void main(void)
{
	vec4 diffuse_color;
	if (uUseTexture.r > 0.9)
		diffuse_color = texture(uDiffuseMap, diffuseMapTexcoord);
	else
		diffuse_color = uDiffuseColor;	

	vec4 mask;
	if (uUseTexture.g > 0.9)
		mask = texture(uTextMap, texCoord);
	else
		mask = vec4(0,0,0,1);

	vec4 text_color = uTextColor * vec4(mask.r, mask.r, mask.r, 1);

	color = mix(diffuse_color, uTextColor, mask.r);
}