#version 330

uniform sampler2D uDiffuseMap;
uniform vec4 uDiffuseColor;

in vec2 pos;
in vec2 texCoord;

out vec4 color;

void main(void)
{	
    vec4 c = texture(uDiffuseMap, texCoord);
    color = c * uDiffuseColor;
}
