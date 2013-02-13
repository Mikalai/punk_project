#ifndef _H_PUNK_SCENE_VISITOR
#define _H_PUNK_SCENE_VISITOR

namespace Scene
{
	class CameraNode;
	class StaticMeshNode;
	class SkinMeshNode;
	class LightNode;
	class MaterialNode;
	class Node;
	class TransformNode;
	class LocationIndoorNode;
	class PortalNode;
	class ArmatureNode;
	class BoneNode;
	class DebugTextureViewNode;
	class TerrainNode;

	class PUNK_ENGINE AbstractVisitor
	{
	public:
		virtual bool Visit(CameraNode* node) = 0;
		virtual bool Visit(StaticMeshNode* node) = 0;
		virtual bool Visit(SkinMeshNode* node) = 0;
		virtual bool Visit(ArmatureNode* node) = 0;
		virtual bool Visit(LightNode* node) = 0;
		virtual bool Visit(MaterialNode* node) = 0;
		virtual bool Visit(Node* node) = 0;
		virtual bool Visit(TransformNode* node) = 0;
		virtual bool Visit(LocationIndoorNode* node) = 0;		
		virtual bool Visit(PortalNode* node) = 0;
		virtual bool Visit(BoneNode* node) = 0;
		virtual bool Visit(TerrainNode* node) = 0;
		virtual bool Visit(DebugTextureViewNode* node) { return true; }		
	};
}

#endif