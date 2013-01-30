#ifndef _H_PUNK_OPENGL_MODULE_GRID_OBJECT
#define _H_PUNK_OPENGL_MODULE_GRID_OBJECT

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE GridObject : public VertexArrayObject2<GL_TRIANGLES, COMPONENT_POSITION|
			COMPONENT_NORMAL|
			COMPONENT_TEXTURE|
			COMPONENT_FLAG>
		{
			enum { PrimitiveType = GL_TRIANGLES };
			enum { VertexType = COMPONENT_POSITION|
				COMPONENT_NORMAL|
				COMPONENT_TEXTURE|
				COMPONENT_FLAG};

		public:

			GridObject::GridObject() {}

			virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices);

		private:
			GridObject(const GridObject& quad);
			GridObject& operator = (const GridObject& quad);
		};
	}
}
#endif