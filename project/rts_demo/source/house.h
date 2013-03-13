#include "building.h"

class House : public Building
{
public:
	House(StructureScheme*);
	virtual void Update(double time, double dt) override;
	virtual bool NeedRemove() override;
	virtual bool NeedDelete() override;

private:
	int m_capacity;
	int m_max_capacity;
};
