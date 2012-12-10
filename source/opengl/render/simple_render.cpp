#include "simple_render.h"
#include "../driver.h"
#include "../../virtual/data/data.h"
#include "../renderable/renderable_data.h"
#include "../../scene/scene_graph.h"
#include "../render_context/render_contexts.h"
#include "../textures/textures.h"
#include "render_target_back_buffer.h"

namespace OpenGL
{
	MeshCooker::MeshCooker()
	{
		m_light_set.Reset(new Virtual::LightSet);
	}

	bool MeshCooker::Visit(Scene::CameraNode* node)
	{
		return true;
	}

	bool MeshCooker::Visit(Scene::GeometryNode* node)
	{		
		if (node->GetGeometry()->GetType() != System::ObjectType::STATIC_GEOMETRY)
			return true;
		System::Proxy<Virtual::StaticGeometry> geom = node->GetGeometry();	
		
		System::Proxy<StaticMesh> mesh = System::GetFactory()->Create(geom->GetStorageName(), System::ObjectType::STATIC_MESH);

		if (!mesh->Cook(geom))
			return (out_error() << "Can't cook static mesh from static geometry" << std::endl, false);
		return true;
	}

	bool MeshCooker::Visit(Scene::LightNode* node)
	{
		m_light_set->Add(node->GetLight());
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

	bool MeshCooker::Visit(Scene::PortalNode* node)
	{		
		return true;
	}

	bool SimpleRender::Visit(Scene::CameraNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->m_camera = node->GetCamera();
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				child->Apply(this);
		}
		return true;
	}

	bool SimpleRender::Visit(Scene::GeometryNode* node)
	{		
		System::Proxy<StaticMesh> mesh = StaticMeshManager::Instance()->Load(node->GetGeometry()->GetStorageName());		
		m_states.CurrentState()->m_tc->Bind();
		m_states.CurrentState()->m_render_policy->Begin();
		m_states.CurrentState()->m_render_policy->BindParameters(m_states.CurrentState());		
		mesh->Bind(m_states.CurrentState()->m_render_policy->GetRequiredAttributesSet());
		mesh->Render();
		mesh->Unbind();		
		m_states.CurrentState()->m_render_policy->End();		
		m_states.CurrentState()->m_tc->Unbind();
		return true;
	}

	bool SimpleRender::Visit(Scene::LightNode* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					return false;
		}
		return true;
	}

	bool SimpleRender::Visit(Scene::MaterialNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->m_current_material = Virtual::MaterialManager::Instance()->Load(node->GetStorageName());
		m_states.CurrentState()->m_tc = m_tc;
		m_states.CurrentState()->m_tc->SetTexture(0, Texture2DManager::Instance()->Load(m_states.CurrentState()->m_current_material->GetDiffuseMap()));
		m_states.CurrentState()->m_tc->SetTexture(1, Texture2DManager::Instance()->Load(m_states.CurrentState()->m_current_material->GetNormalMap()));
		m_states.CurrentState()->m_diffuse_slot = 0;
		m_states.CurrentState()->m_normal_slot = 1;
		m_states.CurrentState()->m_render_policy = m_context;
		//m_states.CurrentState()->m_render_policy->Init();
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					break;
		}
		m_states.Pop();
		return true;
	}

	bool SimpleRender::Visit(Scene::Node* node)
	{
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					break;
		}
		return true;
	}
	bool SimpleRender::Visit(Scene::TransformNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->m_local *= node->GetLocalMatrix();
		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					break;
		}
		m_states.Pop();
		return true;
	}

	bool SimpleRender::Visit(Scene::LocationIndoorNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->m_local *= node->GetLocalMatrix();
		auto pos = m_states.CurrentState()->m_camera->GetPosition();
		
		if (Math::ClassifyPoint(m_states.CurrentState()->m_local.Inversed() * pos, node->GetConvexShape()) != Math::Relation::INSIDE)
		{
			out_message() << "OUTSIDE" << std::endl;
			for each (System::Proxy<Scene::PortalNode> portals in *node)
			{
				if (portals.IsValid())
				{
					Math::mat4 matrix = m_states.CurrentState()->m_camera->GetViewMatrix() * m_states.CurrentState()->m_local * node->GetLocalMatrix() * portals->GetLocalMatrix();
					Math::Portal portal = matrix * portals->GetPortal();

					Math::ClipSpace clip_space;
					Math::Portal clipped_portal;
					auto relation = Math::ClipPortal(m_states.CurrentState()->m_camera->ToClipSpace(), portal, clipped_portal, clip_space);
					if (relation != Math::Relation::NOT_VISIBLE)
					{
						m_states.CurrentState()->m_clip_space = clip_space;
						for each (System::Proxy<Scene::Node> child in *node)
						{
							if (child.IsValid())
							{
								if (!child->Apply(this))
									break;
							}
						}
					}
				}
			}
		}	
		else
		{
			out_message() << "INSIDE" << std::endl;
			for each (System::Proxy<Scene::Node> child in *node)
			{
				if (child.IsValid())
					if (!child->Apply(this))
						break;
			}
		}
		m_states.Pop();
		return true;
	}

	bool SimpleRender::Visit(Scene::PortalNode* node)
	{
		return true;
	}

	bool SimpleRender::Render()
	{
		m_states.CurrentState()->m_camera = m_scene->GetCameraNode()->GetCamera();
		m_states.CurrentState()->m_current_light_set = m_cooker.m_light_set;
		m_rt->Activate();
		m_scene->GetRootNode()->Apply(this);		
		Driver::Instance()->SwapBuffers();
		m_rt->Deactivate();
		return true;
	}

	void SimpleRender::SetScene(System::Proxy<Scene::SceneGraph> scene)
	{
		RenderTargetBackBuffer::RenderTargetBackBufferProperties p;
		m_rt = Driver::Instance()->CreateRenderTarget(&p);
		m_scene = scene;
		m_scene->GetRootNode()->Apply(&m_cooker);		
		m_context.Reset(new RenderContextBumpMapping());
		m_tc.Reset(new TextureContext());
	}

}