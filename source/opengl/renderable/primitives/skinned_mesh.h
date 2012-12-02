#ifndef _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT
#define _H_PUNK_OPENGL_MODULE_SKINNED_OBJECT

#include "../../../system/object.h"
#include "vertex_array_object.h"

namespace Utility {	class MeshDesc; }
namespace Utility {	class ArmatureDesc; }
namespace Math { template<class T> class Vector4; }

namespace OpenGL
{	
	class PUNK_ENGINE SkinnedMesh 
		: public System::Object
		, public VertexArrayObject2<GL_TRIANGLES, Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TANGENT|
		Utility::COMPONENT_BITANGENT|
		Utility::COMPONENT_TEXTURE|
		Utility::COMPONENT_BONE_ID|
		Utility::COMPONENT_BONE_WEIGHT>
	{
		enum { PrimitiveType = GL_TRIANGLES };
		enum { VertexType = Utility::COMPONENT_POSITION|
		Utility::COMPONENT_NORMAL|
		Utility::COMPONENT_TANGENT|
		Utility::COMPONENT_BITANGENT|
		Utility::COMPONENT_TEXTURE|
		Utility::COMPONENT_BONE_ID|
		Utility::COMPONENT_BONE_WEIGHT};
	public:
		
		SkinnedMesh();
		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		bool Cook(const Utility::MeshDesc* mesh, const Utility::ArmatureDesc* armature);		
		
		static System::Proxy<SkinnedMesh> CreateFromFile(const System::string& path);
		static System::Proxy<SkinnedMesh> CreateFromStream(std::istream& stream);

	protected:				
		bool CookOneVertexWithBone(const Utility::MeshDesc* o, const Utility::ArmatureDesc* armature, int index, Math::Vector4<float>& bone, Math::Vector4<float>& weight) const;
	};

	typedef SkinnedMesh* SkinnedEntityRef;
}

#endif	//	_H_PUNK_OPENGL_MODULE_SKINNED_OBJECT