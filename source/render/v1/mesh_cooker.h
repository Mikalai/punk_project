#ifndef _H_PUNK_OPENGL_RENDER_V1_MESH_COOKER
#define _H_PUNK_OPENGL_RENDER_V1_MESH_COOKER

#include <vector>
#include "../../config.h"
#include "../../scene/interface.h"
#include "../../virtual/interface.h"
#include "../../system/smart_pointers/module.h"

namespace Render
{
	class PUNK_ENGINE MeshCooker : public Scene::AbstractVisitor
	{
	public:
		MeshCooker();
		virtual bool Visit(Scene::CameraNode* node);
		virtual bool Visit(Scene::StaticMeshNode* node);
		virtual bool Visit(Scene::SkinMeshNode* node);
		virtual bool Visit(Scene::ArmatureNode* node);
		virtual bool Visit(Scene::LightNode* node);
		virtual bool Visit(Scene::MaterialNode* node);
		virtual bool Visit(Scene::Node* node);
		virtual bool Visit(Scene::TransformNode* node);
		virtual bool Visit(Scene::LocationIndoorNode* node);		
		virtual bool Visit(Scene::PortalNode* node);
		virtual bool Visit(Scene::BoneNode* node);
		virtual bool Visit(Scene::TerrainNode* node);
		virtual bool Visit(Scene::TextureViewNode* node) { return true; };

		//	this data should not be deleted
		std::vector<Virtual::Light*> m_light_set;
		Virtual::Armature* m_current_armature;
	};
}

#endif	//	_H_PUNK_OPENGL_RENDER_V1_MESH_COOKER