#version 330

#define MAX_LIGHTS 8

uniform mat3 uNormalMatrix;
uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;
uniform mat4 uView;
uniform mat4 uTextureMatrix;

uniform vec4 uLightPosition[MAX_LIGHTS];
uniform vec4 uLightDirection[MAX_LIGHTS];
uniform vec4 uLightDiffuse[MAX_LIGHTS];

uniform float uConstantAttenuation[MAX_LIGHTS];
uniform float uLinearAttenuation[MAX_LIGHTS];
uniform float uQuadricAttenuation[MAX_LIGHTS];

uniform int uMode[MAX_LIGHTS]; //	0 - Constant, 1 - Linear, 2 - Quadric
uniform float uSpotExponent[MAX_LIGHTS];
uniform int uType[MAX_LIGHTS];	//	0 - point, 1 - linear

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 5) in vec4 rm_Texcoord;

out vec4 vertex_color_transparent;
out vec4 vertex_color_opaque;
out vec2 tex_coord0;

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
	
	gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
	
	vec3 object_position = (uViewWorld * vec4(rm_Vertex.xyz, 1.0)).xyz;
	vec3 normal = normalize(uNormalMatrix * rm_Normal.xyz);
	vertex_color_opaque = vec4(0,0,0,1);
	vertex_color_transparent = vec4(0,0,0,1);
	
	for (i = 0; i != MAX_LIGHTS; ++i)
	{
		vec3 light_position = (uView * vec4(uLightPosition[i].xyz, 1.0)).xyz;
		vec3 lightDir = normalize(light_position - object_position);		
		float dst = length(light_position - object_position);
		
		float sc = 1;
		if (uType[i] == 1)
		{		
			float p = uSpotExponent[i];
			vec3 light_direction = normalize((uView * uLightDirection[i]).xyz);		
			sc = SpotAttenuation(light_direction, lightDir, p);
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
		c = min(1, c);

		float back = dot(lightDir, normal);
		vertex_color_opaque += sc * c * uLightDiffuse[i] * max(0, back);
		vertex_color_transparent += sc * c * uLightDiffuse[i] * abs(back);
	}	
	tex_coord0 = (uTextureMatrix * rm_Texcoord).xy;
}
