#include "bounding_volume_updater.h"
#include "../virtual/data/data.h"
#include "../virtual/skinning/skinning.h"
#include "../virtual/animation/anim.h"

#include "scene_graph.h"
#include "../opengl/renderable/renderable_data.h"

namespace Scene
{

	bool BoundingVolumeUpdater::Visit(Scene::CameraNode* node)
	{
		m_states.Push();

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				child->Apply(this);
		}
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::StaticMeshNode* node)
	{		
		System::Proxy<OpenGL::StaticMesh> mesh = OpenGL::StaticMeshManager::Instance()->Load(node->GetStorageName());	
		node->SetBoundingSphere(m_states.CurrentState()->Get().m_local * mesh->GetBoundingSphere());
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::SkinMeshNode* node)
	{				
		System::Proxy<OpenGL::SkinMesh> mesh = OpenGL::SkinMeshManager::Instance()->Load(node->GetStorageName());	
		node->SetBoundingSphere(m_states.CurrentState()->Get().m_local * mesh->GetBoundingSphere());
		return true;
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::ArmatureNode* node)
	{				
		m_states.Push();	
		System::Proxy<Virtual::Armature> armature = Virtual::ArmatureManager::Instance()->Load(node->GetStorageName());

		m_states.CurrentState()->Get().m_armature = armature;
		m_states.CurrentState()->Get().m_armature_world = m_states.CurrentState()->Get().m_local;

		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::BoneNode* node)
	{
		m_states.Push();
		System::Proxy<Virtual::Armature> armature = m_states.CurrentState()->Get().m_armature;
		if (!armature.IsValid())
			return (out_error() << "It is impossible to process bone node without valid armature" << std::endl, false);

		Virtual::Bone* bone = armature->GetBoneByName(node->GetName());
		if (!bone)
			return (out_error() << "Bone " << node->GetName() << std::endl, false);

		m_states.CurrentState()->Get().m_local *= bone->GetAnimatedGlobalMatrix();

		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::LightNode* node)
	{
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::MaterialNode* node)
	{
		m_states.Push();		
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::Node* node)
	{
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		return true;
	}
	bool BoundingVolumeUpdater::Visit(Scene::TransformNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local *= node->GetLocalMatrix();
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::LocationIndoorNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local *= node->GetLocalMatrix();
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::TerrainNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local.Identity();			
		bool was = false;
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
				if (!was)
				{
					node->SetBoundingSphere(child->GetBoundingSphere());
					was = true;
				}
				else
				{
					node->SetBoundingSphere(node->GetBoundingSphere() + child->GetBoundingSphere());
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool BoundingVolumeUpdater::Visit(Scene::PortalNode* node)
	{
		return true;
	}

	void BoundingVolumeUpdater::Update()
	{
		if (m_scene.IsValid())
			m_scene->GetRootNode()->Apply(this);
	}

	void BoundingVolumeUpdater::SetScene(System::Proxy<Scene::SceneGraph> scene)
	{
		m_scene = scene;
	}


}