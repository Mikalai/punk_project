#version 330

#define SLICE 16.0
#define MIN -4
#define MAX 3

#define MIN_VERT 1.0 / SLICE
#define MAX_VERT (1.0 - 1.0 / SLICE)

#define OFFSET 1.0 / SLICE
#define VERT_SCALE 1.0
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uProjViewWorld;
uniform mat3 uNormalTransform;

uniform int ui;
uniform int uj;

uniform sampler2D uHeightMapUniform;

uniform float uScale;
uniform vec2 uPosition;
uniform float uLevel;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Texcoord0;
layout(location = 5) in vec4 rm_Flags;

out vec2 tex_coord;
out vec2 map_coord;
out vec3 normal;
out float level;
out vec4 t_color;

vec3 CalcNormal(float scale, float j, float i)
{
	vec2 position = vec2(scale*j + uPosition.x, scale*i + uPosition.y);

	float h00 = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz) / 2048.0).r;
	float hp10 = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz + scale*vec2(OFFSET,0)) / 2048.0).r;
	float hp01 = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz + scale*vec2(0,OFFSET)) / 2048.0).r;
	float hn10 = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz + scale*vec2(-OFFSET,0)) / 2048.0).r;
	float hn01 = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz + scale*vec2(0,-OFFSET)) / 2048.0).r;

	vec2 pos = position + rm_Vertex.xz;

	vec3 p_00 = normalize(vec3(0, h00, 0));
	vec3 n1 = normalize(vec3(scale*OFFSET, hp10-h00, 0));
	vec3 n2 = normalize(vec3(0, hp01-h00, scale*OFFSET));
	vec3 n3 = normalize(vec3(-scale*OFFSET, hn10-h00, 0));
	vec3 n4 = normalize(vec3(0, hn01-h00, -scale*OFFSET));

	vec3 nn1 = normalize(cross(n1, n2));
	vec3 nn2 = -normalize(cross(n2, n3));
	vec3 nn3 = -normalize(cross(n3, n4));
	vec3 nn4 = -normalize(cross(n4, n1));

	return -normalize(nn1+nn2+nn3+nn4);
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
	if (ui == MIN && int(rm_Flags.x) == 1 && rm_Vertex.z < MIN_VERT)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(OFFSET, 0)) / VERT_SCALE) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(OFFSET, 0)) / VERT_SCALE) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(1,0,0,1);
	}
	else if (ui == MAX && int(rm_Flags.x) == 1 && rm_Vertex.z > MAX_VERT)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(OFFSET, 0)) / VERT_SCALE) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(OFFSET, 0)) / VERT_SCALE) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(0,0,1,1);
	}
	else if (uj == MIN && int(rm_Flags.x) == 1 && rm_Vertex.x < MIN_VERT)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(0, OFFSET)) / VERT_SCALE) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(0, OFFSET)) / VERT_SCALE) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(0,1,1,1);
	}
	else if (uj == MAX && int(rm_Flags.x) == 1 && rm_Vertex.x > MAX_VERT)
	{
		vec2 p1 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		vec2 p2 = vec2(scale*j + uPosition.x, scale*i + uPosition.y);
		float h1 = texture2D(uHeightMapUniform, (p1 + scale*(rm_Vertex.xz - vec2(0, OFFSET)) / VERT_SCALE) / 2048.0).r;
		float h2 = texture2D(uHeightMapUniform, (p2 + scale*(rm_Vertex.xz + vec2(0, OFFSET)) / VERT_SCALE) / 2048.0).r;
		height = 0.5 * (h1 + h2);
		t_color = vec4(1,0,1,1);		
	}/**/
	else
	{
		height = texture2D(uHeightMapUniform, (position + scale*rm_Vertex.xz / VERT_SCALE) / 2048.0).r;
		t_color = vec4(1,1,1,1);
	}

	vec3 pos = vec3((scale*rm_Vertex.x / VERT_SCALE + position.x), 2*height, (scale*rm_Vertex.z / VERT_SCALE + position.y));
	
	gl_Position = uProjection * uView * vec4(pos, 1.0);	
	
	normal = CalcNormal(scale, j, i);
	tex_coord = abs(position + scale*rm_Vertex.xz / VERT_SCALE)  / 2048.0;
	map_coord = (position +scale*rm_Vertex.xz / VERT_SCALE);
}