#ifndef _H_PUNK_OPENGL_SIMPLE_RENDER
#define _H_PUNK_OPENGL_SIMPLE_RENDER

#include "../../config.h"
#include "../../scene/visitor.h"
#include "render_state.h"

namespace OpenGL
{
	class PUNK_ENGINE SimpleRender : public Scene::AbstractVisitor
	{
	public:
		virtual bool Visit(Scene::CameraNode* node);
		virtual bool Visit(Scene::GeometryNode* node);
		virtual bool Visit(Scene::LightNode* node);
		virtual bool Visit(Scene::MaterialNode* node);
		virtual bool Visit(Secne::Node* node);
		virtual bool Visit(Scene::TransformNode* node);
		virtual bool Visit(Scene::LocationIndoorNode* node);		
		virtual bool Visit(Scene::PortalNode* node);
	private:
		StateManager m_states;
	};
}

#endif	//	_H_PUNK_OPENGL_SIMPLE_RENDER