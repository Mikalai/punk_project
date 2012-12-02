#ifndef _H_PUNK_SCENE_VISITOR
#define _H_PUNK_SCENE_VISITOR

namespace Scene
{
	class CameraNode;
	class GeometryNode;
	class LightNode;
	class MaterialNode;
	class Node;
	class TransformNode;
	class LocationIndoorNode;
	class PortalNode;

	class AbstractVisitor
	{
	public:
		virtual bool Visit(CameraNode* node) = 0;
		virtual bool Visit(GeometryNode* node) = 0;
		virtual bool Visit(LightNode* node) = 0;
		virtual bool Visit(MaterialNode* node) = 0;
		virtual bool Visit(Node* node) = 0;
		virtual bool Visit(TransformNode* node) = 0;
		virtual bool Visit(LocationIndoorNode* node) = 0;		
		virtual bool Visit(PortalNode* node) = 0;
	};
}

#endif