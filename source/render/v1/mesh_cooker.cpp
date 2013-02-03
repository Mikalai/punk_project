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
		System::Proxy<Virtual::Material> material(new Virtual::Material);
		material->GetCache().m_diffuse_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"snow.jpg");
		material->GetCache().m_diffuse_texture_cache_2 = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"ground.png");
		material->GetCache().m_normal_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"bump.png");
		node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->SetMaterial(material);
		return true;
	}

	bool MeshCooker::Visit(Scene::SkinMeshNode* node)
	{
		System::Proxy<Virtual::SkinGeometry> geom = Virtual::SkinGeometry::find(node->GetStorageName());

		System::Proxy<GPU::OpenGL::SkinMesh> mesh;
		if (geom->IsCacheValid())
			mesh = geom->GetGPUBufferCache();
		else
		{
			mesh.Reset(new GPU::OpenGL::SkinMesh);
			if (!mesh->Cook(geom, m_current_armature))
				throw System::PunkException(L"Can't cook static mesh from static geometry");
			geom->SetGPUBufferCache(mesh);
		}
		node->SetGeometry(geom);
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
		Virtual::StaticGeometry::validate();
		System::Proxy<Virtual::StaticGeometry> geom = Virtual::StaticGeometry::find(node->GetStorageName());	

		System::Proxy<GPU::OpenGL::StaticMesh> mesh;
		if (geom->IsCacheValid())
			mesh = geom->GetGPUBufferCache();
		else
		{
			mesh.Reset(new GPU::OpenGL::StaticMesh);
			if (!mesh->Cook(geom))
				throw System::PunkException(L"Can't cook static mesh for " + geom->GetName());
			geom->SetGPUBufferCache(mesh);
		}
		node->SetGeometry(geom);
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
		Virtual::Material::validate();
		System::Proxy<Virtual::Material> mat = Virtual::Material::find(node->GetName());
		node->SetMaterial(mat);
		mat->GetCache().m_diffuse_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + mat->GetDiffuseMap());
		mat->GetCache().m_normal_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + mat->GetNormalMap());
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