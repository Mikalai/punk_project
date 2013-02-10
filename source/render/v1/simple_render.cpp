#include "simple_render.h"
#include "../../gpu/module.h"
#include "../../virtual/module.h"
#include "../../scene/module.h"
#include "../../system/window/module.h"
#include "../../utility/fonts/font_builder.h"

#define STATE m_states.CurrentState()->Get()

namespace Render
{
	SimpleRender::SimpleRender(System::Proxy<GPU::OpenGL::Driver> driver)
		: m_driver(driver)
	{}

	bool SimpleRender::Visit(Scene::CameraNode* node)
	{
		m_states.Push();
		STATE.m_view = node->GetCamera()->GetViewMatrix();
		STATE.m_projection = node->GetCamera()->GetProjectionMatrix();
		STATE.m_camera_position = node->GetCamera()->GetPosition();
		STATE.m_camera = node->GetCamera();

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				child->Apply(this);
		}
		return true;
	}

	bool SimpleRender::Visit(Scene::DebugTextureViewNode* node)
	{
		//RenderQuad(0, 0.8, 0.2, 0.2, Math::vec4(1,0,0,1));
		RenderTexturedQuad(0, 0.8, 0.2, 0.2, node->GetWatchTexture());
		return true;
	}

	bool SimpleRender::Visit(Scene::StaticMeshNode* node)
	{				
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0,1,0,1));
		System::Proxy<GPU::OpenGL::StaticMesh> mesh = node->GetStaticGeometry()->GetGPUBufferCache();// = GPU::OpenGL::StaticMeshManager::Instance()->Load(node->GetStorageName());		
		const Math::BoundingBox& bbox = mesh->GetBoundingBox();		
		m_tc->Bind();
		if (!STATE.m_rc.IsValid())
			STATE.m_rc = m_context;
		STATE.m_rc->Begin();
		STATE.m_rc->BindParameters(STATE);	
		mesh->Bind(STATE.m_rc->GetRequiredAttributesSet());
		mesh->Render();
		mesh->Unbind();		
		STATE.m_rc->End();		
		m_tc->Unbind();
		return true;
	}

	bool SimpleRender::Visit(Scene::SkinMeshNode* node)
	{			
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0,1,0,1));
		System::Proxy<Virtual::Armature> armature = STATE.m_armature;
		//out_message() << "Mesh matrix: " << STATE.m_mesh_matrix_local.ToString() << std::endl;
		//for (int i = 0; i < armature->GetBonesCount(); ++i)
		//{
		//	Virtual::Bone* bone = armature->GetBoneByIndex(i);
		//	out_message() << bone->GetName() << ": " << std::endl << (STATE.m_armature_world * bone->GetAnimatedGlobalMatrix()).ToString() << std::endl;
		//}
		STATE.m_rc = m_skin_rc;
		System::Proxy<GPU::OpenGL::SkinMesh> mesh = node->GetSkinGeometry()->GetGPUBufferCache();
		m_tc->Bind();		
		STATE.m_rc->Begin();
		STATE.m_rc->BindParameters(STATE);		
		mesh->Bind(STATE.m_rc->GetRequiredAttributesSet());
		mesh->Render();
		mesh->Unbind();		
		STATE.m_rc->End();		
		m_tc->Unbind();
		return true;
	}

	bool SimpleRender::Visit(Scene::ArmatureNode* node)
	{		
		Virtual::Action::validate();
		m_states.Push();	
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(1, 0, 0, 1));
		System::Proxy<Virtual::Armature> armature = Virtual::Armature::find(node->GetStorageName());
		System::Proxy<Virtual::Action> action = Virtual::Action::find(L"male_walk");
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

		STATE.m_armature = armature;
		STATE.m_armature_world = STATE.m_local;
		STATE.m_rc = m_skin_rc;

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
				if (!child->Apply(this))
					return false;
		}
		m_states.Pop();
		return true;
	}

	bool SimpleRender::Visit(Scene::BoneNode* node)
	{
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(1, 1, 0, 1));
		m_states.Push();
		STATE.m_rc = m_context;
		System::Proxy<Virtual::Armature> armature = STATE.m_armature;
		if (!armature.IsValid())
			return (out_error() << "It is impossible to process bone node without valid armature" << std::endl, false);

		Virtual::Bone* bone = armature->GetBoneByName(node->GetName());
		if (!bone)
			return (out_error() << "Bone " << node->GetName() << std::endl, false);

		STATE.m_local *= bone->GetAnimatedGlobalMatrix();

		for each (System::Proxy<Scene::Node> child in *node)
		{
			if (child.IsValid())
			{
				if (!child->Apply(this))
					return false;
			}
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
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0, 0, 1, 1));
		m_states.Push();
		STATE.m_material = Virtual::Material::find(node->GetStorageName());
		//m_tc = m_tc;
		m_tc->SetTexture(0, node->GetMaterial()->GetCache().m_diffuse_texture_cache);
		m_tc->SetTexture(1, node->GetMaterial()->GetCache().m_normal_texture_cache);
		STATE.m_diffuse_slot_0 = 0;
		STATE.m_normal_slot = 1;
		//STATE.m_rc = m_context;
		//STATE.m_rc->Init();
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
		if (Math::Relation::VISIBLE != Math::ClassifyBoudingSphere(STATE.m_camera->GetViewMatrix() * node->GetBoundingSphere(), STATE.m_camera->ToClipSpace()))
			return true;
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0, 0, 0, 1));
		m_states.Push();
		STATE.m_mesh_matrix_local = node->GetLocalMatrix();
		STATE.m_local *= node->GetLocalMatrix();
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
		STATE.m_local *= node->GetLocalMatrix();
		auto pos = STATE.m_camera_position;

		if (Math::ClassifyPoint(STATE.m_local.Inversed() * pos, node->GetConvexShape()) != Math::Relation::INSIDE)
		{
			out_message() << "OUTSIDE" << std::endl;
			for each (System::Proxy<Scene::PortalNode> portals in *node)
			{
				if (portals.IsValid())
				{
					Math::mat4 matrix = STATE.m_view * STATE.m_local * node->GetLocalMatrix() * portals->GetLocalMatrix();
					Math::Portal portal = matrix * portals->GetPortal();

					Math::ClipSpace clip_space;
					Math::Portal clipped_portal;
					auto relation = Math::ClipPortal(STATE.m_camera->ToClipSpace(), portal, clipped_portal, clip_space);
					if (relation != Math::Relation::NOT_VISIBLE)
					{
						STATE.m_clip_space = clip_space;
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
		RenderCube(1,1,1);
		//m_text->SetText(L"Hello world");
		//RenderTexturedQuad(0,0,1,1,m_text->GetTexture());
		//RenderText(-0.9, 0, L"Вітаю Вас, шаноўнае спадарства! PunkEngine ńešta moža :)", Math::vec4(0, 1, 0, 1));
		return true;
	}

	bool SimpleRender::Visit(Scene::TerrainNode* node)
	{
		m_states.Push();

		Math::vec2 relative_pos = (node->GetTerrainObserver()->GetTerrainView()->GetPosition() - STATE.m_camera->GetPosition().XZ());

		STATE.m_local = Math::mat4::CreateTranslate(STATE.m_camera->GetPosition().X(), 0, 
			STATE.m_camera->GetPosition().Z());
		STATE.m_terrain = node->GetTerrainObserver()->GetTerrainView()->GetTerrain();
		STATE.m_terrain_observer = node->GetTerrainObserver();

		static Math::vec3 sun(100, 100, 100);
		static float angle = 0;

		STATE.m_height_map_slot = 0;
		STATE.m_diffuse_slot_0 = 1;
		STATE.m_diffuse_slot_1 = 2;
		STATE.m_normal_slot = 3;

		System::Proxy<Virtual::TerrainView> view = node->GetTerrainObserver()->GetTerrainView();
		if (view.IsValid() && view->GetHeightMap()->IsValid())
		{
			//m_tc = m_tc;
			m_tc->SetTexture(0, view->GetHeightMap());
			m_tc->SetTexture(1, node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache);
			m_tc->SetTexture(2, node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache_2);
			m_tc->SetTexture(3, node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_normal_texture_cache);

			m_terrain_rc->Begin();
			m_grid.Bind(m_terrain_rc->GetRequiredAttributesSet());
			m_tc->Bind();		
			STATE.m_wireframe = false;
			STATE.m_depth_test = true;
			STATE.m_line_width = 1;
			//STATE.m_terran_position = Math::vec2(floor(STATE.m_camera->GetPosition().X()), floor(STATE.m_camera->GetPosition().Z()));
			auto v = node->GetTerrainObserver()->GetTerrainView()->GetPosition();
			STATE.m_terran_position.Set(floor(v.X()), floor(v.Y()));
			m_terrain_rc->BindParameters(STATE);
			m_grid.Render();

			m_terrain_rc->End();
			m_tc->Unbind();
			m_grid.Unbind();
		}
		m_states.Pop();
		return true;
	}

	void SimpleRender::RenderCube(float width, float height, float depth)
	{
		m_states.Push();
		//	shift quad
		STATE.m_local *= Math::mat4::CreateScaling(width, height, depth);		
		STATE.m_diffuse_color.Set(0,1,0,1);
		STATE.m_wireframe = true;
		m_solid_rc->Begin();
		m_solid_rc->BindParameters(STATE);
		GPU::OpenGL::CubeObject::Instance()->Bind(m_context->GetRequiredAttributesSet());
		GPU::OpenGL::CubeObject::Instance()->Render();
		GPU::OpenGL::CubeObject::Instance()->Unbind();
		m_solid_rc->End();
		m_states.Pop();
	}

	void SimpleRender::RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color)
	{
		m_states.Push();
		//	shift quad
		STATE.m_local = Math::mat4::CreateTranslate(position) * Math::mat4::CreateScaling(radius, radius, radius);		
		STATE.m_diffuse_color = color;
		STATE.m_wireframe = true;
		STATE.m_line_width = 5.0f;
		m_solid_rc->Begin();
		m_solid_rc->BindParameters(STATE);
		GPU::OpenGL::SphereObject::Instance()->Bind(m_context->GetRequiredAttributesSet());
		GPU::OpenGL::SphereObject::Instance()->Render();
		GPU::OpenGL::SphereObject::Instance()->Unbind();
		m_solid_rc->End();
		m_states.Pop();
	}

	void SimpleRender::RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
	{
		m_states.Push();
		//	shift quadSTATE
		STATE.m_local = Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1);
		STATE.m_projection = Math::mat4::CreateIdentity();
		STATE.m_view = Math::mat4::CreateIdentity();
		STATE.m_diffuse_color = color;
		m_solid_rc->Begin();
		m_solid_rc->BindParameters(STATE);
		GPU::OpenGL::QuadObject::Instance()->Bind(m_solid_rc->GetRequiredAttributesSet());
		GPU::OpenGL::QuadObject::Instance()->Render();
		GPU::OpenGL::QuadObject::Instance()->Unbind();
		m_solid_rc->End();
		m_states.Pop();
	}

	void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, const System::Proxy<GPU::OpenGL::Texture2D> texture)
	{
		m_states.Push();
		//	shift quad
		STATE.m_local = Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1);
		STATE.m_projection = Math::mat4::CreateIdentity();
		STATE.m_view = Math::mat4::CreateIdentity();
		STATE.m_diffuse_slot_0 = 0;
		STATE.m_diffuse_color.Set(1,1,1,1);
		STATE.m_texture_matrix = Math::mat2::CreateMirrorX();
		STATE.m_wireframe = false;
		m_tc->Clear();
		m_tc->SetTexture(0, texture);
		m_tc->Bind();
		m_textured_rc->Begin();
		m_textured_rc->BindParameters(STATE);
		GPU::OpenGL::QuadObject::Instance()->Bind(m_textured_rc->GetRequiredAttributesSet());
		GPU::OpenGL::QuadObject::Instance()->Render();
		GPU::OpenGL::QuadObject::Instance()->Unbind();
		m_textured_rc->End();
		m_tc->Unbind();
		m_states.Pop();
	}

	void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	{
		Utility::FontBuilder::Instance()->SetCharSize(14, 14);
		int len = Utility::FontBuilder::Instance()->CalculateLength(text.Data());
		int h = Utility::FontBuilder::Instance()->CalculateHeight(text.Data());
		GPU::OpenGL::TextSurface s;
		s.SetSize(len, h);
		s.SetText(text);
		m_states.Push();
		float width = 2.0f * len / (float)m_driver->GetWindow()->GetWidth();
		float height = 2.0f * h / (float)m_driver->GetWindow()->GetHeight();
		//	shift quad
		STATE.m_local = Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(width, height, 1);
		STATE.m_projection = Math::mat4::CreateIdentity();
		STATE.m_view = Math::mat4::CreateIdentity();
		STATE.m_diffuse_slot_0 = 0;
		STATE.m_diffuse_color.Set(0,0,1,1);
		STATE.m_no_diffuse_texture_color.Set(1,1,1,1);
		STATE.m_texture_matrix = Math::mat2::CreateMirrorX();
		STATE.m_text_slot = 0;

		m_tc->SetTexture(0, s.GetTexture());
		m_tc->SetTexture(1, System::Proxy<GPU::OpenGL::Texture2D>(0));
		m_tc->Bind();
		m_gui_rc->Begin();
		m_gui_rc->BindParameters(STATE);
		GPU::OpenGL::QuadObject::Instance()->Bind(m_gui_rc->GetRequiredAttributesSet());
		GPU::OpenGL::QuadObject::Instance()->Render();
		GPU::OpenGL::QuadObject::Instance()->Unbind();
		m_gui_rc->End();
		m_tc->Unbind();
		m_states.Pop();
	}


	bool SimpleRender::Render()
	{
		m_time += 0.1f;
		m_rt->Activate();			
		if (m_scene.IsValid())
		{
			STATE.m_camera_position = m_scene->GetCameraNode()->GetCamera()->GetPosition();
			STATE.m_projection = m_scene->GetCameraNode()->GetCamera()->GetProjectionMatrix();
			STATE.m_view = m_scene->GetCameraNode()->GetCamera()->GetViewMatrix();
			STATE.m_camera = m_scene->GetCameraNode()->GetCamera();
			STATE.m_lights = m_cooker.m_light_set;
			m_scene->GetRootNode()->Apply(this);			
		}
		if (m_root.IsValid())
		{
			m_gui_render->Begin(0, 0, m_driver->GetWindow()->GetWidth(), m_driver->GetWindow()->GetHeight());
			m_gui_render->RenderWidget(m_root.Get());
			m_gui_render->End();
		}
		m_driver->SwapBuffers();
		m_rt->Deactivate();
		return true;
	}

	void SimpleRender::SetScene(System::Proxy<Scene::SceneGraph> scene)
	{
		m_terrain_slices = 63;
		m_time = 0;
		GPU::OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;
		m_rt.Reset(new GPU::OpenGL::RenderTargetBackBuffer);
		m_rt->Init(&p);
		m_scene = scene;
		if (m_scene.IsValid())
			m_scene->GetRootNode()->Apply(&m_cooker);		
		m_context = GPU::AbstractRenderPolicy::find(GPU::RC_BUMP_MAPING);
		m_tc.Reset(new GPU::OpenGL::TextureContext());
		m_solid_rc = GPU::AbstractRenderPolicy::find(GPU::RC_SOLD_3D);
		m_textured_rc = GPU::AbstractRenderPolicy::find(GPU::RC_TEXTURED_3D);
		m_gui_rc = GPU::AbstractRenderPolicy::find(GPU::RC_GUI);
		m_skin_rc = GPU::AbstractRenderPolicy::find(GPU::RC_SKINNING);
		m_terrain_rc = GPU::AbstractRenderPolicy::find(GPU::RC_TERRAIN);
		m_text.Reset(new GPU::OpenGL::TextSurface);
		m_text->SetSize(int(m_driver->GetWindow()->GetWidth() * 0.5f), int(m_driver->GetWindow()->GetHeight() * 0.5f));
		m_gui_render.Reset(new GUIRender);		
		m_grid.Cook(64, 64, m_terrain_slices, m_terrain_slices, 5);	}

	//void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<Texture2D> texture)
	//{
	//}

	//void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	//{
	//}

}