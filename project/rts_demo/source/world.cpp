#include "world.h"
#include "game_entity.h"
#include "dynamic.h"
#include "house_scheme.h"
#include "house.h"

World::World(Punk::Application* app)
{
	m_time = 0;
	m_app = app;
	m_scene = new Scene::SceneGraph;
	
	CreateCamera();
	CreateTerrain();
	CreateRender();
	CreateBoundingVolumeUpdater();

	m_house_scheme = new HouseScheme;
	
	House* house = new House(m_house_scheme);

	AddGameEntity(house->ToGameEntity());
}

void World::CreateCamera()
{	
	m_camera = new Virtual::Camera();
	m_scene->SetActiveCamera(m_camera);
}

void World::CreateTerrain()
{
	m_app->GetTerrainManager()->Manage(L"test_map");
	m_observer = m_app->GetTerrainManager()->CreateTerrainObserver(m_camera->GetPosition());
	m_terrain_node = new Scene::TerrainNode();
	m_terrain_node->SetTerrainObserver(m_observer);
	m_scene->GetRootNode()->Add(m_terrain_node);
}

void World::CreateRender()
{
	m_render = new Render::SimpleRender(m_app->GetVideoDriver());
	m_render->SetScene(m_scene);
}

void World::CreateBoundingVolumeUpdater()
{
	m_updater = new Scene::BoundingVolumeUpdater;
	m_updater->SetScene(m_scene);
}

void World::AddGameEntity(GameEntity* entity)
{
	m_entity.push_back(entity);
	m_scene->GetRootNode()->Add(entity);
}

void World::Draw()
{
	m_updater->Update();
	m_render->Render();
}

void World::Update(double dt)
{
	m_time += dt;

	for (std::vector<GameEntity*>::iterator it = m_entity.begin(); it != m_entity.end(); ++it)
	{
		IDynamic* dynamic = As<IDynamic*>(*it);
		if (dynamic)
		{
			dynamic->Update(m_time, dt);
			if (dynamic->NeedDelete())
			{
				delete *it;
				*it = nullptr;
			}
		}
	}
	m_entity.erase(m_entity.begin(), std::remove(m_entity.begin(), m_entity.end(), nullptr));
}