//#ifndef _H_ABSTRACT_ENTITY
//#define _H_ABSTRACT_ENTITY
//
//#include <memory>
//#include "../config.h"
//#include "../property/property_collection.h"
//
//namespace System { class Event; }
//
//namespace Logic
//{
//	// used to get fast access to property collection
//#define DECLARE_PROPERTY_COLLECTION PropertyCollection& pc = GetPropertyCollection();
//
//	class Visitor;
//	class ComplexEntity;
//
//	class PUNK_LOGIC_MODULE AbstractEntity
//	{
//		std::unique_ptr<PropertyCollection> m_property_collection;
//		///	Only complex entity can own an entity
//		mutable ComplexEntity* m_owner;
//
//	public:
//
//		AbstractEntity();
//		AbstractEntity(const AbstractEntity& a);
//		AbstractEntity& operator = (const AbstractEntity& a);
//
//		PropertyCollection& GetPropertyCollection();
//		const PropertyCollection& GetPropertyCollection() const;
//
//		void SetOwner(ComplexEntity* e);
//		ComplexEntity* GetOwner();
//		const ComplexEntity* GetOwner() const;
//
//		virtual bool Visit(Visitor* v) = 0;
//		virtual AbstractEntity* Clone() const = 0;
//		virtual void Store(char* buffer) {}
//		virtual ~AbstractEntity();
//	};
//}
//
//#endif
