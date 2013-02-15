#ifndef _H_PUNK_VIRTUAL_OBJECTS_SIMPLE_CUBE
#define _H_PUNK_VIRTUAL_OBJECTS_SIMPLE_CUBE

#include "../../../math/vec3.h"
#include "../../../system/object.h"
#include "../../../scene/scene_graph_adapter.h"
#include "../../../physics/bullet/bullet_adapter.h"

namespace Virtual
{
	class Geometry;

	class PUNK_ENGINE Cube : public System::Object, public Scene::SceneGraphAdapter, public Physics::BulletAdapter
	{
	public:
		Cube();
		virtual ~Cube();
		void SetGeometry(Geometry* geom);
		Geometry* GetGeometry();
		void SetMass(float mass);
		float GetMass() const;
		void SetDimensions(const Math::vec3& value);
		const Math::vec3 GetDimensions() const;

		virtual void OnEnterSceneGraph(Scene::SceneGraph* graph, Scene::Node* node) override;
		virtual void OnLeaveSceneGraph(Scene::SceneGraph* graph) override;
		virtual void OnEnterVisibility() override;
		virtual void OnLostVisibility() override;

		virtual void EnterPhysicalSimulator(Physics::BulletSimulator* value) override;
		virtual void LeavePhysicalSimulator() override;
		virtual void SetTransform(const Math::mat4& value) override;
		virtual void GetTransform(Math::mat4& value) override;

		struct CubeImpl;
		CubeImpl* impl;

	private:
		Cube(const Cube&);
		Cube& operator = (const Cube&);
	};
}

#endif	//	_H_PUNK_VIRTUAL_OBJECTS_SIMPLE_CUBE