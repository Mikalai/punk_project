#pragma once

#include "../PunkEngine/common/IScene.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "Image.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Fog.h"
#include "LightManager.h"
#include "StaticModel.h"

class Driver;

class Scene : public IScene
{
	Driver* m_driver;	
	std::vector<TMesh*> m_meshContainer;
	std::vector<StaticMesh*> m_staticMeshContainer;
	std::vector<StaticModel*> m_staticModelContainer;
	TCamera m_camera;

	TLightManager m_lightManager;
	Fog m_fog;
public:
	Scene(Driver* driver);
	virtual ~Scene();
	virtual IMesh* CreateSimpleMesh();
	virtual IMesh* CreateTexturedAndLitMesh();
	virtual IMesh* CreateTexturedLitAndBumpMappedMesh();
	virtual IStaticMesh* CreateStaticMeshFromFile(const char* filename);
	virtual IStaticModel* CreateStaticModel(IStaticMesh* mesh);
	virtual ICamera* GetCamera();
	virtual ILightManager* GetLightManager();
	virtual IImage* CreateImage();
	virtual ITexture2D* CreateTexture2D();
	virtual IFog* GetFog();
	virtual bool SetLight(unsigned id, float dirx, float diry, float dirz, float r, float g, float b) ;
};#pragma once

#include "../PunkEngine/common/IScene.h"
#include "Mesh.h"
#include "StaticMesh.h"
#include "Image.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Fog.h"
#include "LightManager.h"
#include "StaticModel.h"

class TDriver;

class Scene : public IScene
{
	TDriver* m_driver;	
	std::vector<TMesh*> m_meshContainer;
	std::vector<StaticMesh*> m_staticMeshContainer;
	std::vector<StaticModel*> m_staticModelContainer;
	TCamera m_camera;

	TLightManager m_lightManager;
	TFog m_fog;
public:
	Scene(TDriver* driver);
	virtual ~Scene();
	virtual IMesh* CreateSimpleMesh();
	virtual IMesh* CreateTexturedAndLitMesh();
	virtual IMesh* CreateTexturedLitAndBumpMappedMesh();
	virtual IStaticMesh* CreateStaticMeshFromFile(const char* filename);
	virtual IStaticModel* CreateStaticModel(IStaticMesh* mesh);
	virtual ICamera* GetCamera();
	virtual ILightManager* GetLightManager();
	virtual IImage* CreateImage();
	virtual ITexture2D* CreateTexture2D();
	virtual IFog* GetFog();
	virtual bool SetLight(unsigned id, float dirx, float diry, float dirz, float r, float g, float b) ;
};