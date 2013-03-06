#version 330

uniform float uVertScale;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uProjViewWorld;
uniform mat3 uNormalTransform;

//uniform int ui;
//uniform int uj;
uniform int texture_size;
//uniform int uSlice;

uniform sampler2D uHeightMapUniform;

//uniform float uScale;
uniform vec2 uPosition;
uniform vec2 uTerrainPosition;
//uniform float uLevel;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 4) in vec4 rm_Texcoord0;
layout(location = 6) in vec4 rm_Flags;

out vec2 tex_coord;
out vec2 map_coord;
out vec3 normal;
out float level;
out vec4 t_color;

float GetHeight(vec2 pos)
	float texture_size = textureSize(uHeightMapUniform);
	//vec4 t = texture2D(uHeightMapUniform, pos).rgba;
	vec2 offset = vec2(texture_size / 2, texture_size / 2);
	float h = texture2D(uHeightMapUniform, (pos + offset)/ float(texture_size)).r;
	//float h = uVertScale*(255.0*t.x);//+255.0*255.0*t.y + 255.0*255.0*255.0*t.z);
	return h;
}

vec2 GetPosition()
{
	return vec2(uPosition.x - uTerrainPosition.x, uPosition.y - uTerrainPosition.y);
}

vec3 CalcNormal()
{
	vec2 pos = GetPosition();
	//	it is considered that scale is stored in w
	float scale = rm_Normal.w;
	//	it is considered that slice count is stored in z and w
	float offset = scale / rm_Texcoord0.z;

	float hzz = GetHeight(pos + (rm_Vertex.xz));
	float hpz = GetHeight(pos + (rm_Vertex.xz + vec2(offset,0)));
	float hzp = GetHeight(pos + (rm_Vertex.xz + vec2(0,offset)));
	float hnz = GetHeight(pos + (rm_Vertex.xz + vec2(-offset,0)));
	float hzn = GetHeight(pos + (rm_Vertex.xz + vec2(0,-offset)));
	float hpp = GetHeight(pos + (rm_Vertex.xz + vec2(offset,offset)));
	float hnp = GetHeight(pos + (rm_Vertex.xz + vec2(-offset,offset)));
	float hnn = GetHeight(pos + (rm_Vertex.xz + vec2(-offset,-offset)));
	float hpn = GetHeight(pos + (rm_Vertex.xz + vec2(offset,-offset)));

	/*vec3 n1 = normalize(vec3(offset, hpz-hzz, 0));
	vec3 n2 = normalize(vec3(0, hzp-hzz, offset));
	vec3 n3 = normalize(vec3(-offset, hnz-hzz, 0));
	vec3 n4 = normalize(vec3(0, hzn-hzz, -offset));	*/

	vec3 n1 = normalize(vec3(offset, hpz-hzz, 0));
	vec3 n2 = normalize(vec3(offset, hpp-hzz, offset));
	vec3 n3 = normalize(vec3(0, hzp-hzz, offset));
	vec3 n4 = normalize(vec3(-offset, hnp-hzz, offset));	
	vec3 n5 = normalize(vec3(-offset, hnz-hzz, 0));
	vec3 n6 = normalize(vec3(-offset, hnn-hzz, -offset));
	vec3 n7 = normalize(vec3(0, hzn-hzz, -offset));
	vec3 n8 = normalize(vec3(offset, hpn-hzz, -offset));


	/*vec3 nn1 = -normalize(cross(n1, n2));
	vec3 nn2 = -normalize(cross(n2, n3));
	vec3 nn3 = -normalize(cross(n3, n4));
	vec3 nn4 = -normalize(cross(n4, n1));*/

	vec3 nn1 = -normalize(cross(n1, n2));
	vec3 nn2 = -normalize(cross(n2, n3));
	vec3 nn3 = -normalize(cross(n3, n4));
	vec3 nn4 = -normalize(cross(n4, n5));
	vec3 nn5 = -normalize(cross(n5, n6));
	vec3 nn6 = -normalize(cross(n6, n7));
	vec3 nn7 = -normalize(cross(n7, n8));
	vec3 nn8 = -normalize(cross(n8, n1));

	return normalize(nn1+nn2+nn3+nn4+nn5+nn6+nn7+nn8);
	//return normalize(nn1+nn2+nn3+nn4);
}

void main()
{
	float texture_size = textureSize(uHeightMapUniform);
	vec4 the_col;
	float scale = rm_Normal.w;
	float width = rm_Texcoord0.w;
	float offset = width*scale / float(rm_Texcoord0.z);

	vec2 vertex_pos_offset = vec2(uPosition.x, uPosition.y);	
	vec2 position = GetPosition();

	float height = 0;
	//	this is an odd border point that position should be adjusted
	if (rm_Vertex.w > 0.8)
	{
		float h1 = GetHeight(position + rm_Vertex.xz - vec2(offset, 0));
		float h2 = GetHeight(position + rm_Vertex.xz + vec2(offset, 0));
		height = 0.5 * (h1 + h2);
		t_color = vec4(1, 0, 0, 1);
	}
	else if (rm_Vertex.w < -0.8)
	{
		float h1 = GetHeight(position + rm_Vertex.xz - vec2(0, offset));
		float h2 = GetHeight(position + rm_Vertex.xz + vec2(0, offset));
		height = 0.5 * (h1 + h2);
		t_color = vec4(0, 0, 1, 1);
	}
	else
	{
		height = GetHeight(position + rm_Vertex.xz);
		t_color = vec4(1, 1, 1,1);
	}

	vec3 pos = vec3(rm_Vertex.x + vertex_pos_offset.x, height, rm_Vertex.z + vertex_pos_offset.y);
	
	gl_Position = uProjection * uView * vec4(pos, 1.0);	
	
	normal = CalcNormal();
	tex_coord = abs(position + rm_Vertex.xz )  / texture_size * 100;
	map_coord = (vertex_pos_offset + rm_Vertex.xz ) / 10;
}