#ifndef _H_PUNK_OPENGL_LINES
#define _H_PUNK_OPENGL_LINES

#include <vector>
#include "vertex_array_object.h"
#include "../../../common/vertex.h"

namespace GPU
{
	namespace OpenGL
	{
		template<typename VertexType>
		class PUNK_ENGINE Lines: public VertexArrayObject2<GL_LINES, VertexType>
		{
            typedef VertexArrayObject2<GL_LINES, VertexType> Base;

			enum { PrimitiveType = GL_LINES };
			static int64_t VertexCode;
		public:

            Lines(VideoDriver* driver) : Base(driver) {}

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

		template<typename VertexType> int64_t Lines<VertexType>::VertexCode = VertexType::Value();
	}
}

#endif	//	_H_PUNK_OPENGL_LINES
