#version 330


in vec3 Normals;
out vec4 FragColor;

void main( void )
{
	FragColor =  vec4(0.5+0.5*Normals, 1.0);       	
}