//#include "../visitor/visitor.h"
//#include "entity.h"
//
//namespace Logic
//{
//	ComplexEntity::ComplexEntity() 	
//		: AbstractEntity()
//		, m_owner(0)
//	{}
//
//	ComplexEntity::ComplexEntity(const ComplexEntity& e)	
//		: AbstractEntity(e)
//		, m_owner(e.m_owner)
//		, m_children(e.begin(), e.end())
//	{}
//
//	ComplexEntity& ComplexEntity::operator = (const ComplexEntity& e)
//	{
//		AbstractEntity::operator = (e);
//		if (this != &e)
//		{
//			m_owner = e.m_owner;
//			m_children = e.m_children;
//		}
//		return *this;
//	}
//
//	ComplexEntity::~ComplexEntity()
//	{
//		for (auto it = m_children.begin(); it != m_children.end(); ++it)
//		{
//			delete *it;
//		}
//	}
//
//	void ComplexEntity::AddChild(ComplexEntity* e)
//	{
//		e->SetOwner(this);
//		m_children.insert(e);
//	}
//
//	void ComplexEntity::RemoveChild(ComplexEntity* e)
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
//	ComplexEntity* ComplexEntity::Clone() const
//	{
//		return new ComplexEntity(*this);
//	}
//
//	const Math::vec3& ComplexEntity::GetPosition() const
//	{
//		return m_position;
//	}
//
//	Math::vec3& ComplexEntity::GetPosition() 
//	{
//		return m_position;
//	}
//
//	void ComplexEntity::SetPosition(const Math::vec3& position)
//	{
//		m_position = position;
//	}
//
//	void ComplexEntity::SetOwner(ComplexEntity* e)
//	{
//		if (m_owner)
//			m_owner->RemoveChild(this);
//		m_owner = e;
//	}
//
//	ComplexEntity* ComplexEntity::GetOwner()
//	{
//		return m_owner;
//	}
//
//	const ComplexEntity* ComplexEntity::GetOwner() const
//	{
//		return m_owner;
//	}
//
//	void ComplexEntity::SetOrientation(const Math::vec3& v)
//	{
//		m_orientation = v;
//	}
//
//	Math::vec3& ComplexEntity::GetOrientation()
//	{
//		return m_orientation;
//	}
//
//	const Math::vec3& ComplexEntity::GetOrientation() const
//	{
//		return m_orientation;
//	}
//	//
//	//int ComplexEntity::CountOf(const wchar_t* type) const
//	//{
//	//	int count = 0;
//	//	for (auto it = m_children.begin(); it != m_children.end(); ++it)
//	//	{
//	//		PropertyCollection& pc = (*it)->GetPropertyCollection();
//	//		if (pc.HasProperty("TYPE"))
//	//		{
//	//			if (wcscmp(pc["TYPE"].AsString(), type) == 0)
//	//				count ++;
//	//		}
//	//	}
//	//	return count;
//	//}
//	//
//	//std::vector<ComplexEntity*> ComplexEntity::FindByType(const wchar_t* type) 
//	//{
//	//	std::vector<ComplexEntity*> res;
//	//	for (auto it = m_children.begin(); it != m_children.end(); ++it)
//	//	{
//	//		PropertyCollection& pc = (*it)->GetPropertyCollection();
//	//		if (pc.HasProperty("TYPE"))
//	//		{
//	//			if (wcscmp(pc["TYPE"].AsString(), type) == 0)
//	//			{
//	//				res.push_back((*it));
//	//			}
//	//		}
//	//	}
//	//	return res;
//	//}
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
//}