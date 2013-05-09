#ifndef _H_PUNK_STRING_WIN32
#define _H_PUNK_STRING_WIN32

#ifdef _WIN32

#include <vector>
#include <iosfwd>
#include <string>
#include <cstdint>
#include "../../config.h"

//
//	to do list:
//		memory monitoring
//

namespace System
{
	//class PUNK_ENGINE StringError : public std::exception
	//{
	//public:
	//	StringError();
	//	StringError(const wchar_t* message);
	//	~StringError();
	//	virtual const wchar_t* w_what() const;
	//private:
	//	const wchar_t* m_w_what;
	//};

	class PUNK_ENGINE  string
	{
	protected:

		struct Representation;
		Representation* m_rep;
		mutable wchar_t* m_cstring_cache;

	public:
		string();
		explicit string(const char* s);
		string(const wchar_t* s);
        string(const char* s, size_t length);
        string(const wchar_t* s, size_t length);
		string(const string& s);
        explicit string(size_t length);

		string& operator = (const string& s);
		string& operator = (const wchar_t* s);
		string& operator = (const char* s);
		~string();

		wchar_t operator [] (int i) const;
		wchar_t& operator [] (int i);

        const std::string ToStdString() const;
        const std::wstring ToStdWString() const;

        size_t Length() const;
        size_t Size() const;
		string& Erase(int start, int len);
		string& Insert(wchar_t chr, int pos);
		const string Replace(const string& what, const string& with) const;
		const string SubString(int start, int end) const;
		const string Trim(const wchar_t* delimiters) const;
		const std::vector<string> Split(const wchar_t *delimiters) const;

		const wchar_t* Data() const;

		string& operator += (const string& s);
		string& operator += (const wchar_t* s);

        void ToANSI(char*& buffer, size_t& length) const;
        void ToANSI(char* buffer, size_t size) const;

		int ToInt32() const;
		int ToInt32FromHex() const;
		float ToFloat() const;
		double ToDouble() const;

		wchar_t* I_know_what_I_do_just_give_me_the_pointer();

		friend PUNK_ENGINE bool operator == (const string& s1, const string& s2);
		friend PUNK_ENGINE bool operator == (const string& s1, const wchar_t* s2);
		friend PUNK_ENGINE bool operator != (const string& s1, const string& s2);
		friend PUNK_ENGINE bool operator != (const string& s1, const wchar_t* s2);
		friend PUNK_ENGINE bool operator < (const string& s1, const string& s2);
		friend PUNK_ENGINE bool operator < (const string& s1, const wchar_t* s2);


		static const string Convert(int32_t value, int radix = 10);
		static const string Convert(uint32_t value, int radix = 10);
		static const string Convert(int64_t value, int radix = 10);
		static const string Convert(uint64_t value, int radix = 10);
		static const string Convert(int16_t value, int radix = 10);
		static const string Convert(uint16_t value, int radix = 10);
		static const string Convert(int8_t value, int radix = 10);
		static const string Convert(uint8_t value, int radix = 10);
		static const string Convert(signed char value);
		static const string Convert(unsigned char value);
		static const string Convert(float value, int precision = 5);
		static const string Convert(double value, int precision = 5);
		static const string Convert(long double value, int precision = 5);
		static const string Convert(wchar_t value);
		static const string Convert(bool value);
		static const string Convert(void* value);

		static const string Format(const wchar_t* fmt, ...);

		void* operator new (size_t size);
		void operator delete (void* pointer, size_t size);

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
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

	PUNK_ENGINE bool operator == (const string& s1, const string& s2);
	PUNK_ENGINE bool operator == (const string& s1, const wchar_t* s2);
	PUNK_ENGINE bool operator != (const string& s1, const string& s2);
	PUNK_ENGINE bool operator != (const string& s1, const wchar_t* s2);
	PUNK_ENGINE bool operator < (const string& s1, const string& s2);
	PUNK_ENGINE bool operator < (const string& s1, const wchar_t* s2);
	PUNK_ENGINE const string operator + (const string& s1, const string& s2);
	PUNK_ENGINE const string operator + (const string& s1, const wchar_t* s2);
	PUNK_ENGINE const string operator + (const wchar_t* s1, const string& s2);


	/** \class string
	\brief This is a description of the string class
	So simple class
	*/

}


#endif

/**/
#endif
