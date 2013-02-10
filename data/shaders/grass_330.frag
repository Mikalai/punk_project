#version 330

uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;

in vec2 pos;
in vec2 texCoord;

out vec4 color;

void main(void)
{	
	vec4 c = texture(uDiffuseMap, texCoord);
	if (c.a > 0.8) 
		color = c;
	else
		discard;
}