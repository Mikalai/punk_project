#include "../error/module.h"
#include "renderable.h"

namespace GPU
{
	Renderable::Renderable() 
		//: m_primitive_type(PrimitiveTypes::NONE)
	{}

	//bool Renderable::Save(std::ostream& stream) const
	//{
	//	stream.write((char*)&m_primitive_type, sizeof(m_primitive_type));	//	it is always written but ignored by load function
	//	return true;
	//}

	//bool Renderable::Load(std::istream& stream)
	//{
	//	return true;	//	type is read by CreateFromStream
	//}

	//System::Proxy<Renderable> Renderable::CreateFromFile(const System::string& path)
	//{
	//	std::ifstream stream(path.Data(), std::ios::binary);
	//	if (!stream.is_open())
	//		throw OpenGLException(L"Can't open file " + path);
	//	return CreateFromStream(stream);
	//}

	//System::Proxy<Renderable> Renderable::CreateFromStream(std::istream& stream)
	//{
	//	/*PrimitiveTypes type;
	//	stream.read((char*)&type, sizeof(type));

	//	switch (type)
	//	{
	//	case OpenGL::QUAD:
	//	return QuadObject::CreateFromStream(stream);
	//	case OpenGL::SKIN_MESH:
	//	return SkinMesh::CreateFromStream(stream);
	//	case OpenGL::STATIC_MESH:
	//	return StaticMesh::CreateFromStream(stream);
	//	default:
	//	throw OpenGLException(L"Can't create renderable from stream ");
	//	}
	//	return System::Proxy<Renderable>(nullptr);*/
	//	throw OpenGLException(L"Not implementerd");
	//}
}