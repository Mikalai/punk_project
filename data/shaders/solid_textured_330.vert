#version 330

uniform mat4 uProjViewWorld;
uniform mat4 uTextureMatrix;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 5) in vec4 rm_Texcoord;

out vec2 vTexture0;

void main(void)
{
    gl_Position = uProjViewWorld * vec4(rm_Vertex.xyz, 1.0);
    vTexture0 = (uTextureMatrix * vec4(rm_Texcoord.xy, 0, 1)).xy;
}
