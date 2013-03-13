#ifndef _H_PUNK_RTS_DEMO_WORLD
#define _H_PUNK_RTS_DEMO_WORLD

#include "../../../source/punk_engine.h"

class GameEntity;
class HouseScheme;
class House;

class World
{
public:	
	
	World(Punk::Application* app);
	void Update(double dt);
	void Draw();
	void AddGameEntity(GameEntity* entity);
	Virtual::Camera* GetCamera() { return m_camera; }
	Virtual::TerrainObserver* GetTerrainObserver() { return m_observer; }

private:
	Punk::Application* m_app;
	Scene::SceneGraph* m_scene;
	Virtual::Camera* m_camera;
	Virtual::TerrainObserver* m_observer;
	Scene::TextureViewNode* m_node;
	Scene::TerrainNode* m_terrain_node;
	Virtual::TerrainManager* m_terrain_manager;
	Render::SimpleRender* m_render;
	Scene::BoundingVolumeUpdater* m_updater;
	double m_time;
	std::vector<GameEntity*> m_entity;

	void CreateCamera();
	void CreateTerrain();
	void CreateRender();
	void CreateBoundingVolumeUpdater();

	HouseScheme* m_house_scheme;
};

#endif	//	_H_PUNK_RTS_DEMO_WORLD