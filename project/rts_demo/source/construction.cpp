#include "construction.h"
#include "game_entity.h"
#include "world.h"
#include "ibuilder.h"
#include "structure_scheme.h"
#include "structure.h"

void Construction::SetWorld(World* world)
{
	m_world = world;
}

void Construction::SetFinishAction(IAction* action)
{
	m_on_finish = action;
}

void Construction::SetBudget(int budget)
{
	m_budget = budget;
};

/**
*	Scheme should not be deleted in the class. 
*/
void Construction::SetScheme(StructureScheme* scheme)
{
	m_scheme = scheme;

	m_game_entity = new GameEntity;
	m_transform_node = new Scene::TransformNode;

	for (auto geom : m_scheme->GetConstructionGeometry())
	{
		Scene::StaticMeshNode* mesh_node = new Scene::StaticMeshNode;
		mesh_node->SetGeometry(geom);
		m_transform_node->Add(mesh_node);
	}

	Scene::MaterialNode* material_node = new Scene::MaterialNode;
	material_node->SetMaterial(m_scheme->GetMaterial());
	material_node->Add(m_transform_node);
	m_game_entity->Add(m_material_node);
}

void Construction::StartBuilding()
{
	m_jobs_elements_left = m_scheme->GetTotalJobsElements();
	m_can_be_deleted = false;
}

void Construction::SetLocation(const Math::vec3& value)
{
	m_location = value;
	Math::mat4 m = Math::mat4::CreateFromPoistionAndDirection(m_location, m_direction);
	m_transform_node->SetLocalMatrix(m);
}

void Construction::SetDirection(const Math::vec3& value)
{}

bool Construction::NeedRemove() 
{
	return false;
}

bool Construction::NeedDelete() 
{
	return m_can_be_deleted;
}

void Construction::Update(double time, double dt) 
{
	if (m_jobs_elements_left <= 0.0f)
	{
		Structure* s = ToStructure();
		m_scheme->Add(s);
		m_world->AddGameEntity(s->ToGameEntity());
		m_world->RemoveGameEntity(ToGameEntity());
		m_can_be_deleted = true;
	}
	return;
}

void Construction::AdvanceConstruction(float steps)
{
	m_jobs_elements_left -= steps;
}

void Construction::AddWorker(IBuilder* worker)
{
	m_workers.push_back(worker);
}

void Construction::RemoveWorker(IBuilder* worker)
{
	m_workers.erase(m_workers.begin(), std::remove(m_workers.begin(), m_workers.end(), worker));
}

Structure* Construction::ToStructure()
{
	Structure* s = m_scheme->CreateNewStruture();
	s->SetPosition(m_location);	
	return s;
}