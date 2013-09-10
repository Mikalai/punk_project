#version 330
#extension GL_EXT_texture_array : enable

uniform vec4 uFarDistance;
uniform sampler2DArray uShadowTextureArray;
uniform mat4 uShadowMatrix[4];

in vec4 vWorldPosition;
in vec4 vFrontColor;

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
    vec4 shadow_coord = uShadowMatrix[index] * vWorldPosition;
    shadow_coord /= shadow_coord.w;

    float x = shadow_coord.x * 0.5 + 0.5;
    float y = shadow_coord.y * 0.5 + 0.5;
    float z = float(index);
    float depth = shadow_coord.z * 0.5 + 0.5;

    // get the stored depth
    float shadow_d = texture(uShadowTextureArray, vec3(x, y, z)).x;

    float diff = shadow_d - depth;
    // smoothen the result a bit, to avoid aliasing at shadow contact point
    return clamp( diff*250.0 + 1.0, 0.0, 1.0);
}

out vec4 vFragmentColor;

void main()
{
    float p = shadowCoef();
    vFragmentColor = vec4(p);
}
