#ifndef _H_PUNK_OPENGL_TRIANGLE_STRIP
#define _H_PUNK_OPENGL_TRIANGLE_STRIP

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<typename VertexType>
		class PUNK_ENGINE TriangleStrip: public VertexArrayObject2<GL_TRIANGLE_STRIP, VertexType>
		{
			enum { PrimitiveType = GL_TRIANGLE_STRIP };
			enum { VertexCode = VertexType::Value() };
		public:

			void Cook(const std::vector<VertexType>& value)
			{
				VertexArrayObject2<PrimitiveType, VertexType>::Clear();
				std::vector<unsigned> ib(value.size());
				for (unsigned i = 0; i < ib.size(); ++i)
					ib[i] = i;
				VertexArrayObject2<PrimitiveType, VertexType>::SetVertexBuffer(value);
				VertexArrayObject2<PrimitiveType, VertexType>::SetIndexBuffer(ib);
				VertexArrayObject2<PrimitiveType, VertexType>::Cook();
			}
		};
	}
}

#endif	//	_H_PUNK_OPENGL_TRIANGLE_STRIP
