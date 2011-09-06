
#include "../driver/video/opengl/os.h"
#include "../driver/video/opengl/camera.h"
#include "advanced_static_mesh.h"
#include "../driver/video/opengl/light.h"
#include "../driver/video/opengl/driver.h"

namespace Render
{
    AdvancedStaticMesh::AdvancedStaticMesh()
    {
    }

    void AdvancedStaticMesh::Init()
    {
		Driver::Video::CheckError("");

        m_bbox.Create(&(m_vertex[0].x), sizeof(Vertex), m_vertexCount);

		if (Driver::g_openGLDriver.OpenGLVersion >= 300)
        {
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);
        }

        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(Vertex), m_vertex, GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(unsigned short), m_index, GL_STATIC_DRAW);
        //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indexCount*sizeof(unsigned short), m_index);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(m_vertexAttrib);
        glEnableVertexAttribArray(m_normalAttrib);
        if (m_textureVertexAttrib != -1) {
            glEnableVertexAttribArray(m_textureVertexAttrib);
            glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(Vertex), (void*)Vertex::TextureOffset);
        }
        glEnableVertexAttribArray(m_binormalAttrib);
        glEnableVertexAttribArray(m_tangentAttrib);
        glVertexAttribPointer(m_vertexAttrib, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void*)Vertex::PositionOffset);
        glVertexAttribPointer(m_normalAttrib, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void*)Vertex::NormalOffset);
        glVertexAttribPointer(m_binormalAttrib, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void*)Vertex::BinormalOffset);
        glVertexAttribPointer(m_tangentAttrib, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), (void*)Vertex::TangentOffset);

        if (Driver::g_openGLDriver.OpenGLVersion >= 300)
        {
            glBindVertexArray(0);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    AdvancedStaticMesh::~AdvancedStaticMesh()
    {
        delete[] m_vertex;
        delete[] m_index;
        if (Driver::g_openGLDriver.OpenGLVersion > 300)
        {
            glDeleteVertexArrays(1, &m_vao);
        }
        glDeleteBuffers(1, &m_vertexBuffer);
        glDeleteBuffers(1, &m_indexBuffer);
    }

    void AdvancedStaticMesh::Render()
    {
        if (Driver::g_openGLDriver.OpenGLVersion >= 300)
            glBindVertexArray(m_vao);
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        }


        Math::mat4 view = CommonStaff::g_camera.ViewMatrix();
        Math::mat4 proj = CommonStaff::g_camera.ProjectionMatrix();
        Math::mat4 worldViewProj = m_matrix*view*proj;
		Math::mat3 normal = view.RotationPart().Inversed().Transposed();
        Math::vec3 pos(CommonStaff::g_camera.position[0], CommonStaff::g_camera.position[1], CommonStaff::g_camera.position[2]);

		Driver::Video::Light light;
        light.m_Position = vec3(-100,100,100);
        int passCount = m_program->GetPassCount();
        for (int i = 0; i < passCount; i++)
        {
            m_program->Bind(i);
			Driver::Video::CheckError("-1");

            m_program->SetUniformMatrix4f("uWorldViewProj", worldViewProj.m);
            m_program->SetUniformMatrix4f("uWorldView", (m_matrix*view).m);
            m_program->SetUniformVector3f("uEyePosition", pos);
            m_program->SetUniformVector4f("uAmbient", light.m_Ambient);
            m_program->SetUniformVector4f("uDiffuse", light.m_Diffuse);
            m_program->SetUniformVector3f("uLightPosition", light.m_Position);
            m_program->SetUniformVector4f("uSpecular", light.m_Specular);
            m_program->SetUniformFloat("uSpecularPower", light.m_SpecularPower);
            if (m_baseMapUniform != -1)
                m_program->SetTexture("uBaseMap", 0);
            if (m_bumpMapUniform != -1)
                m_program->SetTexture("uBumpMap", 1);

			Driver::Video::CheckError("0");
            if (m_baseMapUniform != -1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, m_baseMap);
            }
            if (m_bumpMapUniform != -1)
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, m_normalMap);
                Driver::Video::CheckError("1");
            }

            //glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
			if (Driver::g_openGLDriver.OpenGLVersion >= 300)
            {
            }
            else
            {
                glEnableVertexAttribArray(m_vertexAttrib);
                glEnableVertexAttribArray(m_normalAttrib);
                if (m_textureVertexAttrib != -1) {
                    glEnableVertexAttribArray(m_textureVertexAttrib);
                    glVertexAttribPointer(m_textureVertexAttrib, 2, GL_FLOAT, GL_FALSE,
                                          sizeof(Vertex), (void*)Vertex::TextureOffset);
                }
                glEnableVertexAttribArray(m_binormalAttrib);
                glEnableVertexAttribArray(m_tangentAttrib);
                glVertexAttribPointer(m_vertexAttrib, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex), (void*)Vertex::PositionOffset);
                glVertexAttribPointer(m_normalAttrib, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex), (void*)Vertex::NormalOffset);
                glVertexAttribPointer(m_binormalAttrib, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex), (void*)Vertex::BinormalOffset);
                glVertexAttribPointer(m_tangentAttrib, 3, GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex), (void*)Vertex::TangentOffset);
            }
            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);


        }
		if (Driver::g_openGLDriver.OpenGLVersion >= 300)
            glBindVertexArray(0);
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        Driver::Video::CheckError("6");
        m_program->Unbind();
    }

    ShaderProgram* AdvancedStaticMesh::GetProgram()
    {
        return m_program;
    };

    AdvancedStaticMesh* AdvancedStaticMesh::CreateFromFile(const char *filename)
    {
        FILE* f = 0;
        AdvancedStaticMesh* mesh = new AdvancedStaticMesh();
        f = fopen(filename, "rb");
        if (f == 0)
            throw System::Exception(std::string("Scene::CreateStaticMeshWithMultiTextureFromFile: File not found") + filename);
        fread(mesh->m_matrix.m, sizeof(float), 16, f);
        fread(&mesh->m_vertexCount, sizeof(int), 1, f);
        fread(&mesh->m_indexCount, sizeof(int), 1, f);
        mesh->m_indexCount *= 3;
        //
        //	memory malloc will be only one. for vertex,
        //	besides vertex there also will be data such
        //	as normals texture cooeds and other
        mesh->m_vertex = new AdvancedStaticMesh::Vertex[mesh->m_vertexCount];
        mesh->m_index = new unsigned short[mesh->m_indexCount];
        fread(mesh->m_vertex, sizeof(Vertex), mesh->m_vertexCount, f);
        fread(mesh->m_index, sizeof(unsigned short), mesh->m_indexCount, f);
        fclose(f);

        //m_StaticMeshWithMultiTextureContainer.push_back(mesh);
        return mesh;

    }

    void AdvancedStaticMesh::SetDecalMap(GLuint decal)
    {
        m_baseMap = decal;
    }

    void AdvancedStaticMesh::SetProgram(ShaderProgram* program)
    {
        m_program = program;
    }

    void AdvancedStaticMesh::SetBumpMap(GLuint bump)
    {
        m_normalMap = bump;
    }

    void AdvancedStaticMesh::FlipNormals()
    {
        for (int i = 0; i < m_vertexCount; i++)
        {
            m_vertex[i].nx = -m_vertex[i].nx;
            m_vertex[i].ny = -m_vertex[i].ny;
            m_vertex[i].nz = -m_vertex[i].nz;/**/

            m_vertex[i].bx = -m_vertex[i].bx;
            m_vertex[i].by = -m_vertex[i].by;
            m_vertex[i].bz = -m_vertex[i].bz;/**/

            m_vertex[i].tx = -m_vertex[i].tx;
            m_vertex[i].ty = -m_vertex[i].ty;
            m_vertex[i].tz = -m_vertex[i].tz;/**/
        }
    }

    void AdvancedStaticMesh::BindShaderData()
    {
        m_vertexAttrib = m_program->GetAttribLocation("rm_Vertex");
        m_textureVertexAttrib = m_program->GetAttribLocation("rm_Texcoord");
        m_normalAttrib = m_program->GetAttribLocation("rm_Normal");
        m_tangentAttrib = m_program->GetAttribLocation("rm_Tangent");
        m_binormalAttrib = m_program->GetAttribLocation("rm_Binormal");
        m_worldViewProjUniform = m_program->GetUniformLocation("uWorldViewProj");
        m_baseMapUniform = m_program->GetUniformLocation("uBaseMap");
        m_worldViewUniform = m_program->GetUniformLocation("uWorldView");
        m_lightDirUniform = m_program->GetUniformLocation("uLightDir");
        m_normalUniform = m_program->GetUniformLocation("uNormal");
        m_bumpMapUniform = m_program->GetUniformLocation("uBumpMap");
        m_eyePositionUniform = m_program->GetUniformLocation("uEyePosition");
        m_lightPositionUniform = m_program->GetUniformLocation("uLightPosition");
        m_lightAmbientUniform = m_program->GetUniformLocation("uAmbient");
        m_lightDiffuseUniform = m_program->GetUniformLocation("uDiffuse");
        m_lightSpecularUniform = m_program->GetUniformLocation("uSpecular");
        m_specularPowerUniform = m_program->GetUniformLocation("uSpecularPower");
    }

    AdvancedStaticMesh* AdvancedStaticMesh::CreateCube(float length, float width, float height, int lSeg, int wSeg, int hSeg)
    {
        int faceCount = (lSeg*wSeg*2+lSeg*hSeg*2+wSeg*hSeg*2)*2;
        int vertexCount = faceCount*3;
        float* vertex = new float[vertexCount*3*6];
        float* normal = vertex + vertexCount*3;
        float* texture = normal + vertexCount*3;
        unsigned short* index = new unsigned short[faceCount*3];
        unsigned vertexID = 0;
        unsigned faceID = 0;
        float lStep = length / lSeg;
        float wStep = width / wSeg;
        float hStep = height / hSeg;
        for (int k = 0; k < 2; k++)
        {
            for (int i = 0; i < wSeg; i++)
            {
                for (int j = 0; j < lSeg; j++)
                {
                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;

                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = k*height;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;
                }
            }
        }

        for (int k = 0; k < 2; k++)
        {
            for (int i = 0; i < hSeg; i++)
            {
                for (int j = 0; j < lSeg; j++)
                {
                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = i*hStep;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = i*hStep;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = (i+1)*hStep;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;

                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = i*hStep;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = (j+1)*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = (i+1)*hStep;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = j*lStep;
                    vertex[vertexID*3+1] = k*width;
                    vertex[vertexID*3+2] = (i+1)*hStep;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;
                }
            }
        }

        for (int k = 0; k < 2; k++)
        {
            for (int i = 0; i < wSeg; i++)
            {
                for (int j = 0; j < hSeg; j++)
                {
                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = j*hStep;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = (j+1)*hStep;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = (j+1)*hStep;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;

                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = i*wStep;
                    vertex[vertexID*3+2] = j*hStep;
                    index[faceID*3+0] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = (j+1)*hStep;
                    index[faceID*3+1] = vertexID;
                    vertexID++;
                    vertex[vertexID*3+0] = k*length;
                    vertex[vertexID*3+1] = (i+1)*wStep;
                    vertex[vertexID*3+2] = j*hStep;
                    index[faceID*3+2] = vertexID;
                    vertexID++;
                    faceID++;
                }
            }
        }

        //
        //	calculate normals
        //
        for (int i = 0; i < faceCount; i++)
        {
            float* v1 = &vertex[3*index[3*i+0]];
            float* v2 = &vertex[3*index[3*i+1]];
            float* v3 = &vertex[3*index[3*i+2]];
            float* n1 = &normal[3*index[3*i+0]];
            float* n2 = &normal[3*index[3*i+1]];
            float* n3 = &normal[3*index[3*i+2]];
            float out1[3];
            float out2[3];
            float out3[3];
            Math::glSubVector3fv(out1, v1, v2);
            Math::glSubVector3fv(out2, v1, v3);
            Math::glNormalize3fv(out1, Math::glCrossProduct3fv(out1, out2, out3));

            Math::glSubVector3fv(out1, v1, v2);
            Math::glSubVector3fv(out2, v1, v3);
            Math::glNormalize3fv(n1, Math::glCrossProduct3fv(n1, out1, out2));

            Math::glSubVector3fv(out1, v2, v1);
            Math::glSubVector3fv(out2, v2, v3);
            Math::glNormalize3fv(n2, Math::glCrossProduct3fv(n2, out1, out2));

            Math::glSubVector3fv(out1, v3, v1);
            Math::glSubVector3fv(out2, v3, v2);
            Math::glNormalize3fv(n3, Math::glCrossProduct3fv(n3, out1, out2));
        }

        SetCacheSize(16);
        SetListsOnly(true);
        PrimitiveGroup* groups;
        PrimitiveGroup* remappedGroups;
        unsigned short numGroups;
        GenerateStrips(index, faceCount*3, &groups, &numGroups);
        RemapIndices(groups, numGroups, vertexCount, &remappedGroups);
        delete[] groups;
        delete[] index;
        //AdvancedStaticMesh* mesh = new AdvancedStaticMesh(vertexCount*3, faceCount*3, vertex, texture, normal, index);
        //AdvancedStaticMesh* mesh = new AdvancedStaticMesh(vertexCount*3, groups[0].numIndices, vertex, texture, normal, groups[0].indices);
        //AdvancedStaticMesh* mesh = new AdvancedStaticMesh(vertexCount*3, remappedGroups[0].numIndices, vertex, texture, normal, remappedGroups[0].indices);
        return NULL;
    }
}
