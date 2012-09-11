#ifndef _H_BULLET_RIGID_BODY
#define _H_BULLET_RIGID_BODY

#include "rigid_body.h"

class btCollisionObject;

namespace Utility
{
	class Object;

	class BulletRigidBody : public RigidBody
	{
		btCollisionObject* m_rigid_body;	

		Object* m_object;
	public:		

		void SetCollisionObject(btCollisionObject* body) { m_rigid_body = body; }
		btCollisionObject* GetCollisionObject() { return m_rigid_body; }
		const btCollisionObject* GetCollisionObject() const { return m_rigid_body; }		

	public:
		virtual void SetObject(Object* object);
		virtual Object* GetObject(Object* object) { return m_object; }
		virtual const Object* GetObject(Object* object) const { return m_object; }
		virtual const Math::mat4 GetLocation() const;
		virtual void SetLocation(const Math::Matrix4x4<float>& m);
	private:
		void Update();
		void Clear();
		void Init();
	};
}

#endif	//	_H_BULLET_RIGID_BODY