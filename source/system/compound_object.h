#ifndef _H_PUNK_SYSTEM_COMPOUND_OBJECT
#define _H_PUNK_SYSTEM_COMPOUND_OBJECT

#include <map>
#include "object.h"
#include "smart_pointers/proxy.h"

namespace System
{
	class PUNK_ENGINE CompoundObject : public Object
	{
	public:
		virtual ~CompoundObject();

		bool Add(Object* object);
		
		bool Remove(Object* object);
		bool Remove(const string& name);
		bool Remove(int index);

		Object* Find(const string& name);
		Object* Find(int index);
		const Object* Find(const string& name) const;
		const Object* Find(int index) const;

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

	public:
		typedef std::map<string, int> CollectionCacheType;
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

		virtual bool OnAdd(System::Object* object) { return true; }
		virtual bool OnRemove(System::Object* object) { return true; }
	private:

		CollectionType m_children;
		CollectionCacheType m_cache;
	};
}

#endif	//	_H_PUNK_SYSTEM_COMPOUND_OBJECT