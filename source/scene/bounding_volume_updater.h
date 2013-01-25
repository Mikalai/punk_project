#ifndef _H_PUNK_SCENE_BOUNDING_VOLUME_UPDATER
#define _H_PUNK_SCENE_BOUNDING_VOLUME_UPDATER

#include "../config.h"
#include "visitor.h"
#include "../system/smart_pointers/proxy.h"
#include "../math/bounding_shere.h"
#include "../system/state_manager.h"

namespace Virtual { class Armature; }

namespace Scene
{	
	class SceneGraph;

	class PUNK_ENGINE BoundingVolumeUpdater : public AbstractVisitor
	{
	public:
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
		virtual bool Visit(BoneNode* node);
		virtual bool Visit(TerrainNode* node);
		void SetScene(System::Proxy<SceneGraph> value);
		void Update();

	private:

		struct BoundingVolumeState
		{
			Math::mat4 m_local;
			Math::mat4 m_armature_world;
			Math::BoundingSphere m_sphere;
			System::Proxy<Virtual::Armature> m_armature;			
		};

		System::StateManager<BoundingVolumeState> m_states;
		System::Proxy<SceneGraph> m_scene;
	};
}

#endif	//	_H_PUNK_SCENE_BOUNDING_VOLUME_UPDATER