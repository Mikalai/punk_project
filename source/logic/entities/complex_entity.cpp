//#include <iostream>
//#include "../visitor/visitor.h"
//#include "complex_entity.h"
//
//namespace Logic
//{
//	ComplexEntity::ComplexEntity()
//		: SolidEntity()
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	ComplexEntity::ComplexEntity(const ComplexEntity& e)
//		: SolidEntity(e)
//		, m_children(e.begin(), e.end())
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	ComplexEntity& ComplexEntity::operator = (const ComplexEntity& e)
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//		SolidEntity::operator = (e);
//		if (this != &e)
//		{
//			m_children = e.m_children;
//		}
//		return *this;
//	}
//
//	ComplexEntity::~ComplexEntity()
//	{
//		//	std::cout << __FUNCSIG__ << std::endl;
//		for (auto it = m_children.begin(); it != m_children.end(); ++it)
//		{
//			delete *it;
//		}
//	}
//
//	void ComplexEntity::AddChild(SolidEntity* e)
//	{
//		e->SetOwner(this);
//		m_children.insert(e);
//	}
//
//	void ComplexEntity::RemoveChild(SolidEntity* e)
//	{
//		m_children.erase(e);
//	}
//
//	ComplexEntity::iterator ComplexEntity::begin()
//	{
//		return m_children.begin();
//	}
//
//	ComplexEntity::const_iterator ComplexEntity::begin() const
//	{
//		return m_children.begin();
//	}
//
//	ComplexEntity::iterator ComplexEntity::end()
//	{
//		return m_children.end();
//	}
//
//	ComplexEntity::const_iterator ComplexEntity::end() const
//	{
//		return m_children.end();
//	}
//
//	AbstractEntity* ComplexEntity::Clone() const
//	{
//		std::unique_ptr<ComplexEntity> result(new ComplexEntity(*this));
//		return result.release();
//	}
//
//	bool ComplexEntity::Visit(Visitor* v)
//	{
//		for (auto it = m_children.begin(); it != m_children.end(); ++it)
//		{
//			if (v->Visit(this))
//				return true;
//		}
//		return false;
//	}
//
//	int ComplexEntity::GetChildCount() const
//	{
//		return m_children.size();
//	}
//
//}
