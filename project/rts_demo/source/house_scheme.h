#ifndef _H_RTS_DEMO_HOUSE_SCHEME
#define _H_RTS_DEMO_HOUSE_SCHEME

#include "structure_scheme.h"

class House;

class HouseScheme : public StructureScheme
{
public:
	HouseScheme();
private:	
	int m_max_capacity;
};

#endif	//	_H_RTS_DEMO_HOUSE_SCHEME