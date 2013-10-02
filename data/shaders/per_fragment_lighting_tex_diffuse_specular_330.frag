#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"
#include "/material.glsl"

uniform mat4 uView;
uniform vec3 uCameraWorldPosition;
uniform sampler2D uDiffuseMap;

uniform Material uMaterial;
uniform Light uLight[MAX_LIGHTS];

in vec3 vWorldVertexNormal;
in vec3 vWorldVertexPosition;
in vec2 vVertexTextureCoord0;
out vec4 vFragmentColor;

void main()
{
    vec4 primary = vec4(0,0,0,0);
    vec4 secondary = vec4(0,0,0,0);
    vec3 n = normalize(vWorldVertexNormal); //  normal in world space
    vec3 v = normalize(uCameraWorldPosition - vWorldVertexPosition); //  point to eye vector in world space
    vec3 l; //  vector from object to light in world space
    vec3 h; //  half vector in world space

    for (int i = 0; i != MAX_LIGHTS; ++i)
    {
        if (uLight[i].enabled == 0)
            continue;

        AttenuationResult a = LightAttenuation(uLight[i], vWorldVertexPosition); //  attenuation constant
        float c = a.c;
        vec3 l = a.l;

        vec3 h = normalize(v + l);
        float d = max(0.0, dot(l, n));
        float s = pow(dot(n, h), uMaterial.shininess);

        //light_color += max(0.0, dot(object_to_light, normalize(vViewVertexNormal)));
        primary = c * uLight[i].diffuse_color * max(dot(n,l), 0);
        secondary = c*uLight[i].specular_color * pow(max(dot(n,h),0), uMaterial.shininess);
    }
    vec4 diffuse_texture = texture2D(uDiffuseMap, vVertexTextureCoord0);
    vFragmentColor = uMaterial.specular * secondary + uMaterial.diffuse * primary * diffuse_texture;
}
