#ifndef _H_PUNK_OPENGL_MODULE_STATIC_OBJECT
#define _H_PUNK_OPENGL_MODULE_STATIC_OBJECT

#include "../../../../system/resource_manager.h"
#include "../../../../system/object.h"
#include "vertex_array_object.h"

namespace Virtual { class StaticGeometry; }

namespace GPU
{
	namespace OpenGL
	{	
		class PUNK_ENGINE StaticMesh 
			: public System::Object
			, public VertexArrayObject2<GL_TRIANGLES, COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_TEXTURE>
		{
			enum { PrimitiveType = GL_TRIANGLES };
			enum { VertexType = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_TEXTURE };
		public:

			StaticMesh();

			virtual bool Save(std::ostream& stream) const;
			virtual bool Load(std::istream& stream);

			bool Cook(System::Proxy<Virtual::StaticGeometry> desc);		

			static System::Proxy<StaticMesh> CreateFromFile(const System::string& path);
			static System::Proxy<StaticMesh> CreateFromStream(std::istream& stream);

		protected:				
		};

		typedef StaticMesh* StaticEntityRef;
	}
}

#endif