#ifndef _H_PUNK_STRING_WIN32
#define _H_PUNK_STRING_WIN32

#ifdef _WIN32

#include <stddef.h>
#include <windows.h>
#include <vector>
#include <exception>
#include <iosfwd>

#ifdef PUNK_STRING_EXPORTS
#define PUNK_STRING_MODULE __declspec(dllexport)
#else
#define PUNK_STRING_MODULE __declspec(dllimport)
#endif

//
//	to do list:
//		memory monitoring
//

namespace System
{	
	class PUNK_STRING_MODULE StringError : public std::exception
	{
	public:
		StringError();
		StringError(const wchar_t* message);
		~StringError();
		virtual const wchar_t* w_what() const;
	private:
		const wchar_t* m_w_what;
	};

	class PUNK_STRING_MODULE  string
	{
	protected:

		struct Representation;
		Representation* m_rep;
		mutable wchar_t* m_cstring_cache;

	public:
		string();
		explicit string(const char* s);
		string(const wchar_t* s);
		string(const char* s, int length);
		string(const wchar_t* s, int length);
		string(const string& s);
		explicit string(int length);

		string& operator = (const string& s);
		string& operator = (const wchar_t* s);
		string& operator = (const char* s);
		~string();

		wchar_t operator [] (int i) const;
		wchar_t& operator [] (int i);

		int Length() const;
		int Size() const;
		string& Erase(int start, int len);
		string& Insert(wchar_t chr, int pos);
		string Replace(const string& what, const string& with) const;
		string SubString(int start, int end) const;
		string Trim(const wchar_t* delimiters) const;
		std::vector<string> Split(const wchar_t *delimiters) const;

		const wchar_t* Data() const;

		string& operator += (const string& s);
		string& operator += (const wchar_t* s);

		void ToANSI(char*& buffer, int& length) const;

		int ToInt32() const;
		int ToInt32FromHex() const;
		float ToFloat() const;
		double ToDouble() const;

		wchar_t* I_know_what_I_do_just_give_me_the_pointer();

		friend PUNK_STRING_MODULE bool operator == (const string& s1, const string& s2);
		friend PUNK_STRING_MODULE bool operator == (const string& s1, const wchar_t* s2);
		friend PUNK_STRING_MODULE bool operator != (const string& s1, const string& s2);
		friend PUNK_STRING_MODULE bool operator != (const string& s1, const wchar_t* s2);
		friend PUNK_STRING_MODULE bool operator < (const string& s1, const string& s2);
		friend PUNK_STRING_MODULE bool operator < (const string& s1, const wchar_t* s2);


		static string Convert(int value, int radix = 10);
		static string Convert(unsigned value, int radix = 10);
		static string Convert(INT64 value, int radix = 10);
		static string Convert(unsigned __int64 value, int radix = 10);
		static string Convert(__int16 value, int radix = 10);
		static string Convert(unsigned __int16 value, int radix = 10);
		static string Convert(__int8 value, int radix = 10);
		static string Convert(unsigned __int8 value, int radix = 10);
		static string Convert(signed char value);
		static string Convert(unsigned char value);
		static string Convert(float value, int precision = 5);
		static string Convert(double value, int precision = 5);
		static string Convert(long double value, int precision = 5);
		static string Convert(wchar_t value);
		static string Convert(bool value);
		static string Convert(void* value);

		static string Format(const wchar_t* fmt, ...);

		void* operator new (size_t size);
		void operator delete (void* pointer, size_t size);

		//
		//	debugging info
		//
	public:
		static unsigned GetTotalMemoryUsed() throw();
		static unsigned GetMemoryUsage() throw();
		static unsigned GetAllocationsCount() throw();
		static unsigned GetFreeingCount() throw();
	private:
		static unsigned int m_total_memory_used;
		static unsigned int m_memory_used;
		static unsigned int m_allocs_count;
		static unsigned int m_frees_count;
	};

	PUNK_STRING_MODULE bool operator == (const string& s1, const string& s2);
	PUNK_STRING_MODULE bool operator == (const string& s1, const wchar_t* s2);
	PUNK_STRING_MODULE bool operator != (const string& s1, const string& s2);
	PUNK_STRING_MODULE bool operator != (const string& s1, const wchar_t* s2);
	PUNK_STRING_MODULE bool operator < (const string& s1, const string& s2);
	PUNK_STRING_MODULE bool operator < (const string& s1, const wchar_t* s2);
	PUNK_STRING_MODULE string operator + (const string& s1, const string& s2);
	PUNK_STRING_MODULE string operator + (const string& s1, const wchar_t* s2);
	PUNK_STRING_MODULE string operator + (const wchar_t* s1, const string& s2);


	/** \class string
	\brief This is a description of the string class
	So simple class
	*/

}


#endif

/**/
#endif
