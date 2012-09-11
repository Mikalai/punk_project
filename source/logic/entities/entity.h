#ifndef _H_ITEM
#define _H_ITEM

#include "abstract_entity.h"
#include <set>
#include <memory>
#include "../../math/vec3.h"

namespace Logic
{
	//class ComplexEntity : public AbstractEntity
	//{
	//protected:

	//	typedef std::set<AbstractEntity*> type;
	//	typedef type::iterator iterator;
	//	typedef type::const_iterator const_iterator;
	//	ComplexEntity* m_owner;
	//	type m_children;	

	//	Math::vec3 m_position;		//	in parent space
	//	Math::vec3 m_orientation;	//	in parent space

	//public:

	//	ComplexEntity();
	//	ComplexEntity(const ComplexEntity& entity);
	//	ComplexEntity& operator = (const ComplexEntity& entity);
	//	virtual ~ComplexEntity();

	//	void AddChild(ComplexEntity* child);
	//	void RemoveChild(ComplexEntity* child);

	//	iterator begin();
	//	const_iterator begin() const;
	//	iterator end();
	//	const_iterator end() const;

	//	virtual ComplexEntity* Clone() const;

	//	void SetPosition(const Math::vec3& position);
	//	Math::vec3& GetPosition();
	//	const Math::vec3& GetPosition() const;

	//	void SetOrientation(const Math::vec3& orientation);
	//	Math::vec3& GetOrientation();
	//	const Math::vec3& GetOrientation() const;

	//	void SetOwner(ComplexEntity* e);
	//	ComplexEntity* GetOwner();
	//	const ComplexEntity* GetOwner() const;

	//	int CountOf(const wchar_t* type) const;
	//	std::vector<ComplexEntity*> FindByType(const wchar_t* type);

	//	virtual bool Visit(Visitor* v);
	//};
}

#endif
