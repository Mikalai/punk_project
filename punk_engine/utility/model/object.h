#ifndef _H_PUNK_UTILITY_OBJECT
#define _H_PUNK_UTILITY_OBJECT

#include <memory>
#include "../config.h"
#include "mesh.h"
#include "../../math/mat4.h"
#include "../../math/bounding_box.h"
#include "../../math/oct_tree.h"
#include "intersection.h"

namespace Utility
{
	class LIB_UTILITY Object
	{
	public:
		typedef std::vector<std::shared_ptr<Object>> Collection;
	private:
		Object* m_parent;
		Collection m_children;
		System::string m_name;
		Math::BoundingBox m_bbox;
		std::auto_ptr<Mesh> m_mesh;
		Math::mat4 m_local_matrix;
		Math::mat4 m_world_matrix;
		Math::vec3 m_location;
		Math::OctTree m_oct_tree;
		AnimationMixer m_animation_mixer;
		Object(const Object&);
		Object& operator = (const Object&);

	public:

		Object();

		void SetParent(Object* obj) { m_parent = obj; }
		Object* GetParent() { return m_parent; }
		const Object* GetParent() const { return m_parent; }

		Collection& GetChildren() { return m_children; }
		const Collection& GetChildren() const { return m_children; }
		
		Object* GetChild(int index) { return m_children[index].get(); }
		const Object* GetChild(int index) const { return m_children[index].get(); }
		Object* GetChild(const System::string& name);
		const Object* GetChild(const System::string& name) const;
		int GetChildIndex(const System::string& name);

		const System::string& GetName() { return m_name; }
		void SetName(const System::string& name) { m_name = name; }

		Math::BoundingBox& AsBoundingBox() { return m_bbox; }
		const Math::BoundingBox& AsBoundingBox() const { return m_bbox; }

		void SetMesh(Mesh* mesh) { m_mesh.reset(mesh); }
		Mesh* GetMesh() { return m_mesh.get(); }
		const Mesh* GetMesh() const { return m_mesh.get(); }

		void SetLocalMatrix(const Math::mat4& value) { m_local_matrix = value; }
		Math::mat4& GetLocalMatrix() { return m_local_matrix; }
		const Math::mat4& GetLocalMatrix() const { return m_local_matrix; }

		void SetWorldMatrix(const Math::mat4& value) { m_local_matrix = value; }
		Math::mat4& GetWorldMatrix() { return m_local_matrix; }
		const Math::mat4& GetWorldMatrix() const { return m_local_matrix; }

		void SetLocation(const Math::vec3& value) { m_location = value; }
		Math::vec3& GetLocation() { return m_location; }
		const Math::vec3& GetLocation() const { return m_location; }

		Math::OctTree& AsOctTree() { return m_oct_tree; }
		const Math::OctTree& AsOctTree() const { return m_oct_tree; }
		
		void AddChild(Object* child) { m_children.push_back(std::shared_ptr<Object>(child)); }
		
		AnimationMixer& AsAnimationMixer() { return m_animation_mixer; }
		const AnimationMixer& AsAnimationMixer() const { return m_animation_mixer; }

		bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res) const;

	};
}

#endif