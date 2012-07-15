#ifndef _H_SIMPLE_ENTITY
#define _H_SIMPLE_ENTITY

#include "../config.h"
#include "solid_entity.h"

namespace Logic
{
	class Visitor;

	class PUNK_LOGIC_MODULE SimpleEntity : public SolidEntity
	{
	public:

		SimpleEntity();
		SimpleEntity(const SimpleEntity& e);
		SimpleEntity& operator = (const SimpleEntity& e);
		virtual ~SimpleEntity() {};

		virtual bool Visit(Visitor* v);
		virtual AbstractEntity* Clone() const;
		//	if m_count > 1 it will decrese m_count and return a clone of this 
		//	entity. Otherwise it will return this
		SimpleEntity* Detach();
	};
}

#endif