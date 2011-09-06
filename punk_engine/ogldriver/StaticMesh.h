#pragma once

#include "../PunkEngine/common/IStaticMesh.h"

class StaticMesh : public IStaticMesh
{
public:
	StaticMesh(int vCount, int fCount, float* v, float* t, float* n, unsigned short* i);
	virtual ~StaticMesh();
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned short* m_index;
	virtual void Draw();
};