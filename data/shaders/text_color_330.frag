#version 330

uniform sampler2D uTextMap;
uniform vec4 uDiffuseColor;

in vec2 texCoord;

out vec4 color;

void main(void)
{	
    vec4 c = texture(uTextMap, texCoord).rrrr;
    color = c * uDiffuseColor;
}
