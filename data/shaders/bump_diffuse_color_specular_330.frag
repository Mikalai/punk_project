#version 330

#extension GL_ARB_shading_language_include : require

#include "/material.glsl"
#include "/light.glsl"

uniform Material uMaterial;
uniform Light uLight;
uniform sampler2D uNormalMap;

in vec2 vVertexTextureCoord0;
in vec3 vViewDirection;
in vec3 vLightDirection;

out vec4 vFragmentColor;

void main()
{
        vec3 LightDir = normalize(vLightDirection);

        vec3 Normal = normalize((texture(uNormalMap, vVertexTextureCoord0).xyz * 2.0) - 1.0);

        float NDotL = max(0.0, dot(Normal, LightDir));

        vec3 Reflection = normalize(((2.0 * Normal)*NDotL) - LightDir);

        vec3 ViewDir = normalize(vViewDirection );

        float RDotV = max(0.0, dot(Reflection, ViewDir));

        vec4 BaseColor = uMaterial.diffuse;

        vec4 TotalAmbient = uLight.ambient_color * BaseColor;

        vec4 TotalDiffuse = uLight.diffuse_color * NDotL * BaseColor;

        vec4 TotalSpecular = uLight.specular_color * (pow(RDotV, uMaterial.shininess));

        vFragmentColor = vec4((TotalAmbient + TotalDiffuse + TotalSpecular).xyz, 1);
}
