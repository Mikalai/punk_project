#include <iostream>
#include <string>
#include <sstream>
#include "../entities/complex_entity.h"
#include "task.h"
#include "../entities/character.h"
#include "../visitor/find_by_type.h"
#include "../visitor/count_specific_type.h"

namespace Logic
{
	bool TaskGoTo::Perform(Character* c, float delta_in_ms)
	{

		Math::vec3 p = c->GetPosition();

		double speed = c->GetPropertyCollection()["SPEED"].AsReal();
		Math::vec3 dir = (m_dst - p).Normalized();
		const Math::vec3& orient = c->GetOrientation();
		dir = 0.8f * orient + 0.2f * dir;

		p += dir * (float)speed * (float)delta_in_ms / (1000.0f);
		c->SetOrientation(dir);
		c->SetPosition(p);

		return true;
	}

	const System::string TaskGoTo::ToString() const
	{
		return System::string::Format(L"Go to: (%f, %f, %f)", m_dst[0], m_dst[1], m_dst[2]);		
	}

	bool TaskEat::Perform(Character* c, float delta_in_ms)
	{	
		//
		//	if the food was not specified we look for the food in the 
		//	inventory ourself
		//
		if (m_entity == 0)
		{
			FindByType finder(L"FOOD");
			c->Visit(&finder);
			if (finder.GetResult().empty())
				return true;
			m_entity = finder.GetResult().front();
		}
		//std::cout << "PERFORM EAT: ";

		PropertyCollection& cp = c->GetPropertyCollection();
		PropertyCollection& ep = m_entity->GetPropertyCollection();
		// if it is not food we can't eat it
		if (wcscmp(ep["TYPE"].AsString(), L"FOOD") != 0)
		{
			//	put it in the inventory
			c->AddChild(m_entity);
			return true;
		}

		for (auto it = ep.begin(); it != ep.end(); ++it)
		{
			Property& p = it->second;
			if (c->GetPropertyCollection().HasProperty(p.GetName()))
			{
				Property& c_p = c->GetPropertyCollection()[p.GetName()];
				switch(p.GetType())
				{
				case Property::TYPE_INTEGER:
					c_p.Inc(p.AsInt());
					break;
				case Property::TYPE_REAL:
					c_p.Inc(p.AsReal());
					break;
				default:
					break;
				}
			}
		}

		delete m_entity;
		return true;
	}

	const System::string TaskEat::ToString() const
	{
		return System::string::Format(L"Eat: %s with satiety + %f", m_entity->GetPropertyCollection()["NAME"].AsString(), 
			m_entity->GetPropertyCollection()["SATIETY"].AsReal());
	}

	bool TaskTake::Perform(Character* c, float delta_in_ms)
	{
		if (m_entity->GetOwner()  == c->GetOwner())
		{
			if ((c->GetPosition() - m_entity->GetPosition()).Length() < 0.5)
			{
				c->AddChild(m_entity);
				m_entity = 0;			
			}	
		}
		c->GetPropertyCollection()["CAN_GO"].SetValue(1);
		return true;
	}

	const System::string TaskTake::ToString() const
	{
		return System::string::Format(L"Take: %s", m_entity->GetPropertyCollection()["NAME"].AsString());
	}
}