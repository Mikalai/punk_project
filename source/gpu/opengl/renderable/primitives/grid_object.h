#ifndef _H_PUNK_OPENGL_MODULE_GRID_OBJECT
#define _H_PUNK_OPENGL_MODULE_GRID_OBJECT

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE GridObject : public VertexArrayObject2<GL_TRIANGLES, 
			Vertex<VertexComponent::Position, 
				VertexComponent::Normal, 
				VertexComponent::Texture0, 
				VertexComponent::Flag>>
		{
            typedef VertexArrayObject2<GL_TRIANGLES,
            Vertex<VertexComponent::Position,
                VertexComponent::Normal,
                VertexComponent::Texture0,
                VertexComponent::Flag>> Base;

			enum { PrimitiveType = GL_TRIANGLES };
			static int64_t VertexCode;

		public:

            GridObject(VideoDriver* driver) : Base(driver) {}

			virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices);

		private:
			GridObject(const GridObject& quad);
			GridObject& operator = (const GridObject& quad);
		};
	}
}
#endif
