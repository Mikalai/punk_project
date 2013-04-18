//#include "simulation.h"
//#include "simulator.h"
//#include "events\events_type.h"
//#include "events\event_update.h"
//#include "../system/event_manager.h"
//
//namespace Logic
//{
//	void Simulator::Activate()
//	{
//		System::EventManager::Instance()->SubscribeHandler(EVENT_UPDATE, System::EventHandler(this, &Simulator::OnUpdate));
//	}
//
//	void Simulator::Deactivate()
//	{
//		System::EventManager::Instance()->UnsubscribeHandler(EVENT_UPDATE, System::EventHandler(this, &Simulator::OnUpdate));
//	}
//
//	void Simulator::Add(Simulation* add)
//	{
//		m_simulations.push_back(add);
//	}
//
//	void Simulator::OnUpdate(System::Event* event)
//	{
//		EventUpdate* e = static_cast<EventUpdate*>(event);
//
//		auto current_simulations = m_simulations;
//		m_simulations.clear();
//		for each (Simulation* sim in current_simulations)
//		{
//			Simulation::PostUpdateAction action = sim->Update(e->time_in_ms);
//			switch(action)
//			{
//			case Simulation::DESTROY:
//				delete sim;
//				break;
//			case Simulation::KEEP:
//				m_simulations.push_back(sim);
//			}
//		}
//	}
//}
