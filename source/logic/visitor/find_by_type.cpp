//#include "../entities/complex_entity.h"
//#include "../entities/simple_entity.h"
//#include "find_by_type.h"
//
//namespace Logic
//{
//	FindByType::FindByType(const wchar_t* type)
//		: m_type(type)
//	{}
//
//	bool FindByType::Visit(ComplexEntity* e)
//	{
//		for (auto it = e->begin(); it != e->end(); ++it)
//		{
//			(*it)->Visit(this);
//		}
//		return true;
//	}
//
//	bool FindByType::Visit(SimpleEntity* e)
//	{
//		PropertyCollection& pc = e->GetPropertyCollection();
//		if (wcscmp(pc["TYPE"].AsString(), m_type.c_str()) == 0)
//		{
//			m_result.push_back(e);
//		}
//		return true;
//	}
//}
