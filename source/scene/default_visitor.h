#ifndef _H_PUNK_SCENE_DEFAULT_VISITOR
#define _H_PUNK_SCENE_DEFAULT_VISITOR

#include "../config.h"
#include "visitor.h"
#include "../opengl/render/render_state.h"
namespace Scene
{
	class PUNK_ENGINE DefaultVisitor : public AbstractVisitor
	{
	public:
		DefaultVisitor();

		virtual bool Visit(CameraNode* node);
		virtual bool Visit(StaticMeshNode* node);
		virtual bool Visit(SkinMeshNode* node);
		virtual bool Visit(ArmatureNode* node);
		virtual bool Visit(LightNode* node);
		virtual bool Visit(MaterialNode* node);
		virtual bool Visit(Node* node);
		virtual bool Visit(TransformNode* node);
		virtual bool Visit(LocationIndoorNode* node);		
		virtual bool Visit(PortalNode* node);

	private:
		int m_level;
		OpenGL::StateManager m_state_manager;
	};
}

#endif	//	_H_PUNK_SCENE_DEFAULT_VISITOR