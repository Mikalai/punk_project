#include "renderable.h"
#include "static_mesh.h"
#include "skin_mesh.h"
#include "quad_mesh.h"
#include "primitive_types.h"

namespace OpenGL
{
	Renderable::Renderable() 
		: m_primitive_type(PrimitiveTypes::NONE)
	{}

	bool Renderable::Save(std::ostream& stream) const
	{
		stream.write((char*)&m_primitive_type, sizeof(m_primitive_type));	//	it is always written but ignored by load function
		return true;
	}

	bool Renderable::Load(std::istream& stream)
	{
		return true;	//	type is read by CreateFromStream
	}

	System::Proxy<Renderable> Renderable::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			return (out_error() << "Can't open file " << path.Data() << std::endl, System::Proxy<Renderable>(nullptr));
		return CreateFromStream(stream);
	}

	System::Proxy<Renderable> Renderable::CreateFromStream(std::istream& stream)
	{
		PrimitiveTypes type;
		stream.read((char*)&type, sizeof(type));

		switch (type)
		{
		case OpenGL::QUAD:
			return QuadObject::CreateFromStream(stream);
		case OpenGL::SKIN_MESH:
			return SkinMesh::CreateFromStream(stream);
		case OpenGL::STATIC_MESH:
			return StaticMesh::CreateFromStream(stream);
		default:
			return (out_error() << "Can't create renderable from stream " << std::endl, System::Proxy<Renderable>(nullptr));
		}
		return System::Proxy<Renderable>(nullptr);
	}
}