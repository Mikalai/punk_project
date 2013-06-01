#version 330

uniform mat4 uProjViewWorld;

out vec4 vertex_color;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 4) in vec4 rm_Color;

void main()
{
    gl_Position = uProjViewWorld*vec4(rm_Vertex.xyz, 1.0);
    vertex_color = rm_Color;
}
