#version 330

uniform vec4 uAmbient;
uniform vec4 uSpecular;
uniform vec4 uDiffuse;
uniform float uSpecularPower;
uniform sampler2D uDiffuseMap;
uniform sampler2D uNormalMap;
uniform sampler2D uDepthMap;
uniform float uNear;
uniform float uFar;

in vec4 Position;
in vec4 WorldVertex;

in vec2 Texcoord;
in vec3 ViewDirection;
in vec3 LightDirection;
in vec3 LightPosition;
out vec4 FragColor;

float unpack (vec4 colour) 
{ 
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0)); 
	return dot(colour, bitShifts); 
}

void main( void )
{
	vec3 LightDir = normalize(LightDirection);
	
	vec3 Normal = normalize((texture(uNormalMap, Texcoord).xyz * 2.0) - 1.0);
	
	float NDotL = max(0.0, dot(Normal, LightDir));    
	
	vec3 Reflection = normalize(((2.0 * Normal)*NDotL) - LightDir); 
	
	vec3 ViewDir = normalize(ViewDirection );
	
	float RDotV = max(0.0, dot(Reflection, ViewDir));
	
	vec4 BaseColor = texture(uDiffuseMap, Texcoord);
	
	vec4 TotalAmbient = uAmbient * BaseColor; 
	
	vec4 TotalDiffuse = uDiffuse * NDotL * BaseColor; 
	
	vec4 TotalSpecular = uSpecular * (pow(RDotV, uSpecularPower));

	vec4 color = vec4((TotalAmbient + TotalDiffuse + TotalSpecular).xyz, 1);  
 
	vec3 depth = Position.xyz / Position.w;
	float linear_depth_constant = 1.0 / (uFar - uNear);
	depth.z = length(WorldVertex.xyz - LightPosition) * linear_depth_constant;
	float shadow = 1.0
	depth.z *= 0.96;
	float shadowDepth = unpack(texture2D(uDepthMap, depth.xy));
	if (depth.z > shadowDepth)
		shadow = 0.5;

	FragColor = shadow * color;
}
