#version 330

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat3 uNormalMatrix;
uniform vec3 uLightPosition;
uniform mat4 uTextureMatrix;

out vec2 Texcoord;
out vec3 ViewDirection;
out vec3 LightDirection;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Tangent;
layout(location = 3) in vec4 rm_Binormal;
layout(location = 5) in vec4 rm_Texcoord;

void main(void)
{
	gl_Position = uProj*uView*uWorld * rm_Vertex; 
	
	vec4 ObjectPosition = uView * uWorld * rm_Vertex;
	vec3 ViewDir = normalize(ObjectPosition.xyz);
	vec3 LightDir = normalize((uView*vec4(uLightPosition, 1.0)).xyz - ObjectPosition.xyz);
	
	vec3 Normal = normalize(uNormalMatrix * rm_Normal.xyz);
	vec3 Tangent = normalize(uNormalMatrix * rm_Tangent.xyz);
	vec3 Binormal = normalize(uNormalMatrix * rm_Binormal.xyz); // normalize(rm_Tangent.w * cross(Normal, Tangent));
	
	ViewDirection.x = dot(Tangent, ViewDir);
	ViewDirection.y = dot(Binormal, ViewDir);
	ViewDirection.z = dot(Normal, ViewDir);
	
	LightDirection.x = dot(Tangent, LightDir);
	LightDirection.y = dot(Binormal, LightDir);
	LightDirection.z = dot(Normal, LightDir);
	
	ViewDirection = normalize(ViewDirection);
	LightDirection = normalize(LightDirection);
	
	Texcoord = (uTextureMatrix * vec4(rm_Texcoord.xy, 0, 1)).xy; 
}
