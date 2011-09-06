#pragma once

#include "Texture2D.h"
#include "StaticMesh.h"
#include "Texture2D.h"
#include "../PunkEngine/common/IStaticModel.h"

class StaticModel : public IStaticModel
{	
	unsigned m_envMapID;
	int m_maxTextures;
	float m_transform[16];
	unsigned* m_textures;
	StaticMesh* m_mesh;
public:
	StaticModel(StaticMesh* mesh);
	virtual void Draw();
	virtual void SetTransform(float* transform);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(unsigned id, unsigned texture);
	virtual void SetEnvironmentMap(unsigned id, unsigned texture);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();
};#pragma once

#include "Texture2D.h"
#include "StaticMesh.h"
#include "Texture2D.h"
#include "../PunkEngine/common/IStaticModel.h"

class StaticModel : public IStaticModel
{	
	unsigned m_envMapID;
	int m_maxTextures;
	float m_transform[16];
	unsigned* m_textures;
	StaticMesh* m_mesh;
public:
	StaticModel(StaticMesh* mesh);
	virtual void Draw();
	virtual void SetTransform(float* transform);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(unsigned id, unsigned texture);
	virtual void SetEnvironmentMap(unsigned id, unsigned texture);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();
};