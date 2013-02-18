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
		SimpleRender(GPU::OpenGL::Driver* driver);
		~SimpleRender();
		bool Render();
		void SetGUIHud(GUI::Widget* root) { m_root = root; }
		void SetScene(Scene::SceneGraph* scene);
		void SetPainter(GPU::Painter* value) { m_painter = value; }

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
		void RenderTexturedQuad(float x, float y, float width, float height, GPU::OpenGL::Texture2D* texture);
		void RenderText(float x, float y, const System::string& text, const Math::vec4& color);
		void RenderCube(float width, float height, float depth);
		void RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color = Math::vec4(1,1,1,1));

	private:
		void Clear();

	private:
		MeshCooker m_cooker;
		GPU::OpenGL::ScaledGridObject m_grid;
		float m_time;
		int m_terrain_slices;
		System::StateManager<GPU::CoreState> m_states;		

		//	next pointers should be destroyed in destructor
		GPU::RenderTarget* m_rt;				
		GPU::OpenGL::TextSurface* m_text;
		GPU::OpenGL::TextureContext* m_tc;
		GUIRender* m_gui_render;
		GPU::Painter* m_painter;

		// next pointers should not be delete in destructor
		GPU::OpenGL::Driver* m_driver;
		GUI::Widget* m_root;
		Scene::SceneGraph* m_scene;		
		GPU::AbstractRenderPolicy* m_skin_rc;
		GPU::AbstractRenderPolicy* m_context;
		GPU::AbstractRenderPolicy* m_solid_rc;
		GPU::AbstractRenderPolicy* m_textured_rc;
		GPU::AbstractRenderPolicy* m_gui_rc;
		GPU::AbstractRenderPolicy* m_terrain_rc;
	};
}

#endif	//	_H_PUNK_RENDER_SIMPLE_RENDER