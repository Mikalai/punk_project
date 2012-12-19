#include "simple_render.h"
#include "../driver.h"
#include "../../virtual/data/data.h"
#include "../renderable/renderable_data.h"
#include "../../scene/scene_graph.h"
#include "../render_context/render_contexts.h"
#include "../textures/textures.h"
#include "../textures/text_surface.h"
#include "render_target_back_buffer.h"
#include "../../system/window.h"
#include "../../utility/fonts/font_builder.h"
#include "../../virtual/animation/anim.h"
namespace OpenGL
{
	MeshCooker::MeshCooker()
	{
		//m_light_set.Reset(new Virtual::LightSet);
	}

	bool MeshCooker::Visit(Scene::CameraNode* node)
	{
		return true;
	}

	bool MeshCooker::Visit(Scene::SkinMeshNode* node)
	{
		System::Proxy<Virtual::SkinGeometry> geom = Virtual::SkinGeometryManager::Instance()->Load(node->GetStorageName());
		
		System::Proxy<SkinMesh> mesh = System::GetFactory()->Create(geom->GetStorageName(), System::ObjectType::SKIN_MESH);

		if (!mesh->Cook(geom, m_current_armature))
			return (out_error() << "Can't cook static mesh from static geometry" << std::endl, false);
		return true;
	}

	bool MeshCooker::Visit(Scene::ArmatureNode* node)
	{		
		m_current_armature = Virtual::ArmatureManager::Instance()->Load(node->GetStorageName());
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
		System::Proxy<Virtual::StaticGeometry> geom = node->GetStaticGeometry();	
		
		System::Proxy<StaticMesh> mesh = System::GetFactory()->Create(geom->GetStorageName(), System::ObjectType::STATIC_MESH);

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

	bool MeshCooker::Visit(Scene::PortalNode* node)
	{		
		return true;
	}

	bool SimpleRender::Visit(Scene::CameraNode* node)
	{
		m_states.Push();
		m_states.CurrentState()->m_view = node->GetCamera()->GetViewMatrix();
		m_states.CurrentState()->m_projection = node->GetCamera()->GetProjectionMatrix();
		m_states.CurrentState()->m_camera_position = node->GetCamera()->GetPosition();
		m_states.CurrentState()->m_camera = node->GetCamera();

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				child->Apply(this);
		}
		return true;
	}

	bool SimpleRender::Visit(Scene::StaticMeshNode* node)
	{		
		System::Proxy<StaticMesh> mesh = StaticMeshManager::Instance()->Load(node->GetStorageName());		
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

	bool SimpleRender::Visit(Scene::SkinMeshNode* node)
	{				
		System::Proxy<Virtual::Armature> armature = m_states.CurrentState()->m_armature;
		//out_message() << "Mesh matrix: " << m_states.CurrentState()->m_mesh_matrix_local.ToString() << std::endl;
		//for (int i = 0; i < armature->GetBonesCount(); ++i)
		//{
		//	Virtual::Bone* bone = armature->GetBoneByIndex(i);
		//	out_message() << bone->GetName() << ": " << std::endl << (m_states.CurrentState()->m_armature_world * bone->GetAnimatedGlobalMatrix()).ToString() << std::endl;
		//}

		System::Proxy<SkinMesh> mesh = SkinMeshManager::Instance()->Load(node->GetStorageName());				
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

	bool SimpleRender::Visit(Scene::ArmatureNode* node)
	{
		m_states.Push();
				
		System::Proxy<Virtual::Armature> armature = Virtual::ArmatureManager::Instance()->Load(node->GetStorageName());
		System::Proxy<Virtual::Action> action = Virtual::ActionManager::Instance()->Load(L"sitdown");
		for (int i = 0, max_i = armature->GetBonesCount(); i < max_i; ++i)
		{
			Virtual::Bone* bone = armature->GetBoneByIndex(i);
			System::Proxy<Virtual::Animation> anim = action->Find(bone->GetName());
			if (!anim.IsValid())
				return (out_error() << "Can't get animation for " << bone->GetName() << std::endl, false);
			auto pos = anim->GetPosition(m_time);
			auto rot = anim->GetRotation(m_time);			
			Math::mat4 m = Math::mat4::CreateTranslate(pos) * Math::QuaternionToMatrix4x4(rot);
			bone->SetBoneMatrix(m);
		}

		m_states.CurrentState()->m_armature = armature;
		m_states.CurrentState()->m_armature_world = m_states.CurrentState()->m_local;
		m_states.CurrentState()->m_render_policy = m_skin_rc;

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					return false;
		}
		m_states.Pop();
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
		//m_states.CurrentState()->m_render_policy = m_context;
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
		m_states.CurrentState()->m_mesh_matrix_local = node->GetLocalMatrix();
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
		auto pos = m_states.CurrentState()->m_camera_position;
		
		if (Math::ClassifyPoint(m_states.CurrentState()->m_local.Inversed() * pos, node->GetConvexShape()) != Math::Relation::INSIDE)
		{
			out_message() << "OUTSIDE" << std::endl;
			for each (System::Proxy<Scene::PortalNode> portals in *node)
			{
				if (portals.IsValid())
				{
					Math::mat4 matrix = m_states.CurrentState()->m_view * m_states.CurrentState()->m_local * node->GetLocalMatrix() * portals->GetLocalMatrix();
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
		//m_text->SetText(L"Hello world");
		//RenderTexturedQuad(0,0,1,1,m_text->GetTexture());
		RenderText(-0.9, 0, L"Вітаю Вас, шаноўнае спадарства! PunkEngine ńešta moža :)", Math::vec4(0, 1, 0, 1));
		return true;
	}

	void SimpleRender::RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
	{
		m_states.Push();
		//	shift quad
		m_states.CurrentState()->m_local = Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(width, height, 1);
		m_states.CurrentState()->m_projection = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_view = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_diffuse_color = color;
		m_solid_rc->Begin();
		m_solid_rc->BindParameters(m_states.CurrentState());
		QuadObject::Instance()->Bind(m_solid_rc->GetRequiredAttributesSet());
		QuadObject::Instance()->Render();
		QuadObject::Instance()->Unbind();
		m_solid_rc->End();
		m_states.Pop();
	}

	void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, const System::Proxy<Texture2D> texture)
	{
		m_states.Push();
		//	shift quad
		m_states.CurrentState()->m_local = Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(width, height, 1);
		m_states.CurrentState()->m_projection = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_view = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_diffuse_slot = 0;
		m_states.CurrentState()->m_diffuse_color.Set(1,1,1,1);
		m_states.CurrentState()->m_texture_matrix = Math::mat2::CreateMirrorX();
		m_tc->SetTexture(0, texture);
		m_tc->Bind();
		m_textured_rc->Begin();
		m_textured_rc->BindParameters(m_states.CurrentState());
		QuadObject::Instance()->Bind(m_textured_rc->GetRequiredAttributesSet());
		QuadObject::Instance()->Render();
		QuadObject::Instance()->Unbind();
		m_textured_rc->End();
		m_tc->Unbind();
		m_states.Pop();
	}

	void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	{
		Utility::FontBuilder::Instance()->SetCharSize(14, 14);
		int len = Utility::FontBuilder::Instance()->CalculateLength(text.Data());
		int h = Utility::FontBuilder::Instance()->CalculateHeight(text.Data());
		TextSurface s;
		s.SetSize(len, h);
		s.SetText(text);
		m_states.Push();
		float width = 2.0f * len / (float)System::Window::Instance()->GetWidth();
		float height = 2.0f * h / (float)System::Window::Instance()->GetHeight();
		//	shift quad
		m_states.CurrentState()->m_local = Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(width, height, 1);
		m_states.CurrentState()->m_projection = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_view = Math::mat4::CreateIdentity();
		m_states.CurrentState()->m_diffuse_slot = 0;
		m_states.CurrentState()->m_diffuse_color.Set(0,0,1,1);
		m_states.CurrentState()->m_no_diffuse_texture_color.Set(1,1,1,1);
		m_states.CurrentState()->m_texture_matrix = Math::mat2::CreateMirrorX();
		m_states.CurrentState()->m_text_slot = 0;
		
		m_tc->SetTexture(0, s.GetTexture());
		m_tc->SetTexture(1, System::Proxy<Texture2D>(0));
		m_tc->Bind();
		m_gui_rc->Begin();
		m_gui_rc->BindParameters(m_states.CurrentState());
		QuadObject::Instance()->Bind(m_gui_rc->GetRequiredAttributesSet());
		QuadObject::Instance()->Render();
		QuadObject::Instance()->Unbind();
		m_gui_rc->End();
		m_tc->Unbind();
		m_states.Pop();
	}


	bool SimpleRender::Render()
	{
		m_time += 0.01;
		m_states.CurrentState()->m_camera_position = m_scene->GetCameraNode()->GetCamera()->GetPosition();
		m_states.CurrentState()->m_projection = m_scene->GetCameraNode()->GetCamera()->GetProjectionMatrix();
		m_states.CurrentState()->m_view = m_scene->GetCameraNode()->GetCamera()->GetViewMatrix();
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
		m_time = 0;
		RenderTargetBackBuffer::RenderTargetBackBufferProperties p;
		m_rt = Driver::Instance()->CreateRenderTarget(&p);
		m_scene = scene;
		m_scene->GetRootNode()->Apply(&m_cooker);		
		m_context.Reset(new RenderContextBumpMapping());
		m_tc.Reset(new TextureContext());
		m_solid_rc.Reset(new RenderContextSolid3D);
		m_textured_rc.Reset(new RenderContextSolidTexture3D);
		m_gui_rc.Reset(new RenderContextGUI);
		m_skin_rc.Reset(new RenderContextSkinning);
		m_text.Reset(new TextSurface);
		m_text->SetSize(System::Window::Instance()->GetWidth() * 0.5, System::Window::Instance()->GetHeight()*0.5);
	}

	//void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<Texture2D> texture)
	//{
	//}

	//void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	//{
	//}

}