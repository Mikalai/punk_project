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
    //class  StringError : public std::exception
    //{
    //public:
    //	StringError();
    //	StringError(const wchar_t* message);
    //	~StringError();
    //	virtual const wchar_t* w_what() const;
    //private:
    //	const wchar_t* m_w_what;
    //};

    class PUNK_ENGINE_API string : public std::wstring
    {
    public:
        string();
        string(const char* s);
        string(const wchar_t* s);
        string(const char* s, size_t length);
        string(const wchar_t* s, size_t length);
        string(const string& s);
        string(const std::wstring& s);
        explicit string(size_t length);

        string& operator = (const string&);
        string& operator = (const wchar_t*) { return *this; }
        string& operator = (const char*);
        ~string();

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

        const std::vector<char> ToAscii() const;
        const std::vector<char> ToUtf8() const;

        int ToInt32() const;
        int ToInt32FromHex() const;
        float ToFloat() const;
        double ToDouble() const;

        static const string Convert(std::int32_t value, int radix = 10);
        static const string Convert(std::uint32_t value, int radix = 10);
        static const string Convert(std::int64_t value, int radix = 10);
        static const string Convert(std::uint64_t value, int radix = 10);
        static const string Convert(std::int16_t value, int radix = 10);
        static const string Convert(std::uint16_t value, int radix = 10);
        static const string Convert(std::int8_t value, int radix = 10);
        static const string Convert(std::uint8_t value, int radix = 10);
        //static const string Convert(signed char value);
        //static const string Convert(unsigned char value);
        static const string Convert(float value, int precision = 5);
        static const string Convert(double value, int precision = 5);
        static const string Convert(long double value, int precision = 5);
        static const string Convert(wchar_t value);
        static const string Convert(bool value);
        static const string Convert(void* value);
        static const string FromUtf8(const char* buffer);
        static const string Format(const char* fmt, ...);

        void* operator new (size_t size);
        void operator delete (void* pointer, size_t size);

        string& arg(std::int8_t value);
        string& arg(std::uint8_t value);
        string& arg(std::int16_t value);
        string& arg(std::uint16_t value);
        string& arg(std::int32_t value);
        string& arg(std::uint32_t value);
        string& arg(std::uint64_t value);
        string& arg(std::int64_t value);
        string& arg(float value);
        string& arg(double value);
        string& arg(const string& value);
        string& arg(bool value);
        string& arg(const char* value);
#ifdef _WIN32
        string& arg(long value);
#endif
        bool EndWith(const string& value) const;
        bool StartWith(const string& value) const;

        const string ToLower() const;
    };

    bool operator == (const string& l, const string& r);
    const string operator + (const string& l, const string& r);

    std::wostream& operator << (std::wostream& stream, const System::string& value);
    std::ostream& operator << (std::ostream& stream, const System::string& value);
}


#endif
