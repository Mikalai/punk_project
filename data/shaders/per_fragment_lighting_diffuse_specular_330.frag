#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"
#include "/material.glsl"

uniform mat4 uView;
uniform vec3 uCameraWorldPosition;

uniform Material uMaterial;
uniform Light uLight[MAX_LIGHTS];

in vec3 vWorldVertexNormal;
in vec3 vWorldVertexPosition;

out vec4 vFragmentColor;

void main()
{
    int i;
    vec4 light_color = vec4(0,0,0,0);
    vec4 primary = vec4(0,0,0,0);
    vec4 secondary = vec4(0,0,0,0);
    vec3 n = normalize(vWorldVertexNormal); //  normal in world space
    vec3 v = normalize(uCameraWorldPosition - vWorldVertexPosition); //  point to eye vector in world space
    vec3 l; //  vector from object to light in world space
    vec3 h; //  half vector in world space

    for (i = 0; i != MAX_LIGHTS; ++i)
    {
        if (uLight[i].enabled == 0)
            continue;   
        float k0 = uLight[i].attenuation_constant;
        float k1 = uLight[i].attenuation_linear;
        float k2 = uLight[i].attenuation_quadric;
        int mode = uLight[i].attenuation_model;

        float c = 1; //  attenuation constant
        if (uLight[i].type == POINT_LIGHT)
        {
            l = uLight[i].position.xyz - vWorldVertexPosition;
            float dst = length(l);
            l = normalize(l);
            if (mode == ATTENUATION_CONSTANT)
                c = AttenuationConstant(k0);
            else if (mode == ATTENUATION_LINEAR)
                c = AttenuationLinear(k0, k1, dst);
            else if (mode == ATTENUATION_QUADRIC)
                c = AttenuationQuadric(k0, k1, k2, dst);
        }
        else if (uLight[i].type == DIRECTION_LIGHT)
        {
            l = normalize(-uLight[i].direction.xyz);
        }
        else if (uLight[i].type == SPOT_LIGHT)
        {            
            float p  = uLight[i].spot;
            l = uLight[i].position.xyz - vWorldVertexPosition;
            float dst = length(l);
            l = normalize(l);
            float sc = SpotAttenuation(normalize(uLight[i].direction.xyz), l, p);
            if (mode == ATTENUATION_CONSTANT)
                c = sc*AttenuationConstant(k0);
            else if (mode == ATTENUATION_LINEAR)
                c = sc*AttenuationLinear(k0, k1, dst);
            else if (mode == ATTENUATION_QUADRIC)
                c = sc*AttenuationQuadric(k0, k1, k2, dst);
        }

        vec3 h = normalize(v + l);
        float d = max(0.0, dot(l, n));
        float s = pow(dot(n, h), uMaterial.shininess);

        //light_color += max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
        primary = c*uLight[i].diffuse_color * max(dot(n,l), 0);
        secondary = c*uLight[i].specular_color * pow(max(dot(n,h),0), uMaterial.shininess);
    }

    vFragmentColor = uMaterial.specular * secondary + uMaterial.diffuse * primary;    
}
