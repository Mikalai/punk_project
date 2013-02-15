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
		Virtual::Material* material(new Virtual::Material);
		material->GetCache().m_diffuse_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"snow.jpg");
		material->GetCache().m_diffuse_texture_cache_2 = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"ground.png");
		material->GetCache().m_normal_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + L"bump.png");
		node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->SetMaterial(material);
		return true;
	}

	bool MeshCooker::Visit(Scene::SkinMeshNode* node)
	{
		if (!node->HasGeometry())
		{
			Virtual::SkinGeometry::validate();		
			Virtual::SkinGeometry* geom = Virtual::SkinGeometry::find(node->GetStorageName());

			GPU::OpenGL::SkinMesh* mesh = nullptr;
			if (geom->IsCacheValid())
				mesh = Cast<GPU::OpenGL::SkinMesh*>(geom->GetGPUBufferCache());
			else
			{
				mesh = new GPU::OpenGL::SkinMesh;
				try
				{
					mesh->Cook(geom, m_current_armature);
					geom->SetGPUBufferCache(mesh);
				}			
				catch(...)
				{
					delete mesh;
					throw;
				}
			}
			node->SetGeometry(geom);
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::ArmatureNode* node)
	{		
		Virtual::Armature::validate();
		m_current_armature = Virtual::Armature::find(node->GetStorageName());
		m_current_armature->UpdateHierarchy();
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
				if (!child->Apply(this))
					return false;
		}		
		return true;
	}

	bool MeshCooker::Visit(Scene::StaticMeshNode* node)
	{				
		if (!node->HasGeometry())
		{
			Virtual::StaticGeometry::validate();
			Virtual::StaticGeometry* geom = Virtual::StaticGeometry::find(node->GetStorageName());	

			GPU::OpenGL::StaticMesh* mesh = 0;
			if (geom->IsGPUCacheValid())
				mesh = Cast<GPU::OpenGL::StaticMesh*>(geom->GetGPUBufferCache());
			else
			{
				mesh = new GPU::OpenGL::StaticMesh;
				try
				{
					mesh->Cook(geom);
					geom->SetGPUBufferCache(mesh);				
				}
				catch (...)
				{
					delete mesh;
					throw;
				}			
			}
			node->SetGeometry(geom);
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::LightNode* node)
	{
		m_light_set.push_back(node->GetLight());
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::MaterialNode* node)
	{
		Virtual::Material::validate();
		Virtual::Material* mat = Virtual::Material::find(node->GetName());
		node->SetMaterial(mat);
		mat->GetCache().m_diffuse_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + mat->GetDiffuseMap());
		mat->GetCache().m_normal_texture_cache = GPU::OpenGL::Texture2D::CreateFromFile(System::Environment::Instance()->GetTextureFolder() + mat->GetNormalMap());
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::Node* node)
	{
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::TransformNode* node)
	{
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::LocationIndoorNode* node)
	{
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (!child->Apply(this))
				return false;
		}
		return true;
	}

	bool MeshCooker::Visit(Scene::BoneNode* node)
	{		
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
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