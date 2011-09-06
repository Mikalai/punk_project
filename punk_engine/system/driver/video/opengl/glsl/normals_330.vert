#version 330

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat3 uNormalMatrix;

uniform mat4 uProjViewWorld;
uniform mat4 uViewWorld;
uniform vec3 uLightPosition;

out vec3 Normals;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Texcoord;
layout(location = 3) in vec4 rm_Binormal;
layout(location = 4) in vec4 rm_Tangent;

void main(void)
{
	gl_Position = uProj*uView*uWorld * rm_Vertex; 
	
	Normals = uNormalMatrix*rm_Binormal.xyz*rm_Tangent.w;
}

	