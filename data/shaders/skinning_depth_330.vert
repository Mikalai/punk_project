
#version 330

uniform mat4 uProjViewWorld;
uniform mat4 uBones[64];

layout(location = 0) in vec4 rm_Vertex;
layout(location = 9) in vec4 rm_BonesId;
layout(location = 10) in vec4 rm_Weights;

void main(void)
{
        vec4 pos =  vec4(0.0, 0.0, 0.0, 0.0);
        vec4 b_id = rm_BonesId;
        vec4 weight = rm_Weights;

        for (int i = 0; i < 4; i++)
        {
                if (b_id[i] >= 0)
                {
                        mat4 m44 = uBones[int(b_id[i])];
                        mat3 m33 = mat3(m44[0].xyz, m44[1].xyz, m44[2].xyz);

                        pos += m44 * vec4(rm_Vertex.xyz, 1.0) * weight[i];
                }
        }
        pos = pos / pos.w;
        gl_Position = uProjViewWorld*pos;
}


