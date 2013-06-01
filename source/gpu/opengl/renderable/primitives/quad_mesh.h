#ifndef _H_PUNK_OPENGL_QUAD
#define _H_PUNK_OPENGL_QUAD

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE QuadObject : public VertexArrayObject2<GL_TRIANGLES, Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>>
		{
			enum { PrimitiveType = GL_TRIANGLES };
			typedef Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0> CurrentVertex;
		public:
			QuadObject();
			void Cook(float width, float height);

			static QuadObject* Instance();
			static void Destroy();

		private:
			static std::unique_ptr<QuadObject> m_instance;
		};
	}
}

#endif
