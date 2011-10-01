#ifndef _H_PUNK_RESOURCE_WIN32
#define _H_PUNK_RESOURCE_WIN32

#include "clock_win32.h"
#include "handle_win32.h"
#include "static_string.h"
#include <time.h>
#include <memory>

namespace System
{

	enum ResourceCodes 
	{
		//
		//	Engine resources
		//
		RESOURCE_TEXTURE	= 1,
		RESOURCE_MESH		= 2,
		RESOURCE_AUDIO		= 3,
		RESOURCE_FONT		= 4,
		RESOURCE_IMAGE		= 5,
		//
		//	User resources starts from here
		RESOURCE_USER = 256
	};

	class BaseResource
	{
	protected:
		Handle m_handler;
		time_t m_last_access;

	public:
		virtual ~BaseResource()
		{
		}

		const Handle GetHandle() const
		{
			return m_handler;
		}

		void SetHandle(Handle handle)
		{
			m_handler = handle;
		}

		time_t GetLastTimeAccess() const
		{
			return m_last_access;
		}

		void SetPathToStorage(const string& path)
		{
		}

		const string& GetPathToStorage() const
		{
			return string();
		}		
	};

	template<class T>
	class Resource : public BaseResource
	{
	protected:
		T* m_resource;
	public:

		Resource()
		{
			m_resource = new T();
		}

		Resource(const Resource& res)
		{
			m_handler = res.m_handler;
			m_last_access = res.m_last_access;
			m_resource = res.m_resource;
		}

		Resource& operator = (const Resource& res)
		{
			if (this != &res)
			{
				m_handler = res.m_handler;
				m_last_access = res.m_last_access;
				m_resource = res.m_resource;
			}
			return *this;
		}

		virtual ~Resource()
		{
			delete m_resource;
			m_resource = 0;
		}

		T* Get()
		{
			if (!m_resource)
				RestoreFromHdd();

			time(&m_last_access);

			return m_resource;
		}

		void DropToHdd()
		{
			System::Buffer buffer;
			buffer.WriteUnsigned64(m_handler.Id());
			m_resource->Store(buffer);
			System::string filename = System::string::Convert(m_handler.Id());
			System::BinaryFile::Save(filename, buffer);
			delete m_resource;
			m_resource = 0;
		}

		void RestoreFromHdd()
		{
			System::Buffer buffer;

			if (m_resource)
				throw System::SystemError(L"Nothing to restore. Resource was not dropped to hdd");

			System::string filename = System::string::Convert(m_handler.Id());
			System::BinaryFile::Load(filename, buffer);
			m_handler.SetID(buffer.ReadUnsigned64());
			m_resource = new T();
			m_resource->Restore(buffer);
		}
	};
}

#endif