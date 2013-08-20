#version 330

uniform sampler2D uTextMap;
uniform vec4 uDiffuseColor;

in vec2 vTexture0;

out vec4 vFragmentColor;

void main(void)
{	
    vec4 c = texture(uTextMap, vTexture0).rrrr;
    vFragmentColor = c * uDiffuseColor;
}
