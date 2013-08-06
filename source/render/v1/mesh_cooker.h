//#ifndef _H_PUNK_OPENGL_RENDER_V1_MESH_COOKER
//#define _H_PUNK_OPENGL_RENDER_V1_MESH_COOKER

//#include <vector>
//#include "../../config.h"
//#include "../../scene/interface.h"
//#include "../../virtual/interface.h"
//#include "../../system/smart_pointers/module.h"

//namespace Gpu
//{
//    class VideoDriver;
//}

//namespace Render
//{
//	class PUNK_ENGINE_API MeshCooker : public Scene::AbstractVisitor
//	{
//	public:
//        MeshCooker(Gpu::VideoDriver* driver);
//        virtual bool Visit(Scene::CameraNode*);
//        virtual bool Visit(Scene::StaticMeshNode*);
//        virtual bool Visit(Scene::SkinMeshNode*);
//        virtual bool Visit(Scene::ArmatureNode*);
//        virtual bool Visit(Scene::LightNode*);
//        virtual bool Visit(Scene::MaterialNode*);
//        virtual bool Visit(Scene::Node*);
//        virtual bool Visit(Scene::TransformNode*);
//        virtual bool Visit(Scene::LocationIndoorNode*);
//        virtual bool Visit(Scene::PortalNode*);
//        virtual bool Visit(Scene::BoneNode*);
//        virtual bool Visit(Scene::TerrainNode*);
//        virtual bool Visit(Scene::TextureViewNode*) { return true; }

//		//	this data should not be deleted
//		std::vector<Virtual::Light*> m_light_set;
//		Virtual::Armature* m_current_armature;
//        Gpu::VideoDriver* m_video_driver;
//	};
//}

//#endif	//	_H_PUNK_OPENGL_RENDER_V1_MESH_COOKER
