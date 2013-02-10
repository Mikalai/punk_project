#version 330

uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;

in vec2 pos;
in vec2 texCoord;

out vec4 color;

void main(void)
{	
	vec4 c = texture(uDiffuseMap, texCoord);
	color = c;//vec4(texCoord.x, texCoord.y, 0, 1);	
}