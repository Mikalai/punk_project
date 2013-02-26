#ifndef _H_PUNK_OPENGL_TRIANGLE_FAN
#define _H_PUNK_OPENGL_TRIANGLE_FAN

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<int Attributes>
		class PUNK_ENGINE TriangleFan: public VertexArrayObject2<GL_TRIANGLE_FAN, Attributes>
		{
			enum { PrimitiveType = GL_TRIANGLE_FAN };
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

#endif	//	_H_PUNK_OPENGL_TRIANGLE_FAN
