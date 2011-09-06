
#include "Os.h"
#include "StaticMeshWithVBO.h"

StaticMeshWithVBO::StaticMeshWithVBO(int vCount, int fCount, float *v, float *t, float *n, unsigned short *i) :
m_vertexCount(vCount),
m_indexCount(fCount),
m_vertex(v),
m_texture(t),
m_normals(n),
m_index(i)
{
	m_eye[0] = m_eye[1] = m_eye[2] = 0;
	m_lightColor[0] = 1;
	m_lightColor[1] = 1;
	m_lightColor[2] = 0;
	m_lightColor[3] = 1;

	m_ambientColor[0] = 0;
	m_ambientColor[1] = 0;
	m_ambientColor[2] = 0.5f;
	m_ambientColor[3] = 1;

	m_lightPos[0] = 0;
	m_lightPos[1] = 1;
	m_lightPos[2] = 1;

		//
	//	calculate binormal and tangent
	//
	m_binormal = m_vertex + 4*m_vertexCount;
	m_tangent = m_vertex + 5*m_vertexCount;
	for (int i = 0; i < m_indexCount; i += 3)
	{		
		int a = m_index[i];
		int b = m_index[i+1];
		int c = m_index[i+2];
		float* n1 = &m_normals[3*a];
		float* n2 = &m_normals[3*b];
		float* n3 = &m_normals[3*c];
		float* v1 = &m_vertex[3*a];
		float* v2 = &m_vertex[3*b];
		float* v3 = &m_vertex[3*c];
		float* t1 = &m_tangent[3*a];
		float* t2 = &m_tangent[3*b];
		float* t3 = &m_tangent[3*c];
		float* b1 = &m_binormal[3*a];
		float* b2 = &m_binormal[3*b];
		float* b3 = &m_binormal[3*c];
		if (i%2==0)
			Math::glNormalize3fv(t1, Math::glSubVector3fv(t1, v2, v1));	
		else
			Math::glNormalize3fv(t1, Math::glSubVector3fv(t1, v1, v2));	
		Math::glNormalize3fv(b1, Math::glCrossProduct3fv(b1, n1, t1));
		if (i%2==0)
			Math::glNormalize3fv(t2, Math::glSubVector3fv(t2, v2, v3));		
		else
			Math::glNormalize3fv(t2, Math::glSubVector3fv(t2, v3, v2));		
		Math::glNormalize3fv(b2, Math::glCrossProduct3fv(b2, n2, t2));	
		if (i%2)
			Math::glNormalize3fv(t3, Math::glSubVector3fv(t3, v3, v1));		
		else
			Math::glNormalize3fv(t3, Math::glSubVector3fv(t3, v1, v3));		
		Math::glNormalize3fv(b3, Math::glCrossProduct3fv(b3, n3, t3));	

	}

	m_lightVector = m_vertex + 3*m_vertexCount;
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		float* n = &m_normals[i];
		float* b = &m_binormal[i];
		float* t = &m_tangent[i];
		float v[3];
		Math::glSubVector3fv(v, m_lightPos, &m_vertex[i]);
		Math::glNormalize3fv(v, Math::glSumVector3fv(v, v, m_eye));
		
		m_lightVector[i+0] = Math::glDotProduct3fv(v, t);
		m_lightVector[i+1] = Math::glDotProduct3fv(v, b);
		m_lightVector[i+2] = Math::glDotProduct3fv(v, n);
		Math::glNormalize3fv(&m_lightVector[i], &m_lightVector[i]);
	}

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount*sizeof(float)*6, m_vertex, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(unsigned short), m_index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

StaticMeshWithVBO::~StaticMeshWithVBO()
{
	delete[] m_vertex;
	delete[] m_index;
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}

void StaticMeshWithVBO::Draw()
{
	glPushMatrix();

	int normalsOffset = m_vertexCount*sizeof(float);
	int textureOffset = m_vertexCount*2*sizeof(float);
	int lightOffset = m_vertexCount*3*sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount*sizeof(float)*6, m_vertex);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, (void*)0);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, (void*)normalsOffset);

	if (m_bumpMap)
	{
		glClientActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_bumpMap);
		glTexCoordPointer(3, GL_FLOAT, 0, (void*)textureOffset);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
	}
	if (m_normalizationCubeMap)
	{
		glClientActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_CUBE_MAP);		
		glTexCoordPointer(3, GL_FLOAT, 0, (void*)lightOffset);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_normalizationCubeMap);
	}/**/
	if (m_decalMap)
	{
		glClientActiveTexture(GL_TEXTURE2);
		glActiveTexture(GL_TEXTURE2);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_decalMap);
		glTexCoordPointer(3, GL_FLOAT, 0, (void*)textureOffset);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
	}
	glEnable(GL_REGISTER_COMBINERS_NV);
	glCombinerParameteriNV(GL_NUM_GENERAL_COMBINERS_NV, 2);
	glCombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, m_lightColor);
	glCombinerParameterfvNV(GL_CONSTANT_COLOR1_NV, m_ambientColor);
	//
	//	c
	//
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_A_NV,
		GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA);
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_B_NV,
		GL_TEXTURE1, GL_EXPAND_NORMAL_NV, GL_BLUE);
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_C_NV,
		GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_ALPHA);
	glCombinerInputNV(GL_COMBINER0_NV, GL_ALPHA, GL_VARIABLE_D_NV,
		GL_TEXTURE1, GL_EXPAND_NORMAL_NV, GL_BLUE);
	glCombinerOutputNV(GL_COMBINER0_NV, GL_ALPHA, 
		GL_DISCARD_NV,
		GL_DISCARD_NV,
		GL_SPARE0_NV,
		GL_SCALE_BY_FOUR_NV,
		GL_NONE, 
		GL_FALSE,
		GL_FALSE, GL_FALSE);
	//
	//	color
	//
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_A_NV, 
		GL_TEXTURE0, GL_EXPAND_NORMAL_NV, GL_RGB);
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_B_NV,
		GL_TEXTURE1, GL_EXPAND_NORMAL_NV, GL_RGB);
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_C_NV,
		GL_ZERO, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
	glCombinerInputNV(GL_COMBINER0_NV, GL_RGB, GL_VARIABLE_D_NV,
		GL_ZERO, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA);
	glCombinerOutputNV(GL_COMBINER0_NV, GL_RGB,
		GL_SPARE0_NV,
		GL_DISCARD_NV,
		GL_DISCARD_NV,
		GL_FALSE,
		GL_FALSE,
		GL_TRUE,
		GL_FALSE, 
		GL_FALSE);
	//
	//	r1
	//
	glCombinerInputNV(GL_COMBINER1_NV, GL_RGB, GL_VARIABLE_A_NV,
		GL_SPARE0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glCombinerInputNV(GL_COMBINER1_NV, GL_RGB, GL_VARIABLE_B_NV,
		GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB);
	glCombinerInputNV(GL_COMBINER1_NV, GL_RGB, GL_VARIABLE_C_NV,
		GL_CONSTANT_COLOR0_NV, GL_SIGNED_NEGATE_NV, GL_RGB);
	glCombinerInputNV(GL_COMBINER1_NV, GL_RGB, GL_VARIABLE_D_NV,
		GL_ZERO, GL_UNSIGNED_INVERT_NV, GL_RGB);
	glCombinerOutputNV(GL_COMBINER1_NV, GL_RGB,
		GL_DISCARD_NV,
		GL_DISCARD_NV,
		GL_SPARE0_NV,
		GL_SCALE_BY_FOUR_NV,
		GL_NONE,
		GL_FALSE,
		GL_FALSE, GL_FALSE);
	//
	//	final
	//
	glFinalCombinerInputNV(GL_VARIABLE_A_NV, GL_SPARE0_NV,
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_B_NV, GL_SPARE0_NV, 
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_C_NV, GL_ZERO,
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_D_NV, GL_TEXTURE2,
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_E_NV, GL_ZERO, 
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_F_NV, GL_ZERO, 
		GL_UNSIGNED_IDENTITY_NV, GL_RGB);
	glFinalCombinerInputNV(GL_VARIABLE_G_NV, GL_ZERO, 
		GL_UNSIGNED_INVERT_NV, GL_ALPHA);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_INDEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glIndexPointer(GL_UNSIGNED_INT, 0, 0);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);/**/

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_REGISTER_COMBINERS_NV);
	glDisable(GL_TEXTURE_SHADER_NV);
	glClientActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_REGISTER_COMBINERS_NV);
	glDisable(GL_TEXTURE_SHADER_NV);
	glClientActiveTexture(GL_TEXTURE2);
	glActiveTexture(GL_TEXTURE2);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_REGISTER_COMBINERS_NV);
	glDisable(GL_TEXTURE_SHADER_NV);
	glPopMatrix();

}

void StaticMeshWithVBO::SetNormalizationMap(GLuint textureId)
{
	m_normalizationCubeMap = textureId;
}

void StaticMeshWithVBO::SetBumpMap(GLuint textureId)
{
	m_bumpMap = textureId;
}

void StaticMeshWithVBO::SetLightColor(const float* color)
{
	memcpy(m_lightColor, color, sizeof(m_lightColor));
}

void StaticMeshWithVBO::SetAmbientColor(const float* color)
{
	memcpy(m_ambientColor, color, sizeof(m_ambientColor));
}

void StaticMeshWithVBO::SetEye(const float* eye)
{
	memcpy(m_eye, eye, sizeof(m_eye));
}

void StaticMeshWithVBO::SetDecalMap(GLuint map)
{
	m_decalMap = map;
}

void StaticMeshWithVBO::SetLightPos(float x, float y, float z)
{
	m_lightPos[0] = x; m_lightPos[1] = y; m_lightPos[2] = z;
	for (int i = 0; i < m_vertexCount; i += 3)
	{
		float* n = &m_normals[i];
		float* b = &m_binormal[i];
		float* t = &m_tangent[i];
		float v[3];
		Math::glSubVector3fv(v, m_lightPos, &m_vertex[i]);
		Math::glNormalize3fv(v, Math::glSumVector3fv(v, v, m_eye));
		
		m_lightVector[i+0] = Math::glDotProduct3fv(v, t);
		m_lightVector[i+1] = Math::glDotProduct3fv(v, b);
		m_lightVector[i+2] = Math::glDotProduct3fv(v, n);
		Math::glNormalize3fv(&m_lightVector[i], &m_lightVector[i]);
	}
}

StaticMeshWithVBO* StaticMeshWithVBO::CreateFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw std::runtime_error(std::string("Scene::CreateStaticMeshWithMultiTextureFromFile: File not found") + filename);
	int vertexCount;
	int faceCount;
	fread(&vertexCount, sizeof(int), 1, f);
	fread(&faceCount, sizeof(int), 1, f);
	//
	//	memory malloc will be only one. for vertex,
	//	besides vertex there also will be data such
	//	as normals texture cooeds and other
	float* vertex = new float[vertexCount*6];
	float* normal = vertex + vertexCount;
	float* texture = normal + vertexCount;
	unsigned short* index = new unsigned short[faceCount];
	fread(vertex, sizeof(float), vertexCount, f);
	fread(normal, sizeof(float), vertexCount, f);
	fread(texture, sizeof(float), vertexCount, f);
	fread(index, sizeof(unsigned short), faceCount, f);
	fclose(f);	
	StaticMeshWithVBO* mesh = new StaticMeshWithVBO(vertexCount, faceCount, vertex, texture, normal, index);
	//m_StaticMeshWithMultiTextureContainer.push_back(mesh);
	return mesh;

}