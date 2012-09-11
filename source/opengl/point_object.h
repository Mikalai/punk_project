#ifndef _H_PUNK_OPENGL_MODULE_POINT_OBJECT
#define _H_PUNK_OPENGL_MODULE_POINT_OBJECT

#include "vertex_array_object.h"

namespace Math
{
	template<class T> class Vector3;
}

namespace OpenGL
{
	struct PointObjectImpl;

	class PUNK_ENGINE PointObject : public VertexArrayObject
	{
	public:
		PointObject();
		PointObject(const PointObject&);
		PointObject& operator = (const PointObject& object);

		void SetSize(float size);
		void SetPosition(const Math::Vector3<float>& pos);
	protected:
		virtual void Cook();		
	};
}

#endif