#include "../entities/complex_entity.h"
#include "../entities/simple_entity.h"
#include "../property/property_collection.h"
#include "find_near_by_with_property.h"

namespace Logic
{
	FindNearByWithProperty::FindNearByWithProperty(const Math::vec3& pos, float r, const wchar_t* type, ID property)
		: m_center(pos)
		, m_radius(r)
		, m_type(type)
		, m_required_property(property)
	{}


	bool FindNearByWithProperty::Visit(ComplexEntity* e)
	{
		for (auto it = e->begin(); it != e->end(); ++it)
		{
			(*it)->Visit(this);
		}
		return true;
	}

	bool FindNearByWithProperty::Visit(SimpleEntity* e)
	{
		PropertyCollection& pc = e->GetPropertyCollection();
		if (wcscmp(pc["TYPE"].AsString(), m_type.c_str()) == 0 && pc.HasProperty(m_required_property))
		{
			float dst = (m_center - e->GetPosition()).Length();
			if (dst < m_radius)
			{
				m_result.push_back(e);
			}
		}
		return true;
	}
}
