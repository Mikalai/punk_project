#ifndef _H_PUNK_RESOURCE_WIN32
#define _H_PUNK_RESOURCE_WIN32

#include "clock_win32.h"
#include "handle_win32.h"
#include "static_string.h"
#include <time.h>
#include <memory>

namespace System
{
	template<class T>
	class Resource
	{
	protected:
		Handle m_handler;
		string m_path_to_storage;
		time_t m_last_access;
		T* m_resource;

	public:

		T* Get();

		const Handle GetHandle() const;
		void SetHandle(Handle handle);

		time_t GetLastTimeAccess() const;

		void SetPathToStorage(const string& path);
		const string& GetPathToStorage() const;

		virtual void DropToHdd() = 0;
		virtual void RestoreFromHdd() = 0;
	};

	/*enum ResourceCodes 
	{
		//
		//	Engine resources
		//
		RESOURCE_TEXTURE	= 1,
		RESOURCE_MESH		= 2,
		RESOURCE_AUDIO		= 3,
		RESOURCE_FONT		= 4,
		//
		//	User resources starts from here
		RESOURCE_USER = 256
	};

	template<class T, class Code>
	class Resource : private HandlerSetter<T, Code>
	{
		std::auto_ptr<T> m_object;		
		time_t m_last_access;
		string m_location;
		bool m_is_available;
	public:

		operator T* ()
		{
			return m_object.get();
		}

		operator const T* () const
		{
			return m_object.get();
		}

		void Unload()
		{
			m_object.reset();
		}

		void Load()
		{
			m_object.reset(new T());
			m_object.get()->Load(m_location);
		}

		void SetLocation(const string& location)
		{
			m_location = location;
		}

		template<class T2, class Code2>
		bool operator < (const Resource<T2, Code2>& r)
		{
			return m_last_access < r.m_last_access;
		}

		~Resource();
	}*/
}

#endif