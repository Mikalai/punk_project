#include "../entities/complex_entity.h"
#include "../entities/simple_entity.h"
#include "../property/property_collection.h"
#include "../../math/vec3.h"
#include "../code.h"
#include "find_nearest_with_property.h"

namespace Logic
{
	FindNearestWithProperty::FindNearestWithProperty(const Math::vec3& pos, float r, const wchar_t* type, ID property)
		: m_center(pos)
		, m_radius(r)
		, m_type(type)
		, m_required_property(property)
		, m_result(0)
	{}


	bool FindNearestWithProperty::Visit(ComplexEntity* e)
	{
		for (auto it = e->begin(); it != e->end(); ++it)
		{
			(*it)->Visit(this);
		}
		return true;
	}

	bool FindNearestWithProperty::Visit(SimpleEntity* e)
	{
		PropertyCollection& pc = e->GetPropertyCollection();
		if (wcscmp(pc["TYPE"].AsString(), m_type.c_str()) == 0 && pc.HasProperty(m_required_property))
		{
			float dst = (m_center - e->GetPosition()).Length();
			if (dst < m_radius && (m_result == 0 || (m_result->GetPosition() - m_center).SquareLength() > (e->GetPosition() - m_center).SquareLength()))
			{
				m_result = e;
			}
		}
		return true;
	}

}