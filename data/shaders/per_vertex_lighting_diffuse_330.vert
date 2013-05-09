#version 330

#define MAX_LIGHTS 8

uniform mat3 uNormalMatrix;
uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;
uniform mat4 uView;

uniform vec4 uLightPosition[MAX_LIGHTS];
uniform vec4 uLightDiffuse[MAX_LIGHTS];

uniform float uConstantAttenuation[MAX_LIGHTS];
uniform float uLinearAttenuation[MAX_LIGHTS];
uniform float uQuadricAttenuation[MAX_LIGHTS];

uniform int uMode[MAX_LIGHTS]; //	0 - Constant, 1 - Linear, 2 - Quadric

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;

out vec4 vertex_color;

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

void main()
{	
	int i;
	
	gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
	
	vec3 object_position = (uViewWorld * vec4(rm_Vertex.xyz, 1.0)).xyz;
	vec3 normal = normalize(uNormalMatrix * rm_Normal.xyz);
	vertex_color = vec4(0,0,0,1);
	
	for (i = 0; i != MAX_LIGHTS; ++i)
	{
		vec3 light_position = (uView * vec4(uLightPosition[i].xyz, 1.0)).xyz;
		vec3 lightDir = normalize(light_position - object_position);		
		float dst = length(light_position - object_position);
		
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
		
		vertex_color += c * uLightDiffuse[i] * max(0.0, dot(lightDir, normal));
	}	
}