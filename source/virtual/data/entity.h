#ifndef _H_PUNK_VIRTUAL_ENTITY
#define _H_PUNK_VIRTUAL_ENTITY

#include <memory>

#include "../../config.h"
#include "../../system/hresource.h"
#include "../../system/object.h"

namespace Virtual
{	
	class PUNK_ENGINE_API Entity : public System::Object
	{
	public:
		
		virtual ~Entity();
	protected:
		Entity();

	private:
	};

	typedef Entity* EntityRef;

	//	/*
	//	//System::string m_type;
	//	//System::string m_reference;		
	//	//Math::BoundingBox m_bbox;
	//	//std::auto_ptr<Mesh> m_mesh;
	//	//Math::mat4 m_local_matrix;
	//	//Math::mat4 m_world_matrix;
	//	//Math::vec3 m_location;
	//	//Math::OctTree m_oct_tree;
	//	//AnimationMixer m_animation_Mixer;
	//	//System::string m_material_name;
	//	//Material m_material;
	//	//std::auto_ptr<Sound> m_sound;
	//	//std::auto_ptr<Light> m_light;
	//	//std::auto_ptr<StaticMesh> m_static_mesh;
	//	//std::auto_ptr<SkinMesh> m_skinned_mesh;

	//	//CollisionCollection m_collision;

	//	//
	//	//	RUN TIME STUFF
	//	//		
	//	//Entity* m_ref_object;		//	used if type is proxy
	//	//	for physical simulator
	//	//std::auto_ptr<ShapeBody> m_shape_body;
	//	*/


	//	Entity(const Entity&);
	//	Entity& operator = (const Entity&);

	//public:

	//	Entity();
	//	virtual ~Entity();

	//	

	//	/*void SetType(const System::string& type) { m_type = type; }
	//	const System::string& GetType() const { return m_type; }

	//	Math::BoundingBox& AsBoundingBox() { return m_bbox; }
	//	const Math::BoundingBox& AsBoundingBox() const { return m_bbox; }
	//	
	//	void SetMesh(Mesh* mesh) { m_mesh.reset(mesh); }
	//	Mesh* GetMesh() { return m_mesh.get(); }
	//	const Mesh* GetMesh() const { return m_mesh.get(); }

	//	void SetLocalMatrix(const Math::mat4& value) { m_local_matrix = value; }
	//	Math::mat4& GetLocalMatrix() { return m_local_matrix; }
	//	const Math::mat4& GetLocalMatrix() const { return m_local_matrix; }

	//	void SetWorldMatrix(const Math::mat4& value) { m_local_matrix = value; }
	//	Math::mat4& GetWorldMatrix() { return m_local_matrix; }
	//	const Math::mat4& GetWorldMatrix() const { return m_local_matrix; }

	//	void SetLocation(const Math::vec3& value) { m_location = value; }
	//	Math::vec3& GetLocation() { return m_location; }
	//	const Math::vec3& GetLocation() const { return m_location; }

	//	Math::OctTree& AsOctTree() { return m_oct_tree; }
	//	const Math::OctTree& AsOctTree() const { return m_oct_tree; }*/
	//	//				
	//	//AnimationMixer& AsAnimationMixer() { return m_animation_Mixer; }
	//	//const AnimationMixer& AsAnimationMixer() const { return m_animation_Mixer; }

	//	//const System::string& GetMaterialName() const { return m_material_name; }
	//	//void SetMaterialName(const System::string& name) { m_material_name = name; }

	//	//Material& GetMaterial() { return m_material; }
	//	//const Material& GetMaterial() const { return m_material; }

	//	//void SetMaterial(const Material& value) { m_material = value; }

	//	//bool IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res) const;

	//	//Sound* GetSound() { return m_sound.get(); }
	//	//const Sound* GetSound() const { return m_sound.get(); }
	//	//void SetSound(Sound* snd) { m_sound.reset(snd); }

	//	//void SetReferenceObjectName(const System::string& ref) { m_reference = ref; }
	//	//const System::string& GetReferenceObjectName() const { return m_reference; }
	//	//System::string& GetReferenceObjectName() { return m_reference; }

	//	//void SetReferenceObject(Entity* obj) { m_ref_object = obj; }
	//	//const Entity* GetReferenceObject() const { return m_ref_object; }
	//	//Entity* GetReferenceObject() { return m_ref_object; }

	//	////	if has bone weights than cook skinned mesh, other wise cooks static
	//	//bool CookAsStaticMesh();
	//	//bool CookAsSkinnedMesh(Armature& armrature);		
	//	//void CookOneVertexWithBone(Armature& armature, int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4);

	//	//void BuildOctTree();

	//	//SkinMesh* GetSkinnedMesh() { return m_skinned_mesh.get(); }
	//	//const SkinMesh* GetSkinnedMesh() const { return m_skinned_mesh.get(); }

	//	//StaticMesh* GetStaticMesh() { return m_static_mesh.get(); }
	//	//const StaticMesh* GetStaticMesh() const { return m_static_mesh.get(); }
	//	//
	//	//bool IsCollisionVolume() const;

	//	//bool IsStaticMesh() const  { return m_static_mesh.get() != 0; }
	//	//bool IsSkinnedMesh() const { return m_skinned_mesh.get() != 0; }
	//	//bool IsLight() const { return m_light.get() != 0; }
	//	//bool IsSound() const { return m_sound.get() != 0; }
	//	//bool IsMesh() const { return m_mesh.get() != 0; }
	//	//bool IsProxy() const { return m_type == L"proxy"; }

	//	//void SetLight(Light* light) { m_light.reset(light); }
	//	//Light* GetLight() { return m_light.get(); }
	//	//const Light* GetLight() const { return m_light.get(); }

	//	////	test collision of bbox with all collision objects
	//	////	bbox is in world coordinates
	//	//bool TestCollision(const Math::BoundingBox& bbox) const;

	//	//void SetShapeBody(ShapeBody* body)  { m_shape_body.reset(body); }
	//	//ShapeBody* GetShapeBody() { return m_shape_body.get(); }
	//	//const ShapeBody* GetShapeBody() const { return m_shape_body.get(); }

	//private:

	////	bool TestCollision(const Math::BoundingBox& bbox, const Math::mat4& parent, const Entity& child) const;
	////	void UpdateCollision();
	////	void UpdateProxy(Entity* object);

	//};
}

#endif	//	_H_PUNK_VIRTUAL_ENTITY