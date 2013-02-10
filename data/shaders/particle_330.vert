#version 330

uniform mat4 uProjViewWorld;
uniform float uTime;
uniform int uUseGravity;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Velocity;
layout(location = 4) in vec4 rm_Texcoord;

out vec2 texCoord;
out float life_time;
out float cur_time;
out float start_time;

vec3 GetPosition(vec3 vel)
{
	float start_time = rm_Vertex.w;
	vec3 position = rm_Vertex.xyz;

	if (start_time > uTime)
		return rm_Vertex.xyz;

	vec3 velocity = vel;

	float time = uTime - start_time;
	if (uUseGravity == 1)
	{
		vec3 gravity = vec3(0, -9.8, 0);		
		vec3 new_pos = position + velocity*time + gravity * time*time / 2.0;
		return new_pos;
	}
	else
	{
		vec3 new_pos = position + velocity*time;
		return new_pos;
	}
}

void main(void)
{
	vec3 vel = rm_Velocity.xyz;
	vec3 position = GetPosition(vel);
	gl_Position = uProjViewWorld * vec4(position, 1.0);
	texCoord = rm_Texcoord.xy;
	life_time = rm_Velocity.w;
	cur_time = uTime;
	start_time = rm_Vertex.w;
	
}