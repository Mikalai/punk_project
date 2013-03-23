#include "building.h"

class HouseScheme;

class House : public Building
{
public:
	virtual void Update(double time, double dt) override;
	virtual bool NeedRemove() override;
	virtual bool NeedDelete() override;

private:
	House(StructureScheme*);

	int m_capacity;
	int m_max_capacity;

	friend class HouseScheme;
};
