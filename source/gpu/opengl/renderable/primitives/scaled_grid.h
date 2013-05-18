#ifndef _H_PUNK_OPENGL_SCALED_GRID
#define _H_PUNK_OPENGL_SCALED_GRID

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE ScaledGridObject : public VertexArrayObject2<GL_TRIANGLES, 
			Vertex<VertexComponent::Position, 
				VertexComponent::Normal, 
				VertexComponent::Texture0>>
		{
            typedef VertexArrayObject2<GL_TRIANGLES,
            Vertex<VertexComponent::Position,
                VertexComponent::Normal,
                VertexComponent::Texture0>> Base;

			enum { PrimitiveType = GL_TRIANGLES };
			static int64_t VertexType;

		public:

            ScaledGridObject(VideoDriver* driver) : Base(driver) {}

			virtual void Cook(float width, float height, unsigned hor_slices, unsigned vert_slices, int levels);

			float GetTotalWidth() const;
			float GetTotalHeight() const;

		private:
			ScaledGridObject(const ScaledGridObject& quad);
			ScaledGridObject& operator = (const ScaledGridObject& quad);

			float m_total_width;
			float m_total_height;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_SCALED_GRID
