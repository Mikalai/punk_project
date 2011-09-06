#ifdef _WIN32
#include <windows.h>
#include <commctrl.h>
#endif

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include "Scene.h"
#include "Driver.h"

Scene::Scene(Driver* driver) : m_driver(driver) {}

Scene::~Scene()
{
		//
	//	delete all loaded meshes
	//
	for (unsigned i = 0; i < m_meshContainer.size(); i++)
	{
		DELETE_POINTER(m_meshContainer[i]);
	}
	m_meshContainer.clear();

	//
	//	delete all loaded images
	//
/*	if (!m_imageContainer.empty())
	{
		for (unsigned i = 0; i < m_imageContainer.size(); i++)
		{
			DELETE_POINTER(m_imageContainer[i]);
		}
		m_imageContainer.clear();
	}
*/
	//
	//	delete all created textures
	//
	/*for (unsigned i = 0; i < m_textureContainer.size(); i++)
	{
		DELETE_POINTER(m_textureContainer[i]);
	}
	m_textureContainer.clear();*/
}

ILightManager* Scene::GetLightManager()
{
	return &m_lightManager;
}

IFog* Scene::GetFog()
{
	return &m_fog;
}

ICamera* Scene::GetCamera()
{
	return &m_camera;
}

IMesh* Scene::CreateSimpleMesh()
{
	TMesh* mesh = new TMesh();
	m_meshContainer.push_back(mesh);
	return mesh;
}

IMesh* Scene::CreateTexturedAndLitMesh()
{
	return 0;
}

IMesh* Scene::CreateTexturedLitAndBumpMappedMesh()
{
	return 0;
}

IImage* Scene::CreateImage()
{
	return 0;
}

ITexture2D* Scene::CreateTexture2D()
{
	TTexture2D* texture = new TTexture2D();
	//m_textureContainer.push_back(texture);
	return texture;
}

bool Scene::SetLight(unsigned int id, float dirx, float diry, float dirz, float r, float g, float b)
{
	return false;
}

IStaticMesh* Scene::CreateStaticMeshFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw Exception(PunkString("Scene::CreateStaticMeshFromFile: File not found") + filename);
	int vertexCount;
	int faceCount;
	fread(&vertexCount, sizeof(int), 1, f);
	fread(&faceCount, sizeof(int), 1, f);
	float* vertex = new float[vertexCount];
	float* normal = new float[vertexCount];
	float* texture = new float[vertexCount];
	unsigned short* index = new unsigned short[faceCount];
	fread(vertex, sizeof(float), vertexCount, f);
	fread(normal, sizeof(float), vertexCount, f);
	fread(texture, sizeof(float), vertexCount, f);
	fread(index, sizeof(unsigned short), faceCount, f);

	StaticMesh* mesh = new StaticMesh(vertexCount, faceCount, vertex, texture, normal, index);
	//m_staticMeshContainer.push_back(mesh);
	return mesh;
}

IStaticModel* Scene::CreateStaticModel(IStaticMesh *mesh)
{
	StaticModel* model = new StaticModel(dynamic_cast<StaticMesh*>(mesh));
	m_staticModelContainer.push_back(model);
	return model;
}
#ifdef _WIN32
#include <windows.h>
#include <commctrl.h>
#endif

#ifdef _WIN64
#include <windows.h>
#endif

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\wglext.h>
#include "Scene.h"
#include "Driver.h"

Scene::Scene(TDriver* driver) : m_driver(driver) {}

Scene::~Scene()
{
		//
	//	delete all loaded meshes
	//
	for (unsigned i = 0; i < m_meshContainer.size(); i++)
	{
		DELETE_POINTER(m_meshContainer[i]);
	}
	m_meshContainer.clear();

	//
	//	delete all loaded images
	//
/*	if (!m_imageContainer.empty())
	{
		for (unsigned i = 0; i < m_imageContainer.size(); i++)
		{
			DELETE_POINTER(m_imageContainer[i]);
		}
		m_imageContainer.clear();
	}
*/
	//
	//	delete all created textures
	//
	/*for (unsigned i = 0; i < m_textureContainer.size(); i++)
	{
		DELETE_POINTER(m_textureContainer[i]);
	}
	m_textureContainer.clear();*/
}

ILightManager* Scene::GetLightManager()
{
	return &m_lightManager;
}

IFog* Scene::GetFog()
{
	return &m_fog;
}

ICamera* Scene::GetCamera()
{
	return &m_camera;
}

IMesh* Scene::CreateSimpleMesh()
{
	TMesh* mesh = new TMesh();
	m_meshContainer.push_back(mesh);
	return mesh;
}

IMesh* Scene::CreateTexturedAndLitMesh()
{
	return 0;
}

IMesh* Scene::CreateTexturedLitAndBumpMappedMesh()
{
	return 0;
}

IImage* Scene::CreateImage()
{
	return 0;
}

ITexture2D* Scene::CreateTexture2D()
{
	TTexture2D* texture = new TTexture2D();
	//m_textureContainer.push_back(texture);
	return texture;
}

bool Scene::SetLight(unsigned int id, float dirx, float diry, float dirz, float r, float g, float b)
{
	return false;
}

IStaticMesh* Scene::CreateStaticMeshFromFile(const char *filename)
{
	FILE* f = 0;
	fopen_s(&f, filename, "rb");
	if (f == 0)
		throw Exception(PunkString("Scene::CreateStaticMeshFromFile: File not found") + filename);
	int vertexCount;
	int faceCount;
	fread(&vertexCount, sizeof(int), 1, f);
	fread(&faceCount, sizeof(int), 1, f);
	float* vertex = new float[vertexCount];
	float* normal = new float[vertexCount];
	float* texture = new float[vertexCount];
	unsigned short* index = new unsigned short[faceCount];
	fread(vertex, sizeof(float), vertexCount, f);
	fread(normal, sizeof(float), vertexCount, f);
	fread(texture, sizeof(float), vertexCount, f);
	fread(index, sizeof(unsigned short), faceCount, f);
	
	StaticMesh* mesh = new StaticMesh(vertexCount, faceCount, vertex, texture, normal, index);
	//m_staticMeshContainer.push_back(mesh);
	return mesh;
}

IStaticModel* Scene::CreateStaticModel(IStaticMesh *mesh)
{
	StaticModel* model = new StaticModel(dynamic_cast<StaticMesh*>(mesh));
	m_staticModelContainer.push_back(model);
	return model;
}