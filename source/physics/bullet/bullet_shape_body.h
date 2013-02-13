#ifndef _H_BULLET_SHAPE_BODY
#define _H_BULLET_SHAPE_BODY

#include "../../system/object.h"

namespace Virtual { class Geometry; }

class btCollisionShape;

namespace Physics
{
	class PUNK_ENGINE BulletShapeBody : public System::Object
	{
		btCollisionShape* m_shape;
	public: 
		virtual ~BulletShapeBody();
		virtual void InitConvexHull(Virtual::Geometry* geom, bool auto_cache = true);
		virtual void InitBox(float dim_x, float dim_y, float dim_z);
		virtual void InitSphere(float radius);
		virtual void InitPlain(float height);
		btCollisionShape* GetCollisionShape() { return m_shape; }
		const btCollisionShape* GetCollisionShape() const { return m_shape; }
	};
}

#endif	//	_H_BULLET_SHAPE_BODY