#version 330

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat3 uNormalMatrix;
uniform vec3 uLightPosition;
uniform mat4 uTextureMatrix;

out vec2 vTexture0;
out vec3 vViewDirection;
out vec3 vLightDirection;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Tangent;
layout(location = 3) in vec4 rm_Binormal;
layout(location = 5) in vec4 rm_Texture0;

void main(void)
{
	gl_Position = uProj*uView*uWorld * rm_Vertex; 
	
	vec4 ObjectPosition = uView * uWorld * rm_Vertex;
	vec3 ViewDir = normalize(ObjectPosition.xyz);
        vec3 LightDir = normalize((uView * vec4(uLightPosition, 1.0)).xyz - ObjectPosition.xyz);
	
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
	
        vTexture0 = (uTextureMatrix * vec4(rm_Texture0.xy, 0, 1)).xy;
}
