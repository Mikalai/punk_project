#ifndef _H_PUNK_OPENGL_MODULE_STATIC_OBJECT
#define _H_PUNK_OPENGL_MODULE_STATIC_OBJECT

#include "../../../system/object.h"
#include "vertex_array_object.h"

namespace Utility {	class MeshDesc; }

namespace OpenGL
{	
	class PUNK_ENGINE StaticMesh 
		: public System::Object
		, public VertexArrayObject2<GL_TRIANGLES, Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TANGENT|Utility::COMPONENT_TEXTURE>
	{
		enum { PrimitiveType = GL_TRIANGLES };
		enum { VertexType = Utility::COMPONENT_POSITION|Utility::COMPONENT_NORMAL|Utility::COMPONENT_BITANGENT|Utility::COMPONENT_TANGENT|Utility::COMPONENT_TEXTURE };
	public:
		
		StaticMesh();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		bool Cook(Utility::MeshDesc* desc);		

		static System::Proxy<StaticMesh> CreateFromFile(const System::string& path);
		static System::Proxy<StaticMesh> CreateFromStream(std::istream& stream);

	protected:				
	};

	typedef StaticMesh* StaticEntityRef;
}

#endif