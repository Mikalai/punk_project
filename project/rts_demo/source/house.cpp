#include "house.h"
#include "game_entity.h"
#include "house_scheme.h"

House::House(StructureScheme* scheme)
	: Building(scheme)
{
	m_node = new GameEntity;
	m_transform_node = new Scene::TransformNode;

	for (auto mesh : m_scheme->GetFinalGeometry())
	{
		Scene::StaticMeshNode* mesh_node = new Scene::StaticMeshNode;
		mesh_node->SetGeometry(mesh);
		m_transform_node->Add(mesh_node);
	}

	Scene::MaterialNode* material_node = new Scene::MaterialNode;
	material_node->SetMaterial(m_scheme->GetMaterial());

	material_node->Add(m_transform_node);
	m_node->Add(material_node);
}

void House::Update(double time, double dt) 
{
}

bool House::NeedRemove() 
{
	return false;
}

bool House::NeedDelete() 
{
	return false;
}
