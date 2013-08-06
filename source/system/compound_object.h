#ifndef _H_PUNK_SYSTEM_COMPOUND_OBJECT
#define _H_PUNK_SYSTEM_COMPOUND_OBJECT

#include <map>
#include "object.h"
#include "smart_pointers/proxy.h"

namespace System
{
    class PUNK_ENGINE_API CompoundObject : public Object
	{
	public:
        CompoundObject();
        CompoundObject(const CompoundObject&) = delete;
        CompoundObject& operator = (const CompoundObject&) = delete;
        virtual const string ToString() const;
		virtual ~CompoundObject();

		bool Add(Object* object);
		
        bool Remove(Object* object, bool depth = false);        
		bool Remove(int index);

        Object* Find(int index);        
        const Object* Find(int index) const;        

        virtual void Save(Buffer* buffer) const;
        virtual void Load(Buffer* buffer);

	public:
		typedef std::vector<Object*> CollectionType;
		typedef CollectionType::iterator iterator;
		typedef CollectionType::const_iterator const_iterator;

		iterator begin() { return m_children.begin(); }
		const_iterator begin() const { return m_children.begin(); }
		iterator end() { return m_children.end(); }
		const_iterator end() const { return m_children.end(); }
		void erase(iterator it) { m_children.erase(it); }
		void clear() { m_children.clear(); }

	protected:

        virtual bool OnAdd(System::Object*) { return true; }
        virtual bool OnRemove(System::Object*) { return true; }

		CollectionType m_children;

        PUNK_OBJECT(CompoundObject)
	};

    /**
      * if child had parent, it will be replaced, and from
      * previous parent child will be removed
      */
    void PUNK_ENGINE_API Bind(CompoundObject* parent, Object* child);

}

#endif	//	_H_PUNK_SYSTEM_COMPOUND_OBJECT
