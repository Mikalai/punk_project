#ifndef _H_CONSTRUCTION
#define _H_CONSTRUCTION

#include "../../../source/punk_engine.h"
#include "dynamic.h"

class IAction;
class IBuilder;
class Structure;
class StructureScheme;
class World;
class GameEntity;

class Construction : public IDynamic
{
public:

	void SetWorld(World* world);
	void SetFinishAction(IAction* action);
	void SetBudget(int budget);
	void SetLocation(const Math::vec3& value);
	void SetDirection(const Math::vec3& value);
	void StartBuilding(StructureScheme* scheme);
	void AddWorker(IBuilder* worker);	//	increase worker count by one
	void RemoveWorker(IBuilder* worker);	//	decrease worker count by one

	virtual Structure* ToStructure() = 0;

	bool NeedRemove() override;
	bool NeedDelete() override;
	void Update(double time, double dt) override;

	GameEntity* ToGameEntity() { return m_node; }

private:

	World* m_world;
	bool m_can_be_deleted;
	int m_budget;
	float m_jobs_elements_left;
	StructureScheme* m_scheme;
	std::vector<IBuilder*> m_workers;
	std::map<IBuilder*, double> m_salary;
	IAction* m_on_finish;
	GameEntity* m_node;
};


#endif	//	_H_CONSTRUCTION
