#ifndef _H_PUNK_OPENGL_SPHERE_MESH
#define _H_PUNK_OPENGL_SPHERE_MESH

#include "vertex_array_object.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE SphereObject : public VertexArrayObject2<GL_LINE_LOOP,
			Vertex<VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::Tangent,
				VertexComponent::Bitangent,
				VertexComponent::Texture0>>
		{
			enum { PrimitiveType = GL_LINE_LOOP };
			static int64_t VertexCode;

		public:
			SphereObject();
			void Cook(float radius);

			static SphereObject* Instance();
			static void Destroy();

		private:
			static std::unique_ptr<SphereObject> m_instance;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_SPHERE_MESH
