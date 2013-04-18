//#ifndef _H_PUNK_COMPLEX_ENTITY
//#define _H_PUNK_COMPLEX_ENTITY
//
//#include "../config.h"
//#include "solid_entity.h"
//#include <set>
//#include <memory>
//#include "../../math/vec3.h"
//
//namespace Logic
//{
//	class PUNK_LOGIC_MODULE ComplexEntity : public SolidEntity
//	{
//	protected:
//		typedef std::set<SolidEntity*> type;
//		typedef type::iterator iterator;
//		typedef type::const_iterator const_iterator;
//
//		type m_children;
//
//	public:
//
//		ComplexEntity();
//		ComplexEntity(const ComplexEntity& entity);
//		ComplexEntity& operator = (const ComplexEntity& entity);
//		virtual ~ComplexEntity();
//
//		virtual void AddChild(SolidEntity* child);
//		virtual void RemoveChild(SolidEntity* child);
//		virtual int GetChildCount() const;
//
//		iterator begin();
//		const_iterator begin() const;
//		iterator end();
//		const_iterator end() const;
//
//		virtual AbstractEntity* Clone() const;
//		virtual bool Visit(Visitor* v);
//	};
//}
//
//#endif
