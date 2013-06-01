#version 330

#define MAX_LIGHTS 8

uniform mat4 uView;
uniform vec4 uDiffuseColor;

uniform vec4 uLightPosition[MAX_LIGHTS];
uniform vec4 uLightDirection[MAX_LIGHTS];
uniform vec4 uLightDiffuse[MAX_LIGHTS];

uniform float uConstantAttenuation[MAX_LIGHTS];
uniform float uLinearAttenuation[MAX_LIGHTS];
uniform float uQuadricAttenuation[MAX_LIGHTS];

uniform int uMode[MAX_LIGHTS]; //	0 - Constant, 1 - Linear, 2 - Quadric
uniform float uSpotExponent[MAX_LIGHTS];
uniform int uType[MAX_LIGHTS];	//	0 - point, 1 - linear

in vec3 normal;
in vec3 position;

out vec4 color;

float AttenuationConstant(float k0)
{
	return 1.0 / k0;
}

float AttenuationLinear(float k0, float k1, float dst)
{
	return 1.0f / (k0 + k1 * dst);
}

float AttenuationQuadric(float k0, float k1, float k2, float dst)
{
	return 1.0f / (k0 + k1 * dst + k2 * dst * dst);
}

float SpotAttenuation(vec3 r, vec3 l, float p)
{
	return pow(max(dot(-r, l), 0), p);
}

void main()
{
	int i;
	vec4 light_color = vec4(0,0,0,0);
	for (i = 0; i != MAX_LIGHTS; ++i)
	{
		vec3 light_position = (uView * uLightPosition[i]).xyz;
		vec3 object_to_light = normalize(light_position - position);			
		
		float dst = length(light_position - position);
				
		float sc = 1;
		if (uType[i] == 1)
		{		
			float p = uSpotExponent[i];
			vec3 light_direction = normalize((uView * uLightDirection[i]).xyz);		
			sc = SpotAttenuation(light_direction, object_to_light, p);
		}
		
		float k0 = uConstantAttenuation[i];
		float k1 = uLinearAttenuation[i];
		float k2 = uQuadricAttenuation[i];	
		int mode = uMode[i];
		
		float c = 1;
		if (mode == 0)
			c = AttenuationConstant(k0);
		else if (mode == 1)
			c = AttenuationLinear(k0, k1, dst);
		else if (mode == 2)
			c = AttenuationQuadric(k0, k1, k2, dst);
			
		light_color += sc * c * uLightDiffuse[i] * max(0.0, dot(object_to_light, normalize(normal)));		
	}	
	color = light_color * uDiffuseColor;
}	