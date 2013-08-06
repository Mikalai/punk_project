#version 330

#define MIN -2
#define MAX 1

#define OFFSET 3.0 / 2.0

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorldViewProj;
uniform mat3 uNormalTransform;

uniform int ui;
uniform int uj;

uniform sampler2D uHeightMapUniform;

uniform float uScale;
uniform vec2 uPosition;
uniform float uLevel;

in vec4 rm_Vertex;
in vec4 rm_Normal;
in vec4 rm_Texcoord0;
in vec4 rm_Flags;

out vec2 tex_coord;
out vec2 map_coord;
out vec3 normal;
out float level;
out vec4 t_color;
vec3 CalcNormal()
{
	float h00 = texture2D(uHeightMapUniform, (uPosition + rm_Vertex.xz) / 2048.0).r;
	float hp10 = texture2D(uHeightMapUniform, (uPosition + rm_Vertex.xz + vec2(1,0)) / 2048.0).r;
	float hp01 = texture2D(uHeightMapUniform, (uPosition + rm_Vertex.xz + vec2(0,1)) / 2048.0).r;
	float hn10 = texture2D(uHeightMapUniform, (uPosition + rm_Vertex.xz + vec2(-1,0)) / 2048.0).r;
	float hn01 = texture2D(uHeightMapUniform, (uPosition + rm_Vertex.xz + vec2(0,-1)) / 2048.0).r;

	vec2 pos = uPosition + rm_Vertex.xz;

	vec3 p_00 = vec3(pos.x, h00, pos.y);
	vec3 p_p10 = vec3(pos.x + 1, hp10, pos.y);
	vec3 p_p01 = vec3(pos.x, hp01, pos.y + 1);
	vec3 p_n10 = vec3(pos.x - 1, hn10, pos.y);
	vec3 p_n01 = vec3(pos.x, hn01, pos.y - 1);

	vec3 n1 = cross(p_p01 - p_00, p_p10 - p_00);
	vec3 n2 = cross(p_n01 - p_00, p_p10 - p_00);
	vec3 n3 = cross(p_n10 - p_00, p_n01 - p_00);
	vec3 n4 = cross(p_p01 - p_00, p_n10 - p_00);

	return normalize(n1+n2+n3+n4);
	//return normalize(n1+n2+n3+n4);
}

void main()
{
	float i = float(ui);
	float j = float(uj);
	float scale = pow(2,uLevel-1);

	vec2 position = vec2(scale*j + uPosition.x, scale*i + uPosition.y);

	level = uLevel;

	float height = 0;
	if (ui == MIN && int(rm_Flags.x) == 1 && rm_Vertex.z < 0.5)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(OFFSET, 0)) / 3.0) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(OFFSET, 0)) / 3.0) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(1,0,0,1);
	}
	else if (ui == MAX && int(rm_Flags.x) == 1 && rm_Vertex.z > 2.5)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(OFFSET, 0)) / 3.0) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(OFFSET, 0)) / 3.0) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(0,0,1,1);
	}
	else if (uj == MIN && int(rm_Flags.x) == 1 && rm_Vertex.x < 0.5)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(0, OFFSET)) / 3.0) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(0, OFFSET)) / 3.0) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(0,1,1,1);
	}
	else if (uj == MAX && int(rm_Flags.x) == 1 && rm_Vertex.x > 2.5)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(0, OFFSET)) / 3.0) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(0, OFFSET)) / 3.0) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(1,0,1,1);		
	}
	else
	{
		height = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz / 3.0) / 2048.0).r;
		t_color = vec4(1,1,1,1);
	}

	vec3 pos = vec3((scale*rm_Vertex.x / 3.0 + position.x), 2*height, (scale*rm_Vertex.z / 3.0 + position.y));
	
	gl_Position = uProjection * uView * vec4(pos, 1.0);	
	
	normal = CalcNormal();
	tex_coord = abs(position + scale*rm_Vertex.xz / 3.0)  / 2048.0;
	map_coord = (position +scale*rm_Vertex.xz / 3.0);
}