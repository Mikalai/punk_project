#version 330

uniform float uVertScale;

uniform mat4 uTextureMatrix;
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uProjViewWorld;
uniform mat3 uNormalTransform;
uniform sampler2D uHeightMapUniform;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 4) in vec4 rm_Texcoord0;
layout(location = 6) in vec4 rm_Flags;

out vec2 tex_coord;
out vec2 original_texture_coords;
out vec3 normal;
out float level;
out vec4 t_color;

float GetHeight(vec2 offset)
{
	vec2 t = rm_Texcoord0.xy;
	float h = texture(uHeightMapUniform, t + offset).x;
	return h;
}

vec3 CalcNormal()
{
	const vec2 size = vec2(2.0,0.0);
	const ivec3 off = ivec3(-1,0,1);
	vec2 t = rm_Texcoord0.xy;
    vec4 wave = texture(uHeightMapUniform, t);
    float s11 = wave.x;
    float s01 = textureOffset(uHeightMapUniform, t, off.xy).x;
    float s21 = textureOffset(uHeightMapUniform, t, off.zy).x;
    float s10 = textureOffset(uHeightMapUniform, t, off.yx).x;
    float s12 = textureOffset(uHeightMapUniform, t, off.yz).x;
    vec3 va = normalize(vec3(1, s21-s11, 0));
    vec3 vb = normalize(vec3(0, s12-s10, 1));
    vec4 bump = vec4( cross(va,vb), s11 );

	return bump.xyz;
}

void main()
{
	/*float texture_size = textureSize(uHeightMapUniform, 0);*/
	vec4 the_col;
	float scale = rm_Normal.w;
	float width = rm_Texcoord0.w;
	float offset = rm_Texcoord0.z;

	/*vec2 vertex_pos_offset = vec2(uPosition.x, uPosition.y);	
	vec2 position = GetPosition();*/

	float height = 0;
	//	this is an odd border point that position should be adjusted
	if (rm_Vertex.w > 0.8)
	{
		float h1 = GetHeight(vec2(-offset, 0));
		float h2 = GetHeight(vec2(offset, 0));
		height = 0.5 * (h1 + h2);
	}
	else if (rm_Vertex.w < -0.8)
	{
		float h1 = GetHeight(vec2(0, -offset));
		float h2 = GetHeight(vec2(0, offset));
		height = 0.5 * (h1 + h2);
	}
	else
	{
		height = GetHeight(vec2(0,0));		
	}

	vec4 pos = vec4(rm_Vertex.x, height, rm_Vertex.z, 1.0);	
	gl_Position = uProjection * uView * uWorld * pos;	
	normal = CalcNormal();
	tex_coord = (uTextureMatrix * vec4(rm_Texcoord0.x, rm_Texcoord0.y, 0, 1)).xy * 0.125 * width;	
	original_texture_coords = rm_Texcoord0.xy;
}