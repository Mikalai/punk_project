#ifndef _H_PUNK_SCENE_DEFAULT_VISITOR
#define _H_PUNK_SCENE_DEFAULT_VISITOR

#include "../config.h"
#include "visitor.h"

namespace Scene
{
	class PUNK_ENGINE_API DefaultVisitor : public AbstractVisitor
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
		virtual bool Visit(BoneNode* node) = 0;
		virtual bool Visit(TerrainNode* node) = 0;
	private:
		int m_level;		
	};
}

#endif	//	_H_PUNK_SCENE_DEFAULT_VISITOR