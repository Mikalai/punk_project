#include <iostream>
#include <vector>
#include <algorithm>
#include "../entities/character.h"
#include "simple_ai.h"
#include "../entities/complex_entity.h"
#include "../entities/environment.h"
#include "../task/task.h"
#include "../visitor/find_by_type.h"
#include "../visitor/find_near_by_with_property.h"
#include "../visitor/find_near_by.h"
#include "../visitor/count_specific_type.h"
#include "../visitor/find_nearest_with_property.h"

namespace Logic
{
	SimpleAI::SimpleAI()
	{
		m_entity_to_goto = 0;
	}

	void SimpleAI::SetSimulation(Simulation* s)
	{
		m_character = dynamic_cast<Character*>(s);
		if (m_character == 0)
			std::cout << "Unable to set a character for simple ai" << std::endl;
		PropertyCollection& p = m_character->GetPropertyCollection();
		p.RegisterProperty("TYPE")->SetValue(L"CHARACTER");
		p.RegisterProperty("ALIVE")->SetValue(1);
		p.RegisterProperty("WATER")->SetValue(100.0);
		p.RegisterProperty("HEALTH")->SetValue(100.0);
		p.RegisterProperty("SLEEP")->SetValue(0);
		p.RegisterProperty("ENERGY")->SetValue(100.0);
		p.RegisterProperty("SATIETY")->SetValue(100.0);
		p.RegisterProperty("GO")->SetValue(0);
		p.RegisterProperty("STAY")->SetValue(1);
		p.RegisterProperty("SPEED")->SetValue(1.0);
		p.RegisterProperty("GOTO_FOOD")->SetValue(0);
		p.RegisterProperty("CAN_GO")->SetValue(1);
	}

	void SimpleAI::Solve(float delta_in_ms)
	{
		double delta = delta_in_ms / 1000.0;
		PropertyCollection& p = m_character->GetPropertyCollection();

		p["SATIETY"].Dec(delta);
		p["WATER"].Dec(delta);

		if (p["SLEEP"].AsInt() == 1)
		{
			p["ENERGY"].Inc(delta);
			if (p["ENERGY"].AsReal() > 100)
			{
				p["SLEEP"].SetValue(0);
				p["STAY"].SetValue(1);
				p["GO"].SetValue(0);
				//	std::wcout << p["NAME"].AsString() << L" woke up." << std::endl;
			}
		}
		else
		{
			p["ENERGY"].Dec(delta);
			if (p["ENERGY"].AsReal() < 0)
			{
				//	p["SLEEP"].SetValue(1);
				//	p["STAY"].SetValue(0);
				//p["GO"].SetValue(0);
				//	std::wcout << p["NAME"].AsString() << L" fell sleep." << std::endl;
			}
		}

		/// look for the food staff in the inventory
		FindByType type_finder(L"FOOD");
		m_character->Visit(&type_finder);

		if (p["SATIETY"].AsReal() < 500)	//character needs food
		{
			//	std::wcout << p["NAME"].AsString() << L" feels hunger" << std::endl;		
			// if found something than eat it
			if (!type_finder.GetResult().empty())
			{
				std::auto_ptr<SolidEntity> e(*type_finder.GetResult().begin());
				m_character->RemoveChild(e.get());
				std::auto_ptr<TaskEat> task(new TaskEat);
				task->SetEntityToEat(e.release());
				m_character->AddTask(task.release());
			}
			else
			{
				;	//	std::cout << "Nothing to eat. Soon die" << std::endl;
			}
		}

		//if (p["CAN_GO"].AsInt() == 1)
		{
			if (type_finder.GetResult().size() < 4)
			{
				Environment* env = dynamic_cast<Environment*>(m_character->GetOwner());
				if (env)
				{
					FindNearestWithProperty finder(m_character->GetPosition(), 50, L"FOOD", "SATIETY");
					m_character->GetOwner()->Visit(&finder);
					if (finder.GetResult())
					{
						m_entity_to_goto = finder.GetResult();

						if ((m_entity_to_goto->GetPosition() - m_character->GetPosition()).Length() < 0.5)
						{
							std::auto_ptr<TaskTake> task(new TaskTake(m_entity_to_goto));
							m_character->AddTask(task.release());
							//	std::wcout << p["NAME"].AsString() << L" decided to take from the world " << target->GetPropertyCollection()["NAME"].AsString() << std::endl;												
							m_entity_to_goto = 0;
						}
						else
						{
							//		std::wcout << p["NAME"].AsString() << L" decided to go to " << target->GetPropertyCollection()["NAME"].AsString() << std::endl;
							std::auto_ptr<TaskGoTo> task(new TaskGoTo);
							task->SetDestination(m_entity_to_goto->GetPosition());
							m_character->AddTask(task.release());
						}
					}
				}
			}
		}

		if (p["SATIETY"].AsReal() < 0)
		{
			p["ALIVE"].SetValue(0);
			//std::wcout << p["NAME"].AsString() << L" died from hunger" << std::endl;
		}
	}

	void SimpleAI::Apply(ComplexEntity* e)
	{

	}
}