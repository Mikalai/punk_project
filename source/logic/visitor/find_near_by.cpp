#include "../entities/complex_entity.h"
#include "../entities/simple_entity.h"
#include "find_near_by.h"
#include "../../math/vec3.h"

namespace Logic
{
	FindNearBy::FindNearBy(const Math::vec3& pos, float r, const wchar_t* type)
		: m_center(pos)
		, m_radius(r)
		, m_type(type)
	{}


	bool FindNearBy::Visit(ComplexEntity* e)
	{
		for (auto it = e->begin(); it != e->end(); ++it)
		{
			(*it)->Visit(this);
		}
		return true;
	}

	bool FindNearBy::Visit(SimpleEntity* e)
	{
		PropertyCollection& pc = e->GetPropertyCollection();
		if (wcscmp(pc["TYPE"].AsString(), m_type.c_str()) == 0)
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