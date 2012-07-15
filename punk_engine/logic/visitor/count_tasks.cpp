#include "../entities/complex_entity.h"
#include "count_tasks.h"

namespace Logic
{
	bool CountTasks::Visit(ComplexEntity* e)
	{
		/*PropertyCollection& pc = e->GetPropertyCollection();
		if (wcscmp(pc["TYPE"].AsString(), L"CHARACTER") == )
		{

		}*/
		return true;
	}
}