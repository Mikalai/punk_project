
#version 330

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uMeshMatrix;
uniform mat4 uMeshMatrixInversed;
uniform mat3 uNormalMatrix;

uniform mat4 uProjViewWorld;
uniform mat4 uViewWorld;
uniform vec3 uLightPosition;

uniform mat4 uBones[64];

out vec2 Texcoord;
out vec3 ViewDirection;
out vec3 LightDirection;

layout(location = 0) in vec4 rm_Vertex;
layout(location = 1) in vec4 rm_Normal;
layout(location = 2) in vec4 rm_Tangent;
layout(location = 3) in vec4 rm_Binormal;
layout(location = 4) in vec4 rm_Texcoord;
layout(location = 5) in vec4 rm_BonesId;
layout(location = 6) in vec4 rm_Weights;

out vec4 Weights;

void main(void)
{	
	vec4 pos =  vec4(0.0, 0.0, 0.0, 0.0);
	vec3 norm = vec3(0.0, 0.0, 0.0);
	vec3 tang = vec3(0.0, 0.0, 0.0);
	vec3 bitang = vec3(0.0, 0.0, 0.0);
	
	vec4 b_id = rm_BonesId;
	vec4 weight = rm_Weights;
	
	for (int i = 0; i < 4; i++)
	{
		if (b_id[i] >= 0)
		{
			
			//mat4 m44 = uMeshMatrixInversed*uBones[int(b_id[i])]*uMeshMatrix;	
			mat4 m44 = uBones[int(b_id[i])];	
			mat3 m33 = mat3(m44[0].xyz, m44[1].xyz, m44[2].xyz);
		
			pos += m44 * vec4(rm_Vertex.xyz, 1.0) * weight[i];	
		
			norm += m33*rm_Normal.xyz * weight[i];
			tang += m33*rm_Tangent.xyz * weight[i];
			tang += m33*rm_Binormal.xyz * weight[i];
		}
//		b_id.xyzw = b_id.yzwx;
//		weight.xyzw = weight.yzwx;
	}
		
	pos = pos / pos.w;
	
	if (pos.w > 1)
		Weights.x = 0;
	else
		Weights.x = pos.w;
					 
	gl_Position = uProj*uView*uWorld*pos;
				   	
	vec4 ObjectPosition = uView * uWorld * pos;
	vec3 ViewDir = ObjectPosition.xyz;
	vec3 LightDir = (uView*vec4(uLightPosition, 1.0)).xyz - ObjectPosition.xyz;
	
	vec3 Normal = normalize(uNormalMatrix * norm);
	vec3 Tangent = normalize(uNormalMatrix * tang);
	vec3 Binormal = normalize(uNormalMatrix * bitang);
	
	ViewDirection.x = dot(Tangent, ViewDir);
	ViewDirection.y = dot(Binormal, ViewDir);
	ViewDirection.z = dot(Normal, ViewDir);
	
	LightDirection.x = dot(Tangent, LightDir);
	LightDirection.y = dot(Binormal, LightDir);
	LightDirection.z = dot(Normal, LightDir);
	
	Texcoord = rm_Texcoord.xy; 
}

	