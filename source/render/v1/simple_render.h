#ifndef _H_PUNK_RENDER_SIMPLE_RENDER
#define _H_PUNK_RENDER_SIMPLE_RENDER

#include "../../config.h"
#include "../../gpu/module.h"
#include "../../scene/visitor.h"
#include "../../gui/widget.h"
#include "../../system/state_manager.h"
#include "mesh_cooker.h"
#include "ogl_gui_render.h"

namespace Scene { class SceneGraph; }

namespace Render
{
	class PUNK_ENGINE SimpleRender : public Scene::AbstractVisitor
	{
	public:
		
		bool Render();
		void SetGUIHud(System::Proxy<GUI::Widget> root) { m_root = root; }
		void SetScene(System::Proxy<Scene::SceneGraph> scene);

		virtual bool Visit(Scene::CameraNode* node);
		virtual bool Visit(Scene::StaticMeshNode* node);
		virtual bool Visit(Scene::SkinMeshNode* node);
		virtual bool Visit(Scene::ArmatureNode* node);
		virtual bool Visit(Scene::LightNode* node);
		virtual bool Visit(Scene::MaterialNode* node);
		virtual bool Visit(Scene::Node* node);
		virtual bool Visit(Scene::TransformNode* node);
		virtual bool Visit(Scene::LocationIndoorNode* node);		
		virtual bool Visit(Scene::PortalNode* node);
		virtual bool Visit(Scene::BoneNode* node);
		virtual bool Visit(Scene::TerrainNode* node);
		virtual bool Visit(Scene::DebugTextureViewNode* node);

		void RenderQuad(float x, float y, float width, float height, const Math::vec4& color);
		void RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<GPU::OpenGL::Texture2D> texture);
		void RenderText(float x, float y, const System::string& text, const Math::vec4& color);
		void RenderCube(float width, float height, float depth);
		void RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color = Math::vec4(1,1,1,1));

	private:
		System::Proxy<GPU::RenderTarget> m_rt;
		System::Proxy<Scene::SceneGraph> m_scene;
		MeshCooker m_cooker;
		System::Proxy<GPU::AbstractRenderPolicy> m_skin_rc;
		System::Proxy<GPU::AbstractRenderPolicy> m_context;
		System::Proxy<GPU::AbstractRenderPolicy> m_solid_rc;
		System::Proxy<GPU::AbstractRenderPolicy> m_textured_rc;
		System::Proxy<GPU::AbstractRenderPolicy> m_gui_rc;
		System::Proxy<GPU::AbstractRenderPolicy> m_terrain_rc;
		System::Proxy<GPU::OpenGL::TextureContext> m_tc;
		System::Proxy<GPU::OpenGL::TextSurface> m_text;		
		System::StateManager<GPU::CoreState> m_states;
		System::Proxy<GUI::Widget> m_root;
		System::Proxy<GUIRender> m_gui_render;
		GPU::OpenGL::ScaledGridObject m_grid;
		float m_time;
		int m_terrain_slices;
	};
}

#endif	//	_H_PUNK_RENDER_SIMPLE_RENDER