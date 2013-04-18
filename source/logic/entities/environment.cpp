//#define NOMINMAX
//#include <algorithm>
//#include <limits>
//#include "../../math/vec3.h"
//#include "simple_entity.h"
//#include "environment.h"
//#include "../visitor/find_near_by.h"
//
//namespace Logic
//{
//	Simulation::PostUpdateAction Environment::Update(float delta_in_ms)
//	{
//		static float time = 0;
//		time += delta_in_ms;
//		if (time > 1000)
//		{
//			time = 0;
//			FindNearBy finder(Math::vec3(0,0,0), 50, L"FOOD");
//			Visit(&finder);
//			if (finder.GetResult().size() < 5)
//			{
//				SimpleEntity* fish = new SimpleEntity;
//				fish->GetPropertyCollection().RegisterProperty("NAME")->SetValue(L"Fish");
//				fish->GetPropertyCollection().RegisterProperty("SATIETY")->SetValue(300);
//				fish->GetPropertyCollection().RegisterProperty("WEIGHT")->SetValue(100.0);
//				fish->GetPropertyCollection().RegisterProperty("TYPE")->SetValue(L"FOOD");
//				fish->SetPosition(Math::vec3( rand() % 60, 0, rand() % 60));
//				AddChild(fish);
//			}
//		}
//
//		for (auto it = m_simulations.begin(); it != m_simulations.end(); it++)
//		{
//			(*it)->Update(delta_in_ms);
//		}
//		return KEEP;
//	}
//
//	Environment::~Environment()
//	{
//	}
//
//	void Environment::AddChild(SolidEntity* e)
//	{
//		Simulation* sim = dynamic_cast<Simulation*>(e);
//		if (sim)
//		{
//			m_simulations.push_back(sim);
//		}
//		ComplexEntity::AddChild(e);
//	}
//
//	void Environment::RemoveChild(SolidEntity* e)
//	{
//		Simulation* sim = dynamic_cast<Simulation*>(e);
//		if (sim)
//		{
//			auto to_delete = std::find(m_simulations.begin(), m_simulations.end(), sim);
//			if (to_delete != m_simulations.end())
//				m_simulations.erase(to_delete);
//		}
//		ComplexEntity::RemoveChild(e);
//	}
//
//}
