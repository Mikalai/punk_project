#version 330
#extension GL_EXT_texture_array : enable

uniform sampler2D uDiffuseMap;
uniform vec4 uFarDistance;
uniform sampler2DArray uShadowTextureArray;
uniform mat4x4 uTextureMatrix[4];

in vec4 vViewModelPosition;
in vec2 vTexture0;

float shadowCoef()
{
    int index = 3;

    // find the appropriate depth map to look up in based on the depth of this fragment
    if(gl_FragCoord.z < uFarDistance.x)
        index = 0;
    else if(gl_FragCoord.z < uFarDistance.y)
        index = 1;
    else if(gl_FragCoord.z < uFarDistance.z)
        index = 2;

    // transform this fragment's position from view space to scaled light clip space
    // such that the xy coordinates are in [0;1]
    // note there is no need to divide by w for othogonal light sources
    vec4 shadow_coord = uTextureMatrix[index] * vViewModelPosition;

    shadow_coord.w = shadow_coord.z;

    // tell glsl in which layer to do the look up
    shadow_coord.z = float(index);

    // get the stored depth
    float shadow_d = texture2DArray(uShadowTextureArray, shadow_coord.xyz).x;

    // get the difference of the stored depth and the distance of this fragment to the light
    float diff = shadow_d - shadow_coord.w;

    // smoothen the result a bit, to avoid aliasing at shadow contact point
    return clamp( diff*250.0 + 1.0, 0.0, 1.0);
}

out vec4 color;

void main()
{
    const float shadow_ambient = 0.9;
    vec4 color_tex = texture2D(uDiffuseMap, vTexture0);
    float shadow_coef = shadowCoef();
    float fog = clamp(gl_Fog.scale*(gl_Fog.end + vViewModelPosition.z), 0.0, 1.0);
    color = mix(gl_Fog.color, (shadow_ambient * shadow_coef * gl_Color * color_tex + (1.0 - shadow_ambient) * color_tex), fog);
}
