#version 330

uniform vec4 uDiffuseColor;
out vec4 vFragmentColor;

void main()
{
    vFragmentColor = uDiffuseColor;
}
