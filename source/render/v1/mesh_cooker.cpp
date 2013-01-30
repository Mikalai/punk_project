#include "mesh_cooker.h"
#include "../../gpu/module.h"
#include "../../virtual/module.h"
#include "../../scene/module.h"

namespace Render
{
	MeshCooker::MeshCooker()
	{
		//m_light_set.Reset(new Virtual::LightSet);
	}

	bool MeshCooker::Visit(Scene::CameraNode* node)
	{
		return true;
	}

	bool MeshCooker::Visit(Scene::TerrainNode* node)
	{
		return true;
	}

	bool MeshCooker::Visit(Scene::SkinMeshNode* node)
	{
		System::Proxy<Virtual::SkinGeometry> geom = Virtual::SkinGeometryManager::Instance()->Load(node->GetStorageName());

		System::Proxy<GPU::OpenGL::SkinMesh> mesh = System::GetFactory()->Create(geom->GetStorageName(), System::ObjectType::SKIN_MESH);

		if (!mesh->Cook(geom, m_current_armature))
			return (out_error() << "Can't cook static mesh from static geometry" << std::endl, false);
		return true;
	}

	bool MeshCooker::Visit(Scene::ArmatureNode* node)
	{		
		m_current_armature = Virtual::Armature::find(node->GetStorageName());
		m_current_armature->UpdateHierarchy();
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		m_current_armature.Release();
		return true;
	}

	bool MeshCooker::Visit(Scene::StaticMeshNode* node)
	{				
		System::Proxy<Virtual::StaticGeometry> geom = Virtual::StaticGeometryManager::Instance()->Load(node->GetStorageName());	

		System::Proxy<GPU::OpenGL::StaticMesh> mesh = System::GetFactory()->Create(geom->GetStorageName(), System::ObjectType::STATIC_MESH);

		if (!mesh->Cook(geom))
			return (out_error() << "Can't cook static mesh from static geometry" << std::endl, false);
		return true;
	}

	bool MeshCooker::Visit(Scene::LightNode* node)
	{
		m_light_set.push_back(node->GetLight());
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::MaterialNode* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::Node* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::TransformNode* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::LocationIndoorNode* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::BoneNode* node)
	{		
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::PortalNode* node)
	{		
		return true;
	}
}