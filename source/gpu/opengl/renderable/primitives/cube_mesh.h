#ifndef _H_PUNK_OPENGL_CUBE_MESH
#define _H_PUNK_OPENGL_CUBE_MESH

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE CubeObject : public VertexArrayObject2<GL_TRIANGLES, COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_TANGENT|COMPONENT_BITANGENT >
		{
			enum { PrimitiveType = GL_TRIANGLES };
			enum { VertexType = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_TANGENT|COMPONENT_BITANGENT };
		public:
			CubeObject();
			void Cook(float width, float height, float depth);

			static CubeObject* Instance();
			static void Destroy();

		private:
			static std::auto_ptr<CubeObject> m_instance;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_CUBE_MESH