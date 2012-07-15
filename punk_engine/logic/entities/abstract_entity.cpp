#include <iostream>
#include "abstract_entity.h"
#include "solid_entity.h"
#include "complex_entity.h"

namespace Logic
{
	AbstractEntity::AbstractEntity()
		: m_property_collection(new PropertyCollection)
		, m_owner(0)
	{
		//	std::cout << __FUNCSIG__ << std::endl;

		PropertyCollection& pc = *m_property_collection;
		//	using type we can make decision what can we do with it
		pc.RegisterProperty("TYPE")->SetValue(L"ABSTRACT_ENTITY");
		//	using name we can use it
		pc.RegisterProperty("NAME")->SetValue(L"NONAME");
		//	when active we can update this entity
		pc.RegisterProperty("ACTIVE")->SetValue(1);
	}

	AbstractEntity::AbstractEntity(const AbstractEntity& ae)
		: m_property_collection(new PropertyCollection(*ae.m_property_collection.get()))
		, m_owner(0)
	{
	}


	AbstractEntity& AbstractEntity::operator = (const AbstractEntity& e)
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		if (this != &e)
		{
			m_property_collection.reset(new PropertyCollection(*e.m_property_collection.get()));
		}
		return *this;
	}

	AbstractEntity::~AbstractEntity()
	{
		//	std::cout << __FUNCSIG__ << std::endl;
		m_property_collection.reset(0);
	}

	PropertyCollection& AbstractEntity::GetPropertyCollection()
	{
		return *m_property_collection.get();
	}

	const PropertyCollection& AbstractEntity::GetPropertyCollection() const
	{
		return *m_property_collection.get();
	}

	void AbstractEntity::SetOwner(ComplexEntity* e)
	{
		if (m_owner)
		{	
#pragma message "This is not good"
			m_owner->RemoveChild((SolidEntity*)this);
		}
		m_owner = e;
	}

	ComplexEntity* AbstractEntity::GetOwner()
	{
		return m_owner;
	}

	const ComplexEntity* AbstractEntity::GetOwner() const
	{
		return m_owner;
	}
}
