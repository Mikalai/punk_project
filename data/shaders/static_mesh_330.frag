#version 330

uniform vec4 uAmbient;
uniform vec4 uSpecular;
uniform vec4 uDiffuse;
uniform float uSpecularPower;
uniform sampler2D uDiffuseMap;
uniform sampler2D uNormalMap;

in vec2 Texcoord;
in vec3 ViewDirection;
in vec3 LightDirection;
out vec4 FragColor;

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
	
	FragColor =  TotalAmbient + TotalDiffuse + TotalSpecular;       
	
}