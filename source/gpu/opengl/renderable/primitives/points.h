#ifndef _H_PUNK_OPENGL_POINTS_VAO
#define _H_PUNK_OPENGL_POINTS_VAO

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<typename VertexType>
		class PUNK_ENGINE Points : public VertexArrayObject2<GL_POINTS, VertexType>
		{
			enum { PrimitiveType = GL_POINTS };
			static int64_t VertexCode;

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

		template<typename VertexType> int64_t Points<VertexType>::VertexCode = VertexType::Value();
	}
}

#endif	//	_H_PUNK_OPENGL_POINTS_VAO
