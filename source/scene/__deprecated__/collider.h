#ifndef _H_PUNK_SCENE_COLLIDER
#define _H_PUNK_SCENE_COLLIDER

#include "../config.h"
#include "visitor.h"
#include "../system/state_manager.h"
#include "../math/mat4.h"
#include "../math/bounding_shere.h"

namespace Scene
{
	class SceneGraph;

	class PUNK_ENGINE_API Collider: public AbstractVisitor
	{
	public:
		
		struct CollisionResult
		{
			std::vector<Scene::Node*> m_nodes;
		};

		Collider();
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
		void SetScene(SceneGraph* value);
		const CollisionResult Run(const Math::BoundingSphere& sphere);

	private:

		struct State
		{
			Math::mat4 m_local;
			Math::mat4 m_armature_world;
			Math::BoundingSphere m_sphere;			
			Virtual::Armature* m_armature;
		};

		Math::BoundingSphere m_current_sphere;
		CollisionResult m_result;
		System::StateManager<State> m_states;
		//	should not be deleted
		SceneGraph* m_scene;
	};
}

#endif	//	_H_PUNK_SCENE_COLLIDER