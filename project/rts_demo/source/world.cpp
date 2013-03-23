#include "../../../source/punk_engine.h"
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
	
	House* house = Cast<House*>(m_house_scheme->CreateNewStruture());

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

void World::RemoveGameEntity(GameEntity* entity)
{
	std::vector<GameEntity*>::iterator it = std::find(m_entity.begin(), m_entity.end(), entity);
	m_entity.erase(it);
	m_scene->GetRootNode()->Remove(entity);
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

bool World::CheckCollisitionWithObjects(GameEntity* node)
{
	Scene::Collider collider;
	collider.SetScene(m_scene);
	auto result = collider.Run(node->GetBoundingSphere());

	for (auto item : result.m_nodes)
	{
		if (As<GameEntity*>(item))
			return true;
	}
	return false;
}

const Math::vec3 World::IntersectTerrain(const Math::Line3D& ray)
{
	Math::vec3 result;
	m_observer->GetTerrainView()->IntersectRay(ray, result);
	return result;
}

void World::OnSelectorMove(const Math::Line3D& line)
{
	//Math::Line3D ray;
	//ray.SetOriginDestination(line.GetOrigin(), line.GetOrigin() + line.GetDirection() * 100.0f);
	//Math::vec3 point = IntersectTerrain(ray);

	//House* house = nullptr;
	//for (auto e : m_entity)
	//{
	//	house = As<House*>(e);
	//	if (house)
	//		break;
	//}
	//if (house)
	//	house->SetPosition(point);
}