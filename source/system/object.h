#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <typeinfo>
#include "../config.h"
#include "hresource.h"
#include "../string/string.h"
#include "smart_pointers/proxy.h"
#include "errors/module.h"
#include "static_information.h"
#include "serializable.h"

#define PUNK_OBJECT(TYPE)\
private:\
    unsigned m_local_index;\
public:\
    virtual System::Rtti* GetType() const { return &Info.Type; }\
    unsigned GetLocalIndex() const { return m_local_index; }\
    void SetLocalIndex(unsigned value) { m_local_index = value; }\
    static System::StaticInormation<TYPE> Info; \
    static Object* Create() { return new TYPE; } \
    friend void Save##TYPE(System::Buffer* buffer, const System::Object* o); \
    friend void Load##TYPE(System::Buffer* buffer, System::Object* o);

#define PUNK_OBJECT_UTIL(TYPE)\
    PUNK_ENGINE_API void Save##TYPE(System::Buffer* buffer, const System::Object* o);\
    PUNK_ENGINE_API void Load##TYPE(System::Buffer* buffer, System::Object* o);

#define PUNK_OBJECT_REG(TYPE, NAME, CODE, SAVE, LOAD, PARENT) \
    System::StaticInormation<TYPE> TYPE::Info{NAME, CODE, SAVE, LOAD, PARENT}

namespace System
{
    class Buffer;

    class PUNK_ENGINE_API Object
	{
	public:
        Object();
        Object(const Object&) = delete;
        Object& operator = (const Object&) = delete;
        virtual ~Object();

        void SetOwner(Object* owner);
        const Object* GetOwner() const;
        Object* GetOwner();

        unsigned GetId() const;
        virtual const string ToString() const;        

        const string& Name() const;
        void Name(const string& value);

	private:
		Object* m_owner;
        unsigned m_id;
        System::string m_name;

    public:
        static unsigned m_id_next;

        PUNK_OBJECT(Object)
	};

    PUNK_OBJECT_UTIL(Object)
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

#define safe_delete(V) {delete (V); (V) = nullptr;}
#define safe_delete_array(V) {delete[] (V); (V) = nullptr;}

#endif	//	_H_PUNK_SYSTEM_OBJECT
