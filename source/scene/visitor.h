#ifndef _H_PUNK_SCENE_VISITOR
#define _H_PUNK_SCENE_VISITOR

namespace Scene
{
    class ArmatureNode;
    class BoneNode;
    class BoundingVolumeUpdater;
    class CameraNode;
    class DefaultVisitor;
    class GeometryNode;
    class LightNode;
    class LocationIndoorNode;
    class MaterialNode;
    class Node;
    class PointLightNode;
    class PortalNode;
    class SceneGraph;
    class SkinMeshNode;
    class StaticMeshNode;
    class TerrainNode;
    class TransformNode;
    class SunNode;
    class PathNode;
    class NaviMeshNode;
    class RiverNode;
    class TextureViewNode;

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
        virtual bool Visit(SunNode*) = 0;
        virtual bool Visit(PathNode*) = 0;
        virtual bool Visit(NaviMeshNode*) = 0;
        virtual bool Visit(RiverNode*) = 0;
	};
}

#endif  //  _H_PUNK_SCENE_VISITOR
