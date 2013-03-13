#include "construction.h"
#include "world.h"
#include "ibuilder.h"
#include "structure_scheme.h"
#include "structure.h"

void Construction::SetWorld(World* world)
{
	m_world = world;
}

void Construction::SetFinishAction(IAction* action)
{
	m_on_finish = action;
}

void Construction::SetBudget(int budget)
{
	m_budget = budget;
};

void Construction::StartBuilding(StructureScheme* scheme)
{
	m_jobs_elements_left = scheme->GetTotalJobsElements();
	m_scheme = scheme;
	m_can_be_deleted = false;
}

bool Construction::NeedRemove() 
{
	return false;
}

bool Construction::NeedDelete() 
{
	return m_can_be_deleted;
}

void Construction::Update(double time, double dt) 
{
	for (std::vector<IBuilder*>::iterator it = m_workers.begin(); it != m_workers.end(); ++it)
	{
		IBuilder* worker = *it;
		int cost_per_hour = worker->EstimateConstructionCost(m_scheme);
		m_salary[worker] += (float)cost_per_hour * dt / 60.0 / 60.0;
		m_jobs_elements_left -= (float)worker->GetConstructionProductivity() * dt / 60.0 / 60.0;
		if (m_jobs_elements_left <= 0)
		{
			for (std::map<IBuilder*, double>::iterator salary_it = m_salary.begin(); salary_it != m_salary.end(); ++salary_it)
			{
				double salary = salary_it->second;
				IBuilder* w = salary_it->first;
				w->Pay((int)salary);
			}					
			Structure* s = ToStructure();
			m_scheme->Add(s);
			m_world->AddGameEntity(s->ToGameEntity());
			m_can_be_deleted = true;
		}
		return;
	}
}

void Construction::AddWorker(IBuilder* worker)
{
	m_workers.push_back(worker);
}

void Construction::RemoveWorker(IBuilder* worker)
{
	m_workers.erase(m_workers.begin(), std::remove(m_workers.begin(), m_workers.end(), worker));
}
