#version 330

#define SIZE 2048.0
#define SCALE 1.0

uniform mat4 uProjView;
uniform sampler2D uHeightMap;
uniform vec3 uPosition;
uniform float uTime;
uniform float uWindStrength;
uniform vec3 uWindDirection;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 4) in vec4 rm_Texcoord;

out vec2 texCoord;

float GetHeight(float u, float v)
{
	vec4 height = texture(uHeightMap, vec2(u, v));
	float res = SCALE*height.r;
	return 255.0*res;
}

vec3 CalculateOffset(float time, vec3 position, vec3 wind_direction, float wind_strength)
{
	float h1 = -1 + 2*GetHeight(position.x, position.y);
	float h2 = -1 + 2*GetHeight(position.x+0.1, position.y+0.1);
	float h3 = -1 + 2*GetHeight(position.x-0.1, position.y-0.1);
	vec3 dir2 = normalize(vec3(h1, 0, h3));	
	return (dir2)*(wind_strength);
}

void main(void)
{	
	int flag = gl_InstanceID & 1;
	float delta = flag == 0 ? 0 : 0.5;
	float x = uPosition.x + mod(gl_InstanceID, 100.0) * 0.5;	
	float z = uPosition.z + floor(gl_InstanceID / 100.0) * 0.5;
	float u = x / SIZE;
	float v = z / SIZE;
	float y = GetHeight(u, v);

	vec3 position;
	if (rm_Texcoord.y >= 0.9)
	{
		position = rm_Vertex.xyz + CalculateOffset(uTime, vec3(x, y, z), uWindDirection, uWindStrength);
	}
	else
		position = rm_Vertex.xyz;

	gl_Position = uProjView * vec4(x + position.x, y + position.y, z + position.z, 1.0);	
	texCoord = rm_Texcoord.xy;
}