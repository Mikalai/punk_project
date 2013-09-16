#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"

uniform mat4 uView;
uniform vec4 uDiffuseColor;
uniform Light uLight[MAX_LIGHTS];

in vec3 vViewVertexNormal;
in vec3 vViewVertexPosition;

out vec4 vFragmentColor;

float AttenuationConstant(float k0)
{
    return 1.0 / k0;
}

float AttenuationLinear(float k0, float k1, float dst)
{
    return 1.0f / (k0 + k1 * dst);
}

float AttenuationQuadric(float k0, float k1, float k2, float dst)
{
    return 1.0f / (k0 + k1 * dst + k2 * dst * dst);
}

float SpotAttenuation(vec3 r, vec3 l, float p)
{
    return pow(max(dot(-r, l), 0), p);
}

void main()
{
    int i;
    vec4 light_color = vec4(0,0,0,0);
    for (i = 0; i != MAX_LIGHTS; ++i)
    {
        if (uLight[i].enabled == 0)
            continue;

        vec3 light_position = (uView * uLight[i].position).xyz;
        vec3 object_to_light = normalize(light_position - vViewVertexPosition);

        float dst = length(light_position - vViewVertexPosition);

        float sc = 1;
        if (uLight[i].type == 1)
        {
            float p = uLight[i].spot;
            vec3 light_direction = normalize((uView * uLight[i].direction).xyz);
            sc = SpotAttenuation(light_direction, object_to_light, p);
        }

        float k0 = uLight[i].attenuation_constant;
        float k1 = uLight[i].attenuation_linear;
        float k2 = uLight[i].attenuation_quadric;
        int mode = uLight[i].attenuation_model;

        float c = 1;
        if (mode == 0)
            c = AttenuationConstant(k0);
        else if (mode == 1)
            c = AttenuationLinear(k0, k1, dst);
        else if (mode == 2)
            c = AttenuationQuadric(k0, k1, k2, dst);

        light_color += uLight[i].ambient_color + sc * c * uLight[i].diffuse_color * max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
        //light_color += max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
    }
    vFragmentColor = light_color * uDiffuseColor;
    //vFragmentColor = vec4(object_to_light, 1);
}
