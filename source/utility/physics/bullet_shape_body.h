#ifndef _H_BULLET_SHAPE_BODY
#define _H_BULLET_SHAPE_BODY

#include "shape_body.h"

class btCollisionShape;

namespace Utility
{
	class BulletShapeBody : public ShapeBody
	{
		btCollisionShape* m_shape;
	public: 
		void SetCollisionShape(btCollisionShape* shape) { m_shape = shape; }
		btCollisionShape* GetCollisionShape() { return m_shape; }
		const btCollisionShape* GetCollisionShape() const { return m_shape; }
	};
}
#endif