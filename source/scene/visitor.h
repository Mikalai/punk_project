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
	class TextureViewNode;
	class TerrainNode;

    class AbstractVisitor
	{
	public:
        virtual bool Visit(CameraNode*) = 0;
        virtual bool Visit(StaticMeshNode*) = 0;
        virtual bool Visit(SkinMeshNode*) = 0;
        virtual bool Visit(ArmatureNode*) = 0;
        virtual bool Visit(LightNode*) = 0;
        virtual bool Visit(MaterialNode*) = 0;
        virtual bool Visit(Node*) = 0;
        virtual bool Visit(TransformNode*) = 0;
        virtual bool Visit(LocationIndoorNode*) = 0;
        virtual bool Visit(PortalNode*) = 0;
        virtual bool Visit(BoneNode*) = 0;
        virtual bool Visit(TerrainNode*) = 0;
        virtual bool Visit(TextureViewNode*) = 0;
	};
}

#endif
