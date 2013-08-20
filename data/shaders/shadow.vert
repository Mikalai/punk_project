#version 330

uniform mat4 uWorld;
uniform mat4 uProjViewWorld;

layout(location = 0) in vec4 rm_Vertex;

out vec4 vWorldPosition;

void main()
{    
    vWorldPosition = uWorld * vec4(rm_Vertex.xyz, 1.0);
    vWorldPosition /= vWorldPosition.w;
    gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
}
