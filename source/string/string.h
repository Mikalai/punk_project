#ifndef _H_PUNK_STRING
#define _H_PUNK_STRING

#include <vector>
#include <iosfwd>
#include <string>
#include <cstdint>
#include "../config.h"

#ifdef __linux__
#include <iconv.h>
#endif

//
//	to do list:
//		memory monitoring
//

namespace System
{
    //class PUNK_ENGINE_PUBLIC StringError : public std::exception
	//{
	//public:
	//	StringError();
	//	StringError(const wchar_t* message);
	//	~StringError();
	//	virtual const wchar_t* w_what() const;
	//private:
	//	const wchar_t* m_w_what;
	//};

    class PUNK_ENGINE_PUBLIC string
	{
	public:
        typedef std::vector<char>::iterator iterator;
        typedef std::vector<char>::const_iterator const_iterator;

	public:
		string();
        string(const char* s);
		string(const wchar_t* s);
        string(const char* s, size_t length);
        string(const wchar_t* s, size_t length);
		string(const string& s);
        explicit string(size_t length);

		string& operator = (const string& s);
		string& operator = (const wchar_t* s);
		string& operator = (const char* s);
		~string();

        char operator [] (int i) const;
        char& operator [] (int i);

        const std::string ToStdString() const;
        const std::wstring ToStdWString() const;

        size_t Length() const;
        size_t Size() const;
		string& Erase(int start, int len);
        string& Insert(char chr, int pos);
		const string Replace(const string& what, const string& with) const;
		const string SubString(int start, int end) const;
        const string Trim(const char* delimiters) const;
        const std::vector<string> Split(const char *delimiters) const;

        const char* Data() const;

		string& operator += (const string& s);
        string& operator += (const char* s);

        void ToANSI(char*& buffer, size_t& length) const;
        void ToANSI(char* buffer, size_t size) const;

        const std::vector<char> ToAscii() const;
        const std::vector<char> ToUtf8() const;

		int ToInt32() const;
		int ToInt32FromHex() const;
		float ToFloat() const;
		double ToDouble() const;

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

        static const string Format(const char* fmt, ...);

		void* operator new (size_t size);
		void operator delete (void* pointer, size_t size);

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

        string& arg(int8_t value) { return *this; }
        string& arg(uint8_t value) { return *this; }
        string& arg(int16_t value) { return *this; }
        string& arg(uint16_t value) { return *this; }
        string& arg(int32_t value) { return *this; }
        string& arg(uint32_t value) { return *this; }
        string& arg(int64_t value) { return *this; }
        string& arg(uint64_t value) { return *this; }
        string& arg(float value) { return *this; }
        string& arg(double value) { return *this; }
        string& arg(const string& value) { return *this; }
        string& arg(bool value) { return *this; }
        bool EndWith(const string& value) const { return false; }
        bool StartWith(const string& value) const { return false; }

        const string AsLower() const { return *this; }
        string& ToLower() { return *this; }

    private:
        //  UTF8
        std::vector<char> m_buffer;

        friend bool operator == (const string& s1, const string& s2);
        friend  bool operator == (const string& s1, const char* s2);
        friend  bool operator != (const string& s1, const string& s2);
        friend  bool operator != (const string& s1, const char* s2);
        friend  bool operator < (const string& s1, const string& s2);
        friend  bool operator < (const string& s1, const char* s2);
        friend  const string operator + (const string& s1, const string& s2);
        friend  const string operator + (const string& s1, const char* s2);
        friend  const string operator + (const char* s1, const string& s2);
	};

    PUNK_ENGINE_PUBLIC bool operator == (const string& s1, const string& s2);
    PUNK_ENGINE_PUBLIC bool operator == (const string& s1, const char* s2);
    PUNK_ENGINE_PUBLIC bool operator != (const string& s1, const string& s2);
    PUNK_ENGINE_PUBLIC bool operator != (const string& s1, const char* s2);
    PUNK_ENGINE_PUBLIC bool operator < (const string& s1, const string& s2);
    PUNK_ENGINE_PUBLIC bool operator < (const string& s1, const char* s2);
    PUNK_ENGINE_PUBLIC const string operator + (const string& s1, const string& s2);
    PUNK_ENGINE_PUBLIC const string operator + (const string& s1, const char* s2);
    PUNK_ENGINE_PUBLIC const string operator + (const char* s1, const string& s2);

}


#endif
