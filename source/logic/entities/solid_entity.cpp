//#include <iostream>
//#include "solid_entity.h"
//#include "../visitor/visitor.h"
//
//namespace Logic
//{
//	SolidEntity::SolidEntity()
//		: AbstractEntity()
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//		PropertyCollection& pc = GetPropertyCollection();
//		pc["TYPE"].SetValue(L"SOLID");
//		pc["WEIGHT"].SetValue(0);
//	}
//
//
//	SolidEntity::SolidEntity(const SolidEntity& e)
//		: AbstractEntity(e)
//		, m_position(e.m_position)
//		, m_orientation(e.m_orientation)
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	SolidEntity& SolidEntity::operator = (const SolidEntity& e)
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		AbstractEntity::operator= (e);
//
//		if (this != &e)
//		{
//			m_position = e.m_position;
//			m_orientation = e.m_orientation;
//		}
//		return *this;
//	}
//
//	bool SolidEntity::Visit(Visitor* v)
//	{
//		return true;
//	}
//
//	const Math::vec3& SolidEntity::GetPosition() const
//	{
//		return m_position;
//	}
//
//	Math::vec3& SolidEntity::GetPosition()
//	{
//		return m_position;
//	}
//
//	void SolidEntity::SetPosition(const Math::vec3& position)
//	{
//		m_position = position;
//	}
//
//
//	void SolidEntity::SetOrientation(const Math::vec3& v)
//	{
//		m_orientation = v;
//	}
//
//	Math::vec3& SolidEntity::GetOrientation()
//	{
//		return m_orientation;
//	}
//
//	const Math::vec3& SolidEntity::GetOrientation() const
//	{
//		return m_orientation;
//	}
//}
