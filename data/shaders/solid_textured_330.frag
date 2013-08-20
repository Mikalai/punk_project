#version 330

uniform sampler2D uDiffuseMap;
uniform vec4 uDiffuseColor;

in vec2 vTexture0;

out vec4 vFragmentColor;

void main(void)
{	
    vec4 c = texture(uDiffuseMap, vTexture0);
    vFragmentColor = c * uDiffuseColor;
}
