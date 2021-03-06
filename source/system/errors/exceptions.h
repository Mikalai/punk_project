#ifndef _H_PUNK_SYSTEM_EXCEPTIONS
#define _H_PUNK_SYSTEM_EXCEPTIONS

#include <exception>
#include "../../config.h"
#include "../../string/string.h"

namespace System
{
	class PUNK_ENGINE PunkException
	{		
	public:
		PunkException();
		PunkException(const System::string& data);
		virtual ~PunkException();
		const System::string& ToString() const;
	private:
		const System::string GetStack();
		System::string m_data;
	};

	class PUNK_ENGINE PunkInvalidArgumentException : public PunkException
	{
	public:
		PunkInvalidArgumentException() : PunkException(L"PunkInvalidArgumentException") {}
		PunkInvalidArgumentException(const string& msg) : PunkException(L"PunkInvalidArgumentException: " + msg) {}
	};

	class PUNK_ENGINE PunkInvalidCastException : public PunkException
	{
	public:
		PunkInvalidCastException() : PunkException(L"PunkInvalidCastException") {}
		PunkInvalidCastException(const string& msg) : PunkException(L"PunkInvalidCastException: " + msg) {}
	};

	class PUNK_ENGINE PunkNotInitializedException : public PunkException
	{
	public:
		PunkNotInitializedException() : PunkException(L"PunkNotInitializedException") {}
		PunkNotInitializedException(const string& msg) : PunkException(L"PunkNotInitializedException: " + msg) {}
	};

	class PUNK_ENGINE OSException : public PunkException
	{
	public:
		OSException() : PunkException(L"OSException") {}
		OSException(const string& msg) : PunkException(L"OSException: " + msg) {}
	};
}

#endif	//	_H_PUNK_SYSTEM_EXCEPTIONS