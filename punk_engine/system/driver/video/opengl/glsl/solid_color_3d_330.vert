#version 330
//#extension GL_ARB_separate_shader_objects : enable

uniform mat4 uProjViewWorld;

layout(location = 0) in vec3 rm_Vertex;

void main()
{
	int x = gl_InstanceID;
	vec3 p = rm_Vertex;
	
	p.x += float(x)*3.0;
	
	gl_Position = uProjViewWorld * vec4(p, 1.0);
}
