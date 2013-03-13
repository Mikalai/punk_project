#ifndef _H_RTS_DEMO_WORKER
#define _H_RTS_DEMO_WORKER

#include "ibuilder.h"
#include "../../../source/punk_engine.h"

class Worker : public IBuilder
{
public:

	virtual int GetWorkerLevel() override;
	virtual int GetConstructionProductivity() override;	//	construction job elements per hour
	virtual int GetConstructionEngineeringSkill() override;
	virtual int EstimateConstructionCost(StructureScheme*) override;	
	virtual int GetMilitaryConstructionEngineeringSkillCost() override;	
	virtual int GetElectronicEngineeringSkill() override;	
	virtual int GetElectronicEngineeringSkillCost() override;	
	virtual void Build(Construction* value, double dt) override;
	virtual void Pay(int money) override;

	Scene::Node* GetNode() { return m_node; }

	virtual ~Worker();

private:
	Scene::Node* m_node;
	Scene::TransformNode* m_transform;
	Math::vec3 m_position;
	Math::vec3 m_direction;
};

#endif	//	_H_RTS_DEMO_WORKER