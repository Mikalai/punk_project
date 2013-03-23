#include "worker.h"
#include "construction.h"

#define MODEL_FILE 

void Worker::Build(Construction* construction, double dt)
{
	int cost_per_hour = EstimateConstructionCost(construction->GetStructureScheme());
	m_money += (float)cost_per_hour * dt / 60.0 / 60.0;
	construction->AdvanceConstruction((float)GetConstructionProductivity() * dt / 60.0 / 60.0);
}