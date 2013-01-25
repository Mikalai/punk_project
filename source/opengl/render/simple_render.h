#ifndef _H_PUNK_OPENGL_SIMPLE_RENDER
#define _H_PUNK_OPENGL_SIMPLE_RENDER

#include "../../config.h"
#include "../../scene/visitor.h"
#include "render_state.h"
#include "../render_context/render_contexts.h"
#include "../renderable/renderable_data.h"
#include "render_target.h"
#include "../../gui/widget.h"
#include "../../system/state_manager.h"
#include "ogl_gui_render.h"

namespace Scene { class SceneGraph; }

namespace OpenGL
{
	class Texture2D;
	class TextSurface;

	class PUNK_ENGINE MeshCooker : public Scene::AbstractVisitor
	{
	public:
		MeshCooker();
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
		virtual bool Visit(Scene::DebugTextureViewNode* node) { return true; };

		std::vector<System::Proxy<Virtual::Light>> m_light_set;
		System::Proxy<Virtual::Armature> m_current_armature;
	};

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
		void RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<Texture2D> texture);
		void RenderText(float x, float y, const System::string& text, const Math::vec4& color);
		void RenderCube(float width, float height, float depth);
		void RenderSphere(const Math::vec3& position, float radius, const Math::vec4& color = Math::vec4(1,1,1,1));

	private:
		RenderTarget* m_rt;
		System::Proxy<Scene::SceneGraph> m_scene;
		MeshCooker m_cooker;
		System::Proxy<RenderContextSkinning> m_skin_rc;
		System::Proxy<RenderContextBumpMapping> m_context;
		System::Proxy<RenderContextSolid3D> m_solid_rc;
		System::Proxy<RenderContextSolidTexture3D> m_textured_rc;
		System::Proxy<RenderContextGUI> m_gui_rc;
		System::Proxy<RenderContextTerrain> m_terrain_rc;
		System::Proxy<TextureContext> m_tc;
		System::Proxy<TextSurface> m_text;		
		System::StateManager<CoreState> m_states;
		System::Proxy<GUI::Widget> m_root;
		System::Proxy<GUIRender> m_gui_render;
		OpenGL::ScaledGridObject m_grid;
		float m_time;
		int m_terrain_slices;
	};
}

#endif	//	_H_PUNK_OPENGL_SIMPLE_RENDER