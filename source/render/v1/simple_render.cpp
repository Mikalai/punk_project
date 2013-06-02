/**
*	ł
*/

#include "simple_render.h"
#include "../../gpu/module.h"
#include "../../virtual/module.h"
#include "../../scene/module.h"
#include "../../system/window/module.h"
#include "../../utility/fonts/font_builder.h"

#define STATE m_states.CurrentState()->Get()

namespace Render
{
// TODO (chip#1#): global variable should be removed
    Utility::FontBuilder g_font_builder;

	SimpleRender::SimpleRender(GPU::VideoDriver* driver)
		: m_driver(driver)
        , m_grid(driver)
        , s(driver)
        , m_cooker(driver)
		, m_cube(driver)
		, m_sphere(driver)
		, m_quad(driver)
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
		for (auto o : *node)
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
		m_frame->PushAllState();
		m_frame->SetViewMatrix(node->GetCamera()->GetViewMatrix());
		m_frame->SetProjectionMatrix(node->GetCamera()->GetProjectionMatrix());
		m_frame->SetClipSpace(node->GetCamera()->ToClipSpace());
		result = ApplyToChildren(node);
		m_frame->PopAllState();
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
//		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(0,1,0,1));
//		m_frame->PushAllState();
//		GPU::Renderable* mesh = As<GPU::Renderable*>(node->GetStaticGeometry()->GetGPUBufferCache());
//		if (!mesh)
//		{
//			GPU::StaticMesh* m = nullptr;//	new GPU::OpenGL::StaticMesh();
//			m->Cook(node->GetStaticGeometry());
//			node->GetStaticGeometry()->SetGPUBufferCache(m);
//			mesh = As<GPU::Renderable*>(node->GetStaticGeometry()->GetGPUBufferCache());
//		}

//		m_frame->Render(mesh);
//		m_frame->PopAllState();
		return true;
	}

	bool SimpleRender::Visit(Scene::SkinMeshNode* node)
	{
		m_frame->PushAllState();
		m_frame->EnableSkinning(true);
		GPU::SkinMesh* mesh = nullptr;	// Cast<GPU::OpenGL::SkinMesh*>(node->GetSkinGeometry()->GetGPUBufferCache());
		m_frame->Render(mesh);
		m_frame->PopAllState();
		return true;
	}

	bool SimpleRender::Visit(Scene::ArmatureNode* node)
	{
		bool result = true;
		Virtual::Action::validate();
		m_frame->PushAllState();

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

		m_frame->PopAllState();
		return result;
	}

	bool SimpleRender::Visit(Scene::BoneNode* node)
	{
		bool result = true;
		RenderSphere(node->GetBoundingSphere().GetCenter(), node->GetBoundingSphere().GetRadius(), Math::vec4(1, 1, 0, 1));
		m_frame->PushAllState();

		Virtual::Bone* bone = node->GetBone();
		m_frame->MultWorldMatrix(bone->GetAnimatedGlobalMatrix());
		m_frame->SetBoneMatrix(bone->GetIndex(), m_frame->GetWorldMatrix());

		result = ApplyToChildren(node);

		m_frame->PopAllState();
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
		m_frame->PushAllState();
		auto material = node->GetMaterial();
		m_frame->SetDiffuseColor(material->GetDiffuseColor());

		Virtual::Material* m = node->GetMaterial();
		if (m->GetCache().m_diffuse_texture_cache == nullptr)
			m->GetCache().m_diffuse_texture_cache = nullptr; // m_driver->CreateTexture2D(System::Environment::Instance()->GetTextureFolder() + m->GetDiffuseMap(), true);
		if (m->GetCache().m_normal_texture_cache == nullptr)
			m->GetCache().m_normal_texture_cache = nullptr; // m_driver->CreateTexture2D(System::Environment::Instance()->GetTextureFolder() + m->GetNormalMap(), true);

//		m_frame->SetDiffuseMap0(Cast<GPU::Texture2D*>(m->GetCache().m_diffuse_texture_cache));
//		m_frame->SetBumpMap(Cast<GPU::Texture2D*>(m->GetCache().m_normal_texture_cache));
//		m_frame->SetSpecularColor(material->GetSpecularColor());
//		m_frame->SetSpecularMap(Cast<GPU::Texture2D*>(node->GetMaterial()->GetCache().m_specular_texture_cache));
//		m_frame->SetAmbientColor(material->GetAmbient());
//		m_frame->SetSpecularFactor(material->GetSpecularFactor());

		result = ApplyToChildren(node);

		m_frame->PopAllState();
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
		m_frame->PushAllState();
		m_frame->SetLocalMatrix(node->GetLocalMatrix());
		m_frame->MultWorldMatrix(node->GetLocalMatrix());

		result = ApplyToChildren(node);
		m_frame->PopAllState();

		return result;
	}

	bool SimpleRender::Visit(Scene::LocationIndoorNode* node)
	{
		bool result = true;
		m_frame->PushAllState();
		m_frame->MultWorldMatrix(node->GetLocalMatrix());

		auto pos = m_frame->GetViewMatrix().TranslationPart();
		auto world = m_frame->GetWorldMatrix();
		auto view = m_frame->GetViewMatrix();
		if (Math::ClassifyPoint(world.Inversed() * pos, node->GetConvexShape()) != Math::Relation::INSIDE)
		{
			out_message() << "OUTSIDE" << std::endl;
			for (auto o : *node)
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
		m_frame->PopAllState();
		return result;
	}

    bool SimpleRender::Visit(Scene::PortalNode*)
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
		m_frame->PushAllState();

		auto camera_position = m_frame->GetViewMatrix().Inversed().TranslationPart();
		Math::vec2 terrain_position = node->GetTerrainObserver()->GetTerrainView()->GetPosition();
		Math::vec2 texture_offset(camera_position.X() - terrain_position.X(), camera_position.Z() - terrain_position.Y());
		/*m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(terrain_position.X(), 0, terrain_position.Y()) * Math::mat4::CreateTranslate(texture_offset.X(), 0, texture_offset.Y()));*/

		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(floor(terrain_position.X()), 0, floor(terrain_position.Y())));

    //	static Math::vec3 sun(100, 100, 100);
//		static float angle = 0;

		Virtual::TerrainView* view = node->GetTerrainObserver()->GetTerrainView();
        if (view && view->GetHeightMap())
		{
			//m_tc = m_tc;
			//m_frame->SetTextureMatrix(Math::mat4::CreateIdentity());
			m_frame->SetTextureMatrix(Math::mat4::CreateTranslate(terrain_position.X() / m_grid.GetTotalWidth()
				, terrain_position.Y() / m_grid.GetTotalHeight(), 0));
//			m_frame->SetHeightMap(view->GetHeightMap());
//			m_frame->SetDiffuseMap0(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache));
//			m_frame->SetDiffuseMap1(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_diffuse_texture_cache_2));
//			m_frame->SetBumpMap(Cast<GPU::Texture2D*>(node->GetTerrainObserver()->GetTerrainView()->GetTerrain()->GetMaterial()->GetCache().m_normal_texture_cache));
//			m_frame->EnableWireframe(false);
//			m_frame->EnableDepthTest(true);
//			m_frame->SetLineWidth(1);
//			m_frame->EnableTerrainRendering(true);
//			m_frame->Render(&m_grid);
		}
		m_frame->PopAllState();
		return result;
	}

	void SimpleRender::RenderCube(float width, float height, float depth)
	{
		m_frame->PushAllState();
		//	shift quad
		m_frame->MultWorldMatrix(Math::mat4::CreateScaling(width, height, depth));
		m_frame->SetDiffuseColor(Math::vec4(0,1,0,1));
		m_frame->EnableWireframe(true);
		m_frame->Render(&m_cube);
		m_frame->PopAllState();
	}

	void SimpleRender::RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color)
	{
		m_frame->PushAllState();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(position) * Math::mat4::CreateScaling(radius, radius, radius));
		m_frame->SetDiffuseColor(color);
		m_frame->EnableWireframe(true);
		m_frame->EnableTexturing(false);
		m_frame->EnableDiffuseShading(true);
		m_frame->SetLineWidth(5.0f);
		m_frame->Render(&m_sphere);
		m_frame->PopAllState();
	}

	void SimpleRender::RenderQuad(float x, float y, float width, float height, const Math::vec4& color)
	{
		m_frame->PushAllState();
		//	shift quadSTATE
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(color);
		m_frame->Render(&m_quad);
		m_frame->PopAllState();
	}

	void SimpleRender::RenderTexturedQuad(float x, float y, float width, float height, GPU::Texture2D* texture)
	{
		m_frame->PushAllState();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(2.0f * x - 1, 2.0f * y-1, 0) * Math::mat4::CreateScaling(2.0f*width, 2.0f*height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(Math::vec4(1,1,1,1));
		m_frame->SetTextureMatrix(Math::mat4::CreateReflectY());
		m_frame->EnableWireframe(false);
		m_frame->SetDiffuseMap0(texture);
		m_frame->EnableLighting(false);
		m_frame->EnableTexturing(true);
		m_frame->EnableDiffuseShading(true);
		m_frame->Render(&m_quad);
		m_frame->PopAllState();
	}

    void SimpleRender::RenderText(float x, float y, const System::string& text, const Math::vec4&)
	{
		g_font_builder.SetCharSize(14, 14);
		int len = g_font_builder.CalculateLength(text.Data());
		int h = g_font_builder.CalculateHeight(text.Data());
		s.SetSize(len, h);
		s.SetText(text);

		m_frame->PushAllState();
		float width = 2.0f * len / (float)m_driver->GetWindow()->GetWidth();
		float height = 2.0f * h / (float)m_driver->GetWindow()->GetHeight();
		//	shift quad
		m_frame->SetWorldMatrix(Math::mat4::CreateTranslate(2*x-1.0f, 2*y - 1.0f, 0) * Math::mat4::CreateScaling(width, height, 1));
		m_frame->SetProjectionMatrix(Math::mat4::CreateIdentity());
		m_frame->SetViewMatrix(Math::mat4::CreateIdentity());
		m_frame->SetDiffuseColor(Math::vec4(0,0,1,1));
		m_frame->SetTextColor(Math::vec4(1, 1, 1, 1));
		m_frame->SetTextureMatrix(Math::mat4::CreateReflectY());
		m_frame->SetFontMap(s.GetTexture());
		m_frame->EnableFontRendering(true);
		m_frame->Render(&m_quad);
		m_frame->PopAllState();
	}

	bool SimpleRender::Render()
	{
		m_time += 0.1f;
        //m_rt->Activate();
		m_frame = m_driver->BeginFrame();
		m_frame->BeginRendering();
		if (m_scene)
		{
//			m_rt->SetViewport(m_scene->GetCameraNode()->GetCamera()->GetViewport());
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
			RenderText(0, 0, L"SDFGSDFGS DFGSDFG SDF", Math::vec4(1,1,1,1));
			//GPU::OpenGL::OpenGLPaintEngine* device = Cast<GPU::OpenGL::OpenGLPaintEngine*>(m_paint_engine);
			///RenderTexturedQuad(0, 0, 1, 1, device->GetRenderTarget()->GetColorBuffer());
		}
		m_frame->EndRendering();
		m_driver->EndFrame(m_frame);
//		m_rt->Deactivate();
		return true;
	}

	void SimpleRender::SetScene(Scene::SceneGraph* scene)
	{
		m_terrain_slices = 63;
		m_time = 0;
//		GPU::OpenGL::RenderTargetBackBuffer::RenderTargetBackBufferProperties p;
        m_tc = new GPU::TextureContext;
    //	m_rt = new GPU::OpenGL::RenderTargetBackBuffer;
    //	m_rt->Init(&p);
		m_scene = scene;
		if (m_scene)
			m_scene->GetRootNode()->Apply(&m_cooker);
		m_context = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::BumpMapping);
		m_solid_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::Solid3D);
		m_textured_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::SolidTextured3D);
		m_gui_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::GUI);
		m_skin_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::Skinning);
		m_terrain_rc = GPU::AbstractRenderPolicy::find(GPU::RenderPolicySet::Terrain);
        m_text = new GPU::TextSurface(m_driver);
		m_text->SetSize(int(m_driver->GetWindow()->GetWidth() * 0.5f), int(m_driver->GetWindow()->GetHeight() * 0.5f));
		m_gui_render = new GUIRender(m_driver);
		m_grid.Cook(64, 64, m_terrain_slices, m_terrain_slices, 2);
	}
}
