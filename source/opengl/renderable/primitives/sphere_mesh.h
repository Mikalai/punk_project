#ifndef _H_PUNK_OPENGL_SPHERE_MESH
#define _H_PUNK_OPENGL_SPHERE_MESH

#include "vertex_array_object.h"

namespace OpenGL
{
	class PUNK_ENGINE SphereObject : public VertexArrayObject2<GL_LINE_LOOP, Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT >
	{
		enum { PrimitiveType = GL_LINE_LOOP };
		enum { VertexType = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_TEXTURE|Utility::COMPONENT_TANGENT|Utility::COMPONENT_BITANGENT };
	public:
		SphereObject();
		void Cook(float radius);

		static SphereObject* Instance();
		static void Destroy();

	private:
		static std::auto_ptr<SphereObject> m_instance;
	};
}

#endif	//	_H_PUNK_OPENGL_SPHERE_MESH
