#ifndef _H_BULLET_RIGID_BODY
#define _H_BULLET_RIGID_BODY

#include "../../math/mat4.h"

class btCollisionObject;
class btRigidBody;

namespace Physics
{
	class BulletShapeBody;

	struct RigidBodyDesc
	{
		Math::mat4 m_initial_position;
		float m_mass;
		BulletShapeBody* m_shape;
		short m_group;
		short m_mask;
		bool m_is_character;

		RigidBodyDesc() : m_is_character(false) {}
			
	};

	class PUNK_ENGINE BulletRigidBody 
	{
		btRigidBody* m_rigid_body;
		btDiscreteDynamicsWorld* m_world;

	public:				
		virtual void Init(RigidBodyDesc& desc);
		virtual ~BulletRigidBody();

		btRigidBody* GetRigidBody() { return m_rigid_body; }
		const btRigidBody* GetRigidBody() const { return m_rigid_body; }

		void EnterWorld(btDiscreteDynamicsWorld* world);
		void LeaveWorld();

		//virtual void SetObject(Object* object);
		//virtual Object* GetObject(Object* object) { return m_object; }
		//virtual const Object* GetObject(Object* object) const { return m_object; }
		//virtual const Math::mat4 GetLocation() const;
		//virtual void SetLocation(const Math::Matrix4x4<float>& m);
	private:
		void Update();
		void Clear();
		void Init();
	};
}

#endif	//	_H_BULLET_RIGID_BODY