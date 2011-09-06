#version 330

uniform mat4 uProjViewWorld;
uniform mat3 uNormalTransform;
uniform mat3 uView;
uniform vec3 uLightPosition;
uniform vec3 uLightDirection;
uniform vec4 uDiffuseColor;

in vec3 rm_Vertex;
in vec3 rm_Normal;

out vec4 vertex_color;

void main()
{
	gl_Position = uProjViewWorld * vec4(rm_Vertex, 1.0);

	vec3 normal = normalize(uNormalTransform * rm_Normal);
	vec3 lightDir = normalize(uView * uLightDirection);
	vertex_color = uDiffuseColor * max(0.0, dot(lightDir, normal));
}