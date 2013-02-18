#ifndef _H_PUNK_OPENGL_POINTS_VAO
#define _H_PUNK_OPENGL_POINTS_VAO

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<int Attributes>
		class PUNK_ENGINE Points: public VertexArrayObject2<GL_POINTS, Attributes>
		{
			enum { PrimitiveType = GL_POINTS };
			enum { VertexType = Attributes };
		public:

			void Cook(const std::vector<Vertex<VertexType>>& value)
			{
				Clear();
				std::vector<unsigned> ib(value.size());
				for (unsigned i = 0; i < ib.size(); ++i)
					ib[i] = i;
				SetVertexBuffer(value);
				SetIndexBuffer(ib);
				VertexArrayObject2<PrimitiveType, VertexType>::Cook();
			}
		};
	}
}

#endif	//	_H_PUNK_OPENGL_POINTS_VAO