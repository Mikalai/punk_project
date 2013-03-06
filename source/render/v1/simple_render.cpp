#include "simple_render.h"
#include "../../gpu/module.h"
#include "../../virtual/module.h"
#include "../../scene/module.h"
#include "../../system/window/module.h"
#include "../../utility/fonts/font_builder.h"

#define STATE m_states.CurrentState()->Get()

namespace Render
{
	SimpleRender::SimpleRender(GPU::VideoDriver* driver)
		: m_driver(driver)
	{
		m_rt = nullptr;				
		m_text = nullptr;
		m_tc = nullptr;
		m_gui_render = nullptr;

		// next pointers should not be delete in destructor
		m_scene = nullptr;		
		m_root = nullptr;
		m_skin_rc = nullptr;
		m_context = nullptr;
		m_solid_rc = nullptr;
		m_textured_rc = nullptr;
		m_gui_rc = nullptr;
		m_terrain_rc = nullptr;
		m_paint_engine = nullptr;

	}

	SimpleRender::~SimpleRender()
	{
		try
		{
			Clear();
		}
		catch(...)
		{}
	}

	void SimpleRender::Clear()
	{
		safe_delete(m_rt);
		//safe_delete(m_scene);				
		safe_delete(m_text);		
		safe_delete(m_gui_render);
		safe_delete(m_tc);
	}

	bool SimpleRender::ApplyToChildren(Scene::Node* node)
	{
		for each (auto o in *node)
		{
			Scene::Node* child = As<Scene::Node*>(o);
			if (child)
				if (!child->Apply(this))
					return false;
		}
		return true;
	}

	bool SimpleRender::Visit(Scene::CameraNode* node)
	{
		bool result = true;
		m_frame->PushState();
		m_frame->SetViewMatrix(node->GetCamera()->GetViewMatrix());
		m_frame->SetProjectionMatrix(node->GetCamera()->GetProjectionMatrix());
		m_frame->SetClipSpace(node->GetCamera()->ToClipSpace());
		result = ApplyToChildren(node);
		m_frame->PopState();
		return result;
	}

	bool SimpleRender::Visit(Scene::TextureViewNode* node)
	{
		//RenderQuad(0, 0.8, 0.2, 0.2, Math::vec4(1,0,0,1));
		RenderTexturedQuad(node->GetX(), node->GetY(), node->GetWidth(), node->GetHeight(), node->GetWatchTexture());
		return true;
	}

	bool SimpleRender::Visit(Scene::StaticMeshNode* node)
	{				
		m_frame->PushState();
		m_frame->EnableBumpMapping(true);
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0,1,0,1));
		GPU::Renderable* mesh = As<GPU::Renderable*>(node->GetStaticGeometry()->GetGPUBufferCache());		
		m_frame->Render(mesh);	
		m_frame->PopState();
		return true;
	}

	bool SimpleRender::Visit(Scene::SkinMeshNode* node)
	{			
		m_frame->PushState();
		m_frame->EnableSkinning(true);		
		GPU::OpenGL::SkinMesh* mesh = Cast<GPU::OpenGL::SkinMesh*>(node->GetSkinGeometry()->GetGPUBufferCache());
		m_frame->Render(mesh);		
		m_frame->PopState();
		return true;
	}

	bool SimpleRender::Visit(Scene::ArmatureNode* node)
	{		
		bool result = true;
		Virtual::Action::validate();
		m_frame->PushState();

		//	should be moved in update visitor
		Virtual::Armature* armature = Virtual::Armature::find(node->GetStorageName());
		Virtual::Action* action = Virtual::Action::find(L"male_walk");
		for (int i = 0, max_i = armature->GetBonesCount(); i < max_i; ++i)
		{
			Virtual::Bone* bone = armature->GetBoneByIndex(i);
			Virtual::Animation* anim = Cast<Virtual::Animation*>(action->Find(bone->GetName()));
			auto pos = anim->GetPosition(m_time);
			auto rot = anim->GetRotation(m_time);			
			Math::mat4 m = Math::mat4::CreateTranslate(pos) * Math::QuaternionToMatrix4x4(rot);
			bone->SetBoneMatrix(m);
		}	
		
		result = ApplyToChildren(node);

		m_frame->PopState();
		return result;
	}

	bool SimpleRender::Visit(Scene::BoneNode* node)
	{
		bool result = true;
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(1, 1, 0, 1));
		m_frame->PushState();

		Virtual::Bone* bone = node->GetBone();		
		m_frame->MultWorldMatrix(bone->GetAnimatedGlobalMatrix());
		m_frame->SetBoneMatrix(bone->GetIndex(), m_frame->GetWorldMatrix());		
		
		result = ApplyToChildren(node);

		m_frame->PopState();
		return result;
	}

	bool SimpleRender::Visit(Scene::LightNode* node)
	{
		return ApplyToChildren(node);		
	}

	bool SimpleRender::Visit(Scene::MaterialNode* node)
	{
		bool result = true;
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0, 0, 1, 1));
		m_frame->PushState();
		auto material = node->GetMaterial();
		m_frame->SetDiffuseColor(material->GetDiffuseColor());
		m_frame->SetDiffuseMap0(Cast<GPU::Texture2D*>(node->GetMaterial()->GetCache().m_diffuse_texture_cache));
		m_frame->SetBumpMap(Cast<GPU::Texture2D*>(node->GetMaterial()->GetCache().m_normal_texture_cache));
		m_frame->SetSpecularColor(material->GetSpecularColor());
		m_frame->SetSpecularMap(Cast<GPU::Texture2D*>(node->GetMaterial()->GetCache().m_specular_texture_cache));
		m_frame->SetAmbientColor(material->GetAmbient());
		m_frame->SetSpecularFactor(material->GetSpecularFactor());

		result = ApplyToChildren(node);

		m_frame->PopState();
		return result;
	}

	bool SimpleRender::Visit(Scene::Node* node)
	{
		return ApplyToChildren(node);		
	}
	bool SimpleRender::Visit(Scene::TransformNode* node)
	{		
		bool result = true;
		const Math::mat4& view = m_frame->GetViewMatrix();
		const Math::ClipSpace& clip_space = m_frame->GetClipSpace();
		if (Math::Relation::VISIBLE != Math::ClassifyBoudingSphere(view * node->GetBoundingSphere(), clip_space))
			return true;
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0, 0, 0, 1));
		m_frame->PushState();
		m_frame->SetLocalMatrix(node->GetLocalMatrix());
		m_frame->MultWorldMatrix(node->GetLocalMatrix());

		result = ApplyToChildren(node);
		m_frame->PopState();

		return result;
	}

	bool SimpleRender::Visit(Scene::LocationIndoorNode* node)
	{
		bool result = true;
		m_frame->PushState();
		m_frame->MultWorldMatrix(node->GetLocalMatrix());

		auto pos = m_frame->GetViewMatrix().TranslationPart();
		auto world = m_frame->GetWorldMatrix();
		auto view = m_frame->GetViewMatrix();
		if (Math::ClassifyPoint(world.Inversed() * pos, node->GetConvexShape()) != Math::Relation::INSIDE)
		{
			out_message() << "OUTSIDE" << std::endl;
			for each (auto o in *node)
			{
				Scene::PortalNode* portals = As<Scene::PortalNode*>(o);
				if (portals)
				{
					Math::mat4 matrix = view * world * portals->GetLocalMatrix();
					Math::Portal portal = matrix * portals->GetPortal();

					Math::ClipSpace clip_space;
					Math::Portal clipped_portal;
					auto relation = Math::ClipPortal(m_frame->GetClipSpace(), portal, clipped_portal, clip_space);

					if (relation != Math::Relation::NOT_VISIBLE)
					{
						m_frame->SetClipSpace(clip_space);
						result = ApplyToChildren(node);
					}
				}
			}
		}	
		else
		{
			out_message() << "INSIDE" << std::endl;
			result = ApplyToChildren(node);
		}
		m_frame->PopState();
		return result;
	}

	bool SimpleRender::Visit(Scene::PortalNode* node)
	{
		//RenderCube(1,1,1);
		//m_text->SetText(L"Hello world");
		//RenderTexturedQuad(0,0,1,1,m_text->GetTexture());
		//RenderText(-0.9, 0, L"Вітаю Вас, шаноўнае спадарства! PunkEngine ńešta moža :)", Math::vec4(0, 1, 0, 1));
		return true;
	}

	bool SimpleRender::Visit(Scene::TerrainNode* node)
	{
		bool result = true;
		m_frame->PushState();
	
		auto camera_position = m_frame->GetViewMatrix().TranslationPart();
		Math::vec2 relative_pos = (node->GetTerrainObserver()->GetTerrainView()->GetPosition() - camera_position.XZ());		
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(camera_position.X(), 0, camera_position.Z()));

		//STATE.m_terrain = node->GetTerrainObserver()->GetTerrainView()->GetTerrain();
		///STATE.m_terrain_observer = node->GetTerrainObserver();

		static Math::vec3 sun(100, 100, 100);
		static float angle = 0;

		//STATE.m_height_map_slot = 0;
		/*STATE.m_diffuse_slot_0 = 1;
		STATE.m_diffuse_slot_1 = 2;
		STATE.m_normal_slot = 3;*/

		Virtual::TerrainView* view = node->GetTerrainObserver()->GetTerrainView();
		if (view && view->GetHeightMap()->IsValid())
		{
			//m_tc = m_tc;
			m_frame->SetHeightMap(view->GetHeightMap());
			m_frame->SetDiffuseMap0(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache));
			m_frame->SetDiffuseMap1(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache_2));
			m_frame->SetBumpMap(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_normal_texture_cache));
			m_frame->EnableWireframe(false);
			m_frame->EnableDepthTest(true);
			m_frame->SetLineWidth(1);
			m_frame->EnableTerrainRendering(true);
			m_frame->Render(&m_grid);
		}
		m_frame->PopState();
		return result;
	}

	void SimpleRender::RenderCube(float width, float height, float depth)
	{
		m_frame->PushState();
		//	shift quad
		m_frame->MultWorldMatrix(Math::mat4::CreateScaling(width, height, depth));		
		m_frame->SetDiffuseColor(Math::vec4(0,1,0,1));
		m_frame->EnableWireframe(true);
		m_frame->Render(GPU::OpenGL::CubeObject::Instance());
		m_frame->PopState();
	}

	void SimpleRender::RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color)
	{
		m_frame->PushState();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(position) * Math::mat4::CreateScaling(radius, radius, radius));		
		m_frame->SetDiffuseColor(color);
		m_frame->EnableWireframe(true);
		m_frame->SetLineWidth(5.0f);
		m_frame->Render(GPU::OpenGL::SphereObject::Instance());
		m_frame->PopState();
	}

	void SimpleRender::RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
	{
		m_frame->PushState();
		//	shift quadSTATE
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(color);
		m_frame->Render(GPU::OpenGL::QuadObject::Instance());
		m_frame->PopState();
	}

	void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, GPU::Texture2D* texture)
	{
		m_frame->PushState();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(Math::vec4(1,1,1,1));
		m_frame->SetTextureMatrix(Math::mat2::CreateMirrorX());
		m_frame->EnableWireframe(false);
		m_frame->SetDiffuseMap0(texture);
		m_frame->EnableLighting(false);
		m_frame->EnableTexturing(true);
		m_frame->Render(GPU::OpenGL::QuadObject::Instance());
		m_frame->PopState();
	}

	void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	{
		Utility::FontBuilder::Instance()->SetCharSize(14, 14);
		int len = Utility::FontBuilder::Instance()->CalculateLength(text.Data());
		int h = Utility::FontBuilder::Instance()->CalculateHeight(text.Data());
		GPU::OpenGL::TextSurface s;
		s.SetSize(len, h);
		s.SetText(text);
		
		m_frame->PushState();
		float width = 2.0f * len / (float)m_driver->GetWindow()->GetWidth();
		float height = 2.0f * h / (float)m_driver->GetWindow()->GetHeight();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(x, y, 0) * Math::mat4::CreateScaling(width, height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(Math::vec4(0,0,1,1));
		m_frame->SetTextureMatrix(Math::mat2::CreateMirrorX());
		m_frame->SetDiffuseMap0(s.GetTexture());
		m_frame->EnableTexturing(true);
		m_frame->EnableLighting(false);
		m_frame->EnableDiffuseShading(true);
		m_frame->Render(GPU::OpenGL::QuadObject::Instance());
		m_frame->PopState();
	}

	bool SimpleRender::Render()
	{
		m_time += 0.1f;
		m_rt->Activate();			
		m_frame = m_driver->BeginFrame();
		if (m_scene)
		{
			m_frame->SetViewMatrix(m_scene->GetCameraNode()->GetCamera()->GetViewMatrix());
			m_frame->SetProjectionMatrix(m_scene->GetCameraNode()->GetCamera()->GetProjectionMatrix());
			m_frame->SetClipSpace(m_scene->GetCameraNode()->GetCamera()->ToClipSpace());
			m_scene->GetRootNode()->Apply(this);			
		}
		if (m_root)
		{
			m_gui_render->Begin(0, 0, m_driver->GetWindow()->GetWidth(), m_driver->GetWindow()->GetHeight());
			m_gui_render->RenderWidget(m_root);
			m_gui_render->End();
		}
		if (m_paint_engine)
		{
			GPU::OpenGL::OpenGLPaintEngine* device = Cast<GPU::OpenGL::OpenGLPaintEngine*>(m_paint_engine);
			RenderTexturedQuad(0, 0, 1, 1, device->GetRenderTarget()->GetColorBuffer());
		}
		m_driver->EndFrame(m_frame);
		m_rt->Deactivate();
		return true;
	}

	void SimpleRender::SetScene(Scene::SceneGraph* scene)
	{
		m_terrain_slices = 63;
		m_time = 0;
		GPU::OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;
		m_tc = new GPU::OpenGL::TextureContext;
		m_rt = new GPU::OpenGL::RenderTargetBackBuffer;
		m_rt->Init(&p);
		m_scene = scene;
		if (m_scene)
			m_scene->GetRootNode()->Apply(&m_cooker);		
		m_context = GPU::AbstractRenderPolicy::find(GPU::RC_BUMP_MAPING);
		m_solid_rc = GPU::AbstractRenderPolicy::find(GPU::RC_SOLD_3D);
		m_textured_rc = GPU::AbstractRenderPolicy::find(GPU::RC_TEXTURED_3D);
		m_gui_rc = GPU::AbstractRenderPolicy::find(GPU::RC_GUI);
		m_skin_rc = GPU::AbstractRenderPolicy::find(GPU::RC_SKINNING);
		m_terrain_rc = GPU::AbstractRenderPolicy::find(GPU::RC_TERRAIN);
		m_text = new GPU::OpenGL::TextSurface;
		m_text->SetSize(int(m_driver->GetWindow()->GetWidth() * 0.5f), int(m_driver->GetWindow()->GetHeight() * 0.5f));
		m_gui_render = new GUIRender;		
		m_grid.Cook(64, 64, m_terrain_slices, m_terrain_slices, 5);	}

	//void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<Texture2D> texture)
	//{
	//}

	//void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4& color)
	//{
	//}

}