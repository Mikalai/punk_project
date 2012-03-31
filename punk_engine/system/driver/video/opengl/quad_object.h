#ifndef _H_PUNK_OPENGL_MODULE_QUAD_OBJECT
#define _H_PUNK_OPENGL_MODULE_QUAD_OBJECT

#include "vertex_array_object.h"

namespace OpenGL
{
	struct QuadObjectImpl;

	class MODULE_OPENGL QuadObject : public VertexArrayObject
	{
	public:
		QuadObject();
		QuadObject(const QuadObject& quad);
		QuadObject& operator = (const QuadObject& quad);

		void SetWidth(float width);
		void SetHeight(float height);

	protected:
		virtual void Cook();
	};
}

#endif