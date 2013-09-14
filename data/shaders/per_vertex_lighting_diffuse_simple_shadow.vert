#version 330

#extension GL_ARB_shading_language_include : require
#include "/light.glsl"

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjViewWorld;
uniform mat3 uNormalMatrix;
uniform vec4 uDiffuseColor;
uniform Light uLight[MAX_LIGHTS];

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;

out vec4 vWorldPosition;
out vec4 vFrontColor;

vec3 GetLightDir(int i)
{
    if (uLight[i].type == 0)    //  point
    {
        vec4 pos = uView * uLight[i].position;
        return normalize(pos.xyzw).xyz;
    }
    else if (uLight[i].type == 1)   //  directional
    {
        vec3 dir = uNormalMatrix * uLight[i].direction.xyz;
        return dir;
    }
    return vec3(0, 0, 1);
}

void main()
{    
    //  transform vertex to the world;
    vWorldPosition = uWorld * vec4(rm_Vertex.xyz, 1.0);
   // vWorldPosition /= vWorldPosition.w;
    //  calculate projected position of the vertex in the unit cube
    gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
    //  find normal coordinates in the camera space
    vec3 normal = normalize(uNormalMatrix * rm_Normal.xyz);
    vec4 light_color = vec4(0, 0, 0, 0);

    for (int i = 0; i != MAX_LIGHTS; ++i)
    {
        if (uLight[i].enabled == 1)
        {
            //  transform light direction to the camera space
            vec3 light_dir = GetLightDir(i);
            //  consider that light is in view space
            light_color += uLight[i].diffuse_color * vec4(max(dot(normal, light_dir), 0.0));
        }
    }

    vFrontColor = vec4(normal, 1);
}
