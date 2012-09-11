#include "../entities/complex_entity.h"
#include "../entities/simple_entity.h"
#include "count_specific_type.h"

namespace Logic
{

	bool CountSpecificType::Visit(ComplexEntity* e)
	{
		for (auto it = e->begin(); it != e->end(); ++it)
		{
			(*it)->Visit(this);
		}
		return true;
	}

	bool CountSpecificType::Visit(SimpleEntity* e)
	{
		PropertyCollection& pc = e->GetPropertyCollection();
		if (wcscmp(pc["TYPE"].AsString(), m_type.c_str()) == 0)
		{
			m_count += pc["COUNT"].AsInt();
		}
		return true;
	}

}