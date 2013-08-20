#version 330
#extension GL_EXT_texture_array : enable

uniform sampler2DArray uMaps;
uniform float uLayer;

in vec2  vTexture0;
out vec4 vFragmentColor;

void main()
{
    vec4 tex_coord = vec4(vTexture0.x, vTexture0.y, uLayer, 1.0);
    vFragmentColor = texture2DArray(uMaps, tex_coord.xyz);
}
