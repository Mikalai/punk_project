#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"

uniform mat4 uProjViewWorld;
uniform mat4 uViewWorld;
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat3 uNormalMatrix;
uniform mat4 uTextureMatrix;
uniform Light uLight;

out vec2 vVertexTextureCoord0;
out vec3 vViewDirection;
out vec3 vLightDirection;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Tangent;
layout(location = 3) in vec4 rm_Binormal;
layout(location = 5) in vec4 rm_Texture0;

void main(void)
{
        gl_Position = uProjViewWorld * rm_Vertex;
        vec4 ObjectPosition = uViewWorld * rm_Vertex;
        vec3 ViewDir = normalize(ObjectPosition.xyz);
        vec3 LightDir = normalize(LightViewDirection(uLight, ObjectPosition.xyz));

        vec3 Normal = normalize(uNormalMatrix * rm_Normal.xyz);
        vec3 Tangent = normalize(uNormalMatrix * rm_Tangent.xyz);
        vec3 Binormal = normalize(uNormalMatrix * rm_Binormal.xyz); // normalize(rm_Tangent.w * cross(Normal, Tangent));

        vViewDirection.x = dot(Tangent, ViewDir);
        vViewDirection.y = dot(Binormal, ViewDir);
        vViewDirection.z = dot(Normal, ViewDir);

        vLightDirection.x = dot(Tangent, LightDir);
        vLightDirection.y = dot(Binormal, LightDir);
        vLightDirection.z = dot(Normal, LightDir);

        vViewDirection = normalize(vViewDirection);
        vLightDirection = normalize(vLightDirection);

        vVertexTextureCoord0 = (uTextureMatrix * vec4(rm_Texture0.xy, 0, 1)).xy;
}
