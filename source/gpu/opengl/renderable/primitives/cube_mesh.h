#ifndef _H_PUNK_OPENGL_CUBE_MESH
#define _H_PUNK_OPENGL_CUBE_MESH

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE CubeObject : public VertexArrayObject2<GL_TRIANGLES,
			Vertex<VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::Tangent,
				VertexComponent::Bitangent,
				VertexComponent::Texture0>>
		{
			enum { PrimitiveType = GL_TRIANGLES };
			const int64_t VertexCode = CurrentVertex::Value();

		public:
			CubeObject();
			void Cook(float width, float height, float depth);

			static CubeObject* Instance();
			static void Destroy();

		private:
			static std::unique_ptr<CubeObject> m_instance;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_CUBE_MESH
