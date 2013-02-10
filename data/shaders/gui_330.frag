#version 330

uniform vec4 uDiffuseColor;
uniform vec4 uTextColor;
uniform vec4 uNoDiffuseTexture;
uniform sampler2D uDiffuseMap;
uniform sampler2D uTextMap;

in vec2 pos;
in vec2 texCoord;
in vec2 diffuseMapTexcoord;
out vec4 color;

void main(void)
{
	vec4 diffuse_color;
	diffuse_color = texture(uDiffuseMap, diffuseMapTexcoord);
	diffuse_color = clamp(diffuse_color + uNoDiffuseTexture, 0.0, 1.0);

	vec4 mask = texture(uTextMap, texCoord);
	vec4 text_color = uTextColor * vec4(mask.r, mask.r, mask.r, 1);
	color = mix(diffuse_color, uTextColor, mask.r);
}