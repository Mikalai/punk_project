//#include <iostream>
//#include "../visitor/visitor.h"
//#include "simple_entity.h"
//
//namespace Logic
//{
//	SimpleEntity::SimpleEntity()
//		: SolidEntity()
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		PropertyCollection& pc = GetPropertyCollection();
//		pc["TYPE"].SetValue(L"SIMPLE");
//		pc["COUNT"].SetValue(1);
//	}
//
//	SimpleEntity::SimpleEntity(const SimpleEntity& e)
//		: SolidEntity(e)
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	SimpleEntity& SimpleEntity::operator = (const SimpleEntity& e)
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		SolidEntity::operator = (e);
//
//		if (this != &e)
//		{
//			;
//		}
//		return *this;
//	}
//
//	bool SimpleEntity::Visit(Visitor* v)
//	{
//		return v->Visit(this);
//	}
//
//	AbstractEntity* SimpleEntity::Clone() const
//	{
//		return new SimpleEntity(*this);
//	}
//
//	SimpleEntity* SimpleEntity::Detach()
//	{
//		DECLARE_PROPERTY_COLLECTION;
//
//		int current_count = pc["COUNT"].AsInt();
//
//		if (current_count == 1)
//			return this;
//		else
//		{
//			--current_count;
//			SimpleEntity* detached_entity = static_cast<SimpleEntity*>(this->Clone());
//			detached_entity->GetPropertyCollection()["COUNT"].SetValue(1);
//			pc["COUNT"].Dec(1);
//			return detached_entity;
//		}
//	}
//}
