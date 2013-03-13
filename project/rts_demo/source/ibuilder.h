#ifndef _H_RTS_DEMO_IBUILDER
#define _H_RTS_DEMO_IBUILDER

class Construction;
class StructureScheme;

class IBuilder
{
public:
	virtual int GetWorkerLevel() = 0;
	virtual int GetConstructionProductivity() = 0;	//	construction job elements per hour
	virtual int GetConstructionEngineeringSkill() = 0;
	virtual int EstimateConstructionCost(StructureScheme*) = 0;	
	virtual int GetMilitaryConstructionEngineeringSkillCost() = 0;	
	virtual int GetElectronicEngineeringSkill() = 0;	
	virtual int GetElectronicEngineeringSkillCost() = 0;	
	virtual void Build(Construction* value, double dt) = 0;
	virtual void Pay(int money) = 0;
};

#endif	//	_H_RTS_DEMO_IBUILDER
