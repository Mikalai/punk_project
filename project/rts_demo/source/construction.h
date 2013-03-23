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
	Construction();

	void SetWorld(World* world);
	void SetFinishAction(IAction* action);
	void SetBudget(int budget);
	void SetLocation(const Math::vec3& value);
	void SetDirection(const Math::vec3& value);
	void StartBuilding();
	void SetScheme(StructureScheme* scheme);
	void AddWorker(IBuilder* worker);	//	increase worker count by one
	void RemoveWorker(IBuilder* worker);	//	decrease worker count by one
	void AdvanceConstruction(float steps);

	Structure* ToStructure();

	bool NeedRemove() override;
	bool NeedDelete() override;
	void Update(double time, double dt) override;

	GameEntity* ToGameEntity() { return m_game_entity; }
	StructureScheme* GetStructureScheme() { return m_scheme; }
private:

	World* m_world;
	bool m_can_be_deleted;
	int m_budget;
	float m_jobs_elements_left;
	StructureScheme* m_scheme;
	std::vector<IBuilder*> m_workers;
	std::map<IBuilder*, double> m_salary;
	IAction* m_on_finish;
	GameEntity* m_game_entity;
	Scene::TransformNode* m_transform_node;
	Scene::MaterialNode* m_material_node;

	Math::vec3 m_location;
	Math::vec3 m_direction;
};


#endif	//	_H_CONSTRUCTION
