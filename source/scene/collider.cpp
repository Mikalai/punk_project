#include "../virtual/module.h"
#include "../gpu/module.h"
#include "module.h"
#include "collider.h"

namespace Scene
{

	Collider::Collider()
		: m_scene(nullptr)
	{}

	bool Collider::Visit(Scene::CameraNode* node)
	{
		m_states.Push();

		for (auto o : *node)
		{
			Node* child = As<Node*>(o);
			if (child)
				child->Apply(this);
		}
		return true;
	}

	bool Collider::Visit(Scene::StaticMeshNode* node)
	{
		{
			GPU::StaticMesh* mesh = NULL;// dynamic_cast<GPU::OpenGL::StaticMesh*>(node->GetStaticGeometry()->GetGPUBufferCache());
			if (mesh)
			{
				node->SetBoundingSphere(m_states.CurrentState()->Get().m_local * mesh->GetBoundingSphere());
				return true;
			}
			Math::Sphere s(Math::vec3(0,0,0), 1);
			node->SetBoundingSphere(m_states.CurrentState()->Get().m_local * Math::BoundingSphere(s));

			if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
			{
				m_result.m_nodes.push_back(node);
			}
		}
		return true;
	}

	bool Collider::Visit(Scene::SkinMeshNode* node)
	{
		GPU::SkinMesh* mesh = nullptr;	// dynamic_cast<GPU::OpenGL::SkinMesh*>(node->GetSkinGeometry()->GetGPUBufferCache());
		node->SetBoundingSphere(m_states.CurrentState()->Get().m_local * mesh->GetBoundingSphere());
		if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
		{
			m_result.m_nodes.push_back(node);
		}
		return true;
	}

	bool Collider::Visit(Scene::ArmatureNode* node)
	{
		m_states.Push();
		Virtual::Armature* armature = Virtual::Armature::find(node->GetStorageName());

		m_states.CurrentState()->Get().m_armature = armature;
		m_states.CurrentState()->Get().m_armature_world = m_states.CurrentState()->Get().m_local;

		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

				if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
				{
					m_result.m_nodes.push_back(node);
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool Collider::Visit(Scene::BoneNode* node)
	{
		m_states.Push();
		Virtual::Armature* armature = m_states.CurrentState()->Get().m_armature;
		if (!armature)
			throw System::PunkInvalidArgumentException(L"It is impossible to process bone node without valid armature");

		Virtual::Bone* bone = armature->GetBoneByName(node->GetName());
		if (!bone)
			return (out_error() << "Bone " << node->GetName() << std::endl, false);

		m_states.CurrentState()->Get().m_local *= bone->GetAnimatedGlobalMatrix();

		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

				if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
				{
					m_result.m_nodes.push_back(node);
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool Collider::Visit(Scene::LightNode* node)
	{
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

	bool Collider::Visit(Scene::MaterialNode* node)
	{
		m_states.Push();
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

	bool Collider::Visit(Scene::Node* node)
	{
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

				if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
				{
					m_result.m_nodes.push_back(node);
				}
			}

		}
		return true;
	}
	bool Collider::Visit(Scene::TransformNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local *= node->GetLocalMatrix();
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

				if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
				{
					m_result.m_nodes.push_back(node);
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool Collider::Visit(Scene::LocationIndoorNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local *= node->GetLocalMatrix();
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

				if (Math::CrossSphereSphere(m_current_sphere, node->GetBoundingSphere()))
				{
					m_result.m_nodes.push_back(node);
				}
			}

		}
		m_states.Pop();
		return true;
	}

	bool Collider::Visit(Scene::TerrainNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->Get().m_local.Identity();
		bool was = false;
		for (auto o : *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
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

    bool Collider::Visit(Scene::PortalNode*)
	{
		return true;
	}

	const Collider::CollisionResult Collider::Run(const Math::BoundingSphere& sphere)
	{
		m_current_sphere = sphere;
		if (m_scene)
			m_scene->GetRootNode()->Apply(this);
		return m_result;
	}

	void Collider::SetScene(Scene::SceneGraph* scene)
	{
		m_scene = scene;
	}


}
