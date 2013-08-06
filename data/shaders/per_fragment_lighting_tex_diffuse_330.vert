#version 330

uniform mat3 uNormalMatrix;
uniform mat4 uViewWorld;
uniform mat4 uProjViewWorld;
uniform mat4 uTextureMatrix;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 5) in vec4 rm_Texcoord;

out vec3 normal;
out vec2 tex_coord0;
out vec3 position;

void main()
{	
	gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
	position = (uViewWorld * vec4(rm_Vertex.xyz, 1.0)).xyz;
	normal = normalize(uNormalMatrix * rm_Normal.xyz);	
	tex_coord0 = (uTextureMatrix * rm_Texcoord).xy;
}