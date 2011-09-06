#ifndef _MESH
#define _MESH

#include "../PunkEngine/PunkEngine.h"
#include <gl\gl.h>
#include <gl\glext.h>
#include <gl\glu.h>
#include "../Util/PunkString.h"

#include "Material.h"
#include "Texture2D.h"

class TMesh : public IMesh
{
public:
	virtual ~TMesh();
	virtual bool LoadMesh(const Char* filename);
	virtual bool Render();
	virtual bool SetWorldTransform(void*);
	virtual bool LoadPunkMesh_v_0_1(const Char* filename);
	virtual bool AttachChild(TMesh* mesh);
	virtual bool DetachChild(TMesh* mesh);
	virtual int GetChildrenCount() const;
	virtual TMesh** GetChildren();
	virtual const PunkString& GetName() const;	
	virtual void UseBlending(bool use);
	virtual void ApplyTexture(ITexture2D* texture);
	virtual int GetVertexCount() const;
	virtual void* GetVertex();
	virtual int GetTrianglesCount() const;
	virtual void* GetTriangles();
private:
	typedef float VertexPosition[3];
	typedef float VertexNormal[3];
	typedef float FaceNormal[3];
	typedef float VertexTexcoord[3];
	typedef int Face[3];

	struct MeshData
	{
		int m_vertexCount;
		int m_faceCount;
		int m_normalsCount;
		VertexPosition* m_vertexPosition;
		VertexNormal* m_vertexNormal;
		FaceNormal* m_faceNormal;
		VertexTexcoord* m_vertexTexcoord;
		Face* m_face;

		MeshData();
		~MeshData();
	};

	friend class Scene;
	TMesh();
	TMesh** m_child;
	TMesh* m_parent;
	int m_childCount;
	PunkString m_name;
	MeshData m_data;
	int m_type;

	TMaterial m_material;

	bool m_useBlending;

	TTexture2D* m_texture;

	float m_transform[16];
};

#endif#ifndef _MESH
#define _MESH

#include "../PunkEngine/PunkEngine.h"
#include <gl\gl.h>
#include <gl\glext.h>
#include <gl\glu.h>
#include "../Util/PunkString.h"

#include "Material.h"
#include "Texture2D.h"

class TMesh : public IMesh
{
public:
	virtual ~TMesh();
	virtual bool LoadMesh(const Char* filename);
	virtual bool Render();
	virtual bool SetWorldTransform(void*);
	virtual bool LoadPunkMesh_v_0_1(const Char* filename);
	virtual bool AttachChild(TMesh* mesh);
	virtual bool DetachChild(TMesh* mesh);
	virtual int GetChildrenCount() const;
	virtual TMesh** GetChildren();
	virtual const PunkString& GetName() const;	
	virtual void UseBlending(bool use);
	virtual void ApplyTexture(ITexture2D* texture);
	virtual int GetVertexCount() const;
	virtual void* GetVertex();
	virtual int GetTrianglesCount() const;
	virtual void* GetTriangles();
private:
	typedef float VertexPosition[3];
	typedef float VertexNormal[3];
	typedef float FaceNormal[3];
	typedef float VertexTexcoord[3];
	typedef int Face[3];

	struct MeshData
	{
		int m_vertexCount;
		int m_faceCount;
		int m_normalsCount;
		VertexPosition* m_vertexPosition;
		VertexNormal* m_vertexNormal;
		FaceNormal* m_faceNormal;
		VertexTexcoord* m_vertexTexcoord;
		Face* m_face;

		MeshData();
		~MeshData();
	};

	friend class Scene;
	TMesh();
	TMesh** m_child;
	TMesh* m_parent;
	int m_childCount;
	PunkString m_name;
	MeshData m_data;
	int m_type;

	TMaterial m_material;

	bool m_useBlending;

	TTexture2D* m_texture;

	float m_transform[16];
};

#endif