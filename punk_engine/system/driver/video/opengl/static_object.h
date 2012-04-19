#ifndef _H_PUNK_OPENGL_MODULE_STATIC_OBJECT
#define _H_PUNK_OPENGL_MODULE_STATIC_OBJECT

#include "vertex_array_object.h"

namespace Utility
{
	class StaticMesh;
}

namespace OpenGL
{
	struct StaticObjectImpl;

	class MODULE_OPENGL StaticObject : public VertexArrayObject
	{
	public:
		StaticObject();
		StaticObject(const StaticObject& quad);
		StaticObject& operator = (const StaticObject& quad);

		void SetStaticObject(Utility::StaticMesh* object);

	protected:
		virtual void Cook();		
	};
}

#endif