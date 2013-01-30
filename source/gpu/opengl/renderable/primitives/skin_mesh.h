#ifndef _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
#define _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT

#include "../../../../system/object.h"
#include "vertex_array_object.h"

namespace Virtual { class SkinGeometry; }
namespace Virtual { class Armature; }

namespace Math { template<class T> class Vector4; }

namespace GPU
{
	namespace OpenGL
	{	
		class PUNK_ENGINE SkinMesh 
			: public System::Object
			, public VertexArrayObject2<GL_TRIANGLES, COMPONENT_POSITION|
			COMPONENT_NORMAL|
			COMPONENT_TANGENT|
			COMPONENT_BITANGENT|
			COMPONENT_TEXTURE|
			COMPONENT_BONE_ID|
			COMPONENT_BONE_WEIGHT>
		{
			enum { PrimitiveType = GL_TRIANGLES };
			enum { VertexType = COMPONENT_POSITION|
				COMPONENT_NORMAL|
				COMPONENT_TANGENT|
				COMPONENT_BITANGENT|
				COMPONENT_TEXTURE|
				COMPONENT_BONE_ID|
				COMPONENT_BONE_WEIGHT};
		public:

			SkinMesh();
			virtual bool Save(std::ostream& stream) const;
			virtual bool Load(std::istream& stream);

			bool Cook(const System::Proxy<Virtual::SkinGeometry> mesh, const System::Proxy<Virtual::Armature> armature);	

			static System::Proxy<SkinMesh> CreateFromFile(const System::string& path);
			static System::Proxy<SkinMesh> CreateFromStream(std::istream& stream);

		protected:				
			bool CookOneVertexWithBone(const System::Proxy<Virtual::SkinGeometry> mesh, const System::Proxy<Virtual::Armature> armature, int index, Math::Vector4<float>& bone, Math::Vector4<float>& weight) const;
		};

		typedef SkinMesh* SkinnedEntityRef;
	}
}

#endif	//	_H_PUNK_OPENGL_MODULE_SKINNED_OBJECT