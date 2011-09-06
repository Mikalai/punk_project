#pragma once

#include "../Util/Image.h"

class __declspec(dllexport) Terrain
{
	float m_zoom[3];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned* m_index;
	unsigned m_envMapID;
	int m_maxTextures;
	float m_transform[16];
	unsigned* m_textures;
public:
	Terrain();
	virtual ~Terrain();
	void Draw();
	void Update(float delta);
	void SetZoom(float zoom[]);
	void GenerateFromHeightMap(const Image* image);
	virtual void SetTransform(float* transform);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(unsigned id, unsigned texture);
	virtual void SetEnvironmentMap(unsigned id, unsigned texture);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();
	void InternalDraw_v3();
};#pragma once

#include "../Util/Image.h"

class __declspec(dllexport) Terrain
{
	float m_zoom[3];
	int m_vertexCount;	
	int m_indexCount;
	float* m_vertex;
	float* m_texture;
	float* m_normals;
	unsigned* m_index;
	unsigned m_envMapID;
	int m_maxTextures;
	float m_transform[16];
	unsigned* m_textures;
public:
	Terrain();
	virtual ~Terrain();
	void Draw();
	void Update(float delta);
	void SetZoom(float zoom[]);
	void GenerateFromHeightMap(const Image* image);
	virtual void SetTransform(float* transform);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(unsigned id, unsigned texture);
	virtual void SetEnvironmentMap(unsigned id, unsigned texture);
private:
	void InternalDraw_v1();
	void InternalDraw_v2();
	void InternalDraw_v3();
};