#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <typeinfo>
#include "../config.h"
#include "hresource.h"
#include "../string/string.h"
#include "smart_pointers/proxy.h"
#include "errors/module.h"

namespace System
{
    class PUNK_ENGINE_API Object
	{
	public:
        Object();
        virtual ~Object();

        void SetName(const string& value);
        const string& GetName() const;

        void SetText(const string& value);
        const string& GetText() const;

        void SetOwner(Object* owner);
        const Object* GetOwner() const;
        Object* GetOwner();

        const System::string& GetStorageName() const;
        void SetStorageName(const System::string& name);

        ObjectType GetType() const;
        void SetType(ObjectType type);

        bool IsModified() const;
        void Invalidate();

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

	private:

		/**
		*	If object if modified than it should be saved in the save file as
		*	a whole set. If object is not modified than only a storage name
		*	can be saved
		*/
		bool m_modified;
		ObjectType m_type;
		string m_storage_name;
		string m_name;
		string m_text;
		Object* m_owner;
	};
}

template<class T>
inline T As(System::Object* o)
{
	return dynamic_cast<T>(o);
}

template<class T>
inline T As(const System::Object* o)
{
	return dynamic_cast<T>(o);
}

template<class T, class U>
inline T As(U o)
{
	return dynamic_cast<T>(o);
}

template<class T>
inline bool Is(System::Object* o)
{
	return dynamic_cast<T>(o) != nullptr;
}

template<class T>
inline T Cast(System::Object* o)
{
	T ptr = As<T>(o);
	if (ptr == nullptr && o != nullptr)
		throw System::PunkInvalidCastException(L"Can't cast from " + System::string(typeid(o).name()) + L" to " + System::string(typeid(T).name()));
	return ptr;
}

template<class T, class U>
inline T Cast(U* o)
{
	T ptr = As<T>(o);
	if (ptr == nullptr && o != nullptr)
		throw System::PunkInvalidCastException(L"Can't cast from " + System::string(typeid(o).name()) + L" to " + System::string(typeid(T).name()));
	return ptr;
}

#define safe_delete(V) {delete (V); (V) = 0;}
#define safe_delete_array(V) {delete[] (V); (V) = 0;}

#endif	//	_H_PUNK_SYSTEM_OBJECT
