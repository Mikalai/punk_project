#version 330

uniform vec4 uAmbient;
uniform vec4 uSpecular;
uniform vec4 uDiffuse;
uniform float uSpecularPower;
uniform sampler2D uDiffuseMap;
uniform sampler2D uNormalMap;

in vec2 vTexture0;
in vec3 vViewDirection;
in vec3 vLightDirection;

out vec4 vFragmentColor;

void main( void )
{
        vec3 LightDir = normalize(vLightDirection);
	
        vec3 Normal = normalize((texture(uNormalMap, vTexture0).xyz * 2.0) - 1.0);
	
	float NDotL = max(0.0, dot(Normal, LightDir));    
	
	vec3 Reflection = normalize(((2.0 * Normal)*NDotL) - LightDir); 
	
        vec3 ViewDir = normalize(vViewDirection );
	
	float RDotV = max(0.0, dot(Reflection, ViewDir));
	
        vec4 BaseColor = texture(uDiffuseMap, vTexture0);
	
	vec4 TotalAmbient = uAmbient * BaseColor; 
	
	vec4 TotalDiffuse = uDiffuse * NDotL * BaseColor; 
	
	vec4 TotalSpecular = uSpecular * (pow(RDotV, uSpecularPower));

        vFragmentColor = vec4((TotalAmbient + TotalDiffuse + TotalSpecular).xyz, 1);
}
