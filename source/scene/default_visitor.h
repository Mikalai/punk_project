#ifndef _H_PUNK_SCENE_DEFAULT_VISITOR
#define _H_PUNK_SCENE_DEFAULT_VISITOR

#include "../config.h"
#include "visitor.h"

namespace Scene
{
	class PUNK_ENGINE DefaultVisitor : public AbstractVisitor
	{
	public:
		DefaultVisitor();

		virtual bool Visit(CameraNode* node);
		virtual bool Visit(GeometryNode* node);
		virtual bool Visit(LightNode* node);
		virtual bool Visit(MaterialNode* node);
		virtual bool Visit(Node* node);
		virtual bool Visit(TransformNode* node);
		virtual bool Visit(LocationIndoorNode* node);		
		virtual bool Visit(PortalNode* node);

	private:
		int m_level;
	};
}

#endif	//	_H_PUNK_SCENE_DEFAULT_VISITOR