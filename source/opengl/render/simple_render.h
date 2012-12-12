#ifndef _H_PUNK_OPENGL_SIMPLE_RENDER
#define _H_PUNK_OPENGL_SIMPLE_RENDER

#include "../../config.h"
#include "../../scene/visitor.h"
#include "render_state.h"
#include "../render_context/render_contexts.h"
#include "render_target.h"

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
		virtual bool Visit(Scene::GeometryNode* node);
		virtual bool Visit(Scene::LightNode* node);
		virtual bool Visit(Scene::MaterialNode* node);
		virtual bool Visit(Scene::Node* node);
		virtual bool Visit(Scene::TransformNode* node);
		virtual bool Visit(Scene::LocationIndoorNode* node);		
		virtual bool Visit(Scene::PortalNode* node);

		System::Proxy<Virtual::LightSet> m_light_set;
	};

	class PUNK_ENGINE SimpleRender : public Scene::AbstractVisitor
	{
	public:
		
		bool Render();
		void SetScene(System::Proxy<Scene::SceneGraph> scene);

		virtual bool Visit(Scene::CameraNode* node);
		virtual bool Visit(Scene::GeometryNode* node);
		virtual bool Visit(Scene::LightNode* node);
		virtual bool Visit(Scene::MaterialNode* node);
		virtual bool Visit(Scene::Node* node);
		virtual bool Visit(Scene::TransformNode* node);
		virtual bool Visit(Scene::LocationIndoorNode* node);		
		virtual bool Visit(Scene::PortalNode* node);

		void RenderQuad(float x, float y, float width, float height, const Math::vec4& color);
		void RenderTexturedQuad(float x, float y, float width, float height, System::Proxy<Texture2D> texture);
		void RenderText(float x, float y, const System::string& text, const Math::vec4& color);

	private:
		RenderTarget* m_rt;
		System::Proxy<Scene::SceneGraph> m_scene;
		MeshCooker m_cooker;
		System::Proxy<RenderContextBumpMapping> m_context;
		System::Proxy<RenderContextSolid3D> m_solid_rc;
		System::Proxy<RenderContextSolidTexture3D> m_textured_rc;
		System::Proxy<RenderContextGUI> m_gui_rc;
		System::Proxy<TextureContext> m_tc;
		System::Proxy<TextSurface> m_text;
		StateManager m_states;
	};
}

#endif	//	_H_PUNK_OPENGL_SIMPLE_RENDER