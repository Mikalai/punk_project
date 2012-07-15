#include "object.h"
#include "../../math/line3d.h"
#include "../../math/triangle3d.h"

namespace Utility
{
	Object::Object()
		: m_parent(0)
	{}

	bool Object::IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res) const
	{
		Math::OctTree::FaceList fl  = m_oct_tree.CrossAll(Math::Line3D(start, end));
		if (fl.empty())
			return false;

		for (int tr = 0; tr < fl.size(); tr++)
		{
			const Math::vec3& a = m_mesh->m_vertices[fl[tr].X()];
			const Math::vec3& b = m_mesh->m_vertices[fl[tr].Y()];
			const Math::vec3& c = m_mesh->m_vertices[fl[tr].Z()];

			Math::Triangle3D triangle(a, b, c);
			Math::Line3D line(start, end);
			float t;
			if (Math::LineCrossTriangle(line, triangle, t) == Math::SKEW_CROSS)
			{
				res[m_name].push_back(line.PointAt(t));				
			}
		}			

		if (res.find(m_name) == res.end())
		{
			return false;
		}
		else
		{
			res[m_name].SetName(m_name);
			return true;
		}
	}

	Object* Object::GetChild(const System::string& name)
	{
		return const_cast<Object*>(static_cast<const Object*>(this)->GetChild(name));
	}

	const Object* Object::GetChild(const System::string& name) const
	{
		for each (std::shared_ptr<Object> obj in m_children)
		{
			if (obj->GetName() == name)
				return obj.get();
		}
		return 0;
	}

	int Object::GetChildIndex(const System::string& name)
	{
		int index = 0;
		for each(auto child in m_children)
		{
			if (child->GetName() == name)
				return index;
			index++;
		}
		return -1;
	}
}

