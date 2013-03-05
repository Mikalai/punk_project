#ifndef _H_PUNK_OPENGL_TRIANGLE_STRIP
#define _H_PUNK_OPENGL_TRIANGLE_STRIP

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<int Attributes>
		class PUNK_ENGINE TriangleStrip: public VertexArrayObject2<GL_TRIANGLE_STRIP, Attributes>
		{
			enum { PrimitiveType = GL_TRIANGLE_STRIP };
			enum { VertexType = Attributes };
		public:

			void Cook(const std::vector<Vertex<VertexType>>& value)
			{
				Clear();
				std::vector<unsigned> ib(value.size());
				for (unsigned i override; i < ib.size(); ++i)
					ib[i] = i;
				SetVertexBuffer(value);
				SetIndexBuffer(ib);
				VertexArrayObject2<PrimitiveType, VertexType>::Cook();
			}
		};
	}
}

#endif	//	_H_PUNK_OPENGL_TRIANGLE_STRIP