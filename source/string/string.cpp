#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WIN32
#include <Windows.h>
#elif defined __gnu_linux__
#include "wchar.h"
#endif

#include <clocale>
#include <cctype>
#include <vector>
#include <algorithm>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <istream>
#include <ostream>
#include "../system/logger.h"
#include "string.h"
#include <string.h>

namespace System
{
    bool ConvertByteArray(const char* from, const char* to, void* inp, size_t inp_size, void* outp, size_t* outp_size)
    {
#ifdef _WIN32
        int size = WideCharToMultiByte(CP_UTF8, 0, &m_buffer[0], m_buffer.size(), 0, 0, 0, 0);
        std::vector<char> buffer(size);
        WideCharToMultiByte(CP_UTF8, 0, &m_buffer[0], m_buffer.size(), &buffer[0], size, 0, 0);
#elif defined __gnu_linux__
        if (!outp)
        {
            std::vector<char> result(inp_size*8);
            *outp_size = result.size();
            iconv_t handle = iconv_open(to, from);
            if (handle == (iconv_t)-1)
            {
                *outp_size = 0;
                return false;
            }
            size_t initial_size = *outp_size;
            char* out = (char*)&result[0];
            if (iconv(handle, (char**)&inp, &inp_size, (char**)&out, outp_size) == -1)
            {
                *outp_size = 0;
                return false;
            }
            size_t actual_size = initial_size - *outp_size;
            *outp_size = actual_size;
            iconv_close(handle);
        }
        else
        {
            auto handle = iconv_open(to, from);
            iconv(handle, (char**)&inp, &inp_size, (char**)&outp, outp_size);
            iconv_close(handle);
        }
        return true;
#endif
    }

    string& string::Erase(int start, int len)
	{
        erase(begin() + start, begin() + start + len);
		return *this;
	}

    const std::vector<char> string::ToAscii() const
    {
        size_t inp_size = size() * sizeof(std::wstring::value_type);
        size_t outp_size;        
        void* inp = (void*)c_str();
        if (!ConvertByteArray("WCHAR_T", "ASCII", inp, inp_size, nullptr, &outp_size))
            return std::vector<char>();
        std::vector<char> buffer(outp_size);
        if (!ConvertByteArray("WCHAR_T", "ASCII", inp, inp_size, (void*)&buffer[0], &outp_size))
            return std::vector<char>();
        return buffer;
    }

    const std::vector<char> string::ToUtf8() const
    {
        size_t inp_size = size() * sizeof(std::wstring::value_type);
        size_t outp_size;        
        void* inp = (void*)c_str();
        if (!ConvertByteArray("WCHAR_T", "UTF8", inp, inp_size, nullptr, &outp_size))
            return std::vector<char>();
        std::vector<char> buffer(outp_size);
        if (!ConvertByteArray("WCHAR_T", "UTF8", inp, inp_size, (void*)&buffer[0], &outp_size))
            return std::vector<char>();
        return buffer;
    }

	const string string::Replace(const string& what, const string& with) const
    {
        string res = *this;
        size_t pos = 0;
        while ((pos = res.find(what, pos)) != npos)
        {
            res = res.replace(pos, what.size(), with);
        }
        return res;
	}

	const string string::SubString(int start, int end) const
	{        
        return substr(start, end);
	}

    size_t string::Size() const
	{
        return size()*sizeof(wchar_t);
	}

    size_t string::Length() const
	{
        return size();
	}

    wchar_t string::operator[] (int i) const
	{
        return std::wstring::operator [](i);
	}

    wchar_t& string::operator [] (int i)
	{
        return std::wstring::operator [](i);
	}

	string::~string()
    {}

    string::string() : std::wstring()
    {}

    string::string(const std::wstring& s) : std::wstring(s)
    {}

    string::string(const wchar_t *s) : std::wstring(s)
    {}

    string::string(const wchar_t *s, size_t length) : std::wstring(s, length)
    {}

    string::string(size_t length) : std::wstring(length, L' ')
    {}

	string::string(const char* s)
	{        
        size_t inp_size = strlen(s);
        if (inp_size == 0)
            return;
        size_t outp_size;
        void* inp = (void*)s;
        if (!ConvertByteArray("ASCII", "WCHAR_T", inp, inp_size, nullptr, &outp_size))
            return;
        resize(outp_size / sizeof(wchar_t));
        if (!ConvertByteArray("ASCII", "WCHAR_T", inp, inp_size, (void*)&at(0), &outp_size))
            return;
	}

    string::string(const char* s, size_t length)
	{
        if (length == 0)
            return;
        size_t inp_size = length;
        size_t outp_size;
        void* inp = (void*)s;
        if (!ConvertByteArray("ASCII", "WCHAR_T", inp, inp_size, nullptr, &outp_size))
            return;
        resize(outp_size / sizeof(wchar_t));
        if (!ConvertByteArray("ASCII", "WCHAR_T", inp, inp_size, (void*)&at(0), &outp_size))
            return;
	}

	string::string(const string& s)
        : std::wstring(s)
	{        
	}

	string& string::operator = (const string& s)
	{
        std::wstring::operator =(s);
	}

    const char* string::Data() const
	{
        return (const char*)c_str();
	}

	int string::ToInt32() const
	{
#ifdef _WIN32
        return _wtoi(&m_buffer[0]);
#elif defined __gnu_linux__
        std::wistringstream stream(*this);
        int result;
        stream >> result;
        return result;
#endif
	}

	int string::ToInt32FromHex() const
	{
        std::wistringstream stream(*this);
        int result;
        stream >> result;
        return result;
	}

	float string::ToFloat() const
	{
#ifdef _WIN32
        return (float)_wtof(&m_buffer[0]);
#elif defined __gnu_linux__
        std::wistringstream stream(*this);
        float result;
        stream >> result;
        return result;
#endif
	}

	double string::ToDouble() const
	{
#ifdef _WIN32
        return _wtof(&m_buffer[0]);
#elif defined __gnu_linux__
        std::wistringstream stream(*this);
        double result;
        stream >> result;
        return result;
#endif
	}

	const string string::Convert(int32_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(uint32_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(signed char value)
	{
        char buf[16];
		buf[0] = value;
		buf[1] = 0;
		return string(buf);
	}

	const string string::Convert(unsigned char value)
	{
        char buf[16];
		buf[0] = value;
		buf[1] = 0;
		return string(buf);
	}

	const string string::Convert(int16_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(uint16_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(int8_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(uint8_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(int64_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(uint64_t value, int radix)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(float value, int precision)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

	const string string::Convert(double value, int precision)
	{
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
	}

    const string string::Convert(long double value, int precision)
    {
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
    }

    const string string::Convert(wchar_t value)
    {
        std::wstringstream str;
        str << value;
        return string(str.str().c_str());
    }

	const string string::Convert(bool value)
	{
		if (value)
			return L"True";
		return L"False";
	}

	const string string::Convert(void* value)
	{
#ifdef _WIN64
        char buf[128];
		_ui64tow_s((int64_t)value, buf, 128, 16);
		return string(buf);
#else
        std::stringstream stream;
        stream << value;
        return string(stream.str().c_str());
#endif
	}

    const string string::Format(const char* fmt, ...)
	{
//#define FORMAT_MAX_LENGTH 8192
//		char buffer[FORMAT_MAX_LENGTH];
//		memset(buffer, 0, sizeof(buffer[0])*FORMAT_MAX_LENGTH);
//		va_list argumentPointer;
//		va_start(argumentPointer, fmt);
//        swprintf(
//        snprintf(buffer, fmt, argumentPointer);
//		va_end(argumentPointer);
//#undef	FORMAT_MAX_LENGTH
        return string();
	}

    const string string::Trim(const char* delimiters) const
	{
        unsigned delLength = (unsigned)strlen(delimiters);
		unsigned strLength = Length();
		unsigned start = 0;
		unsigned end = strLength;
		for (unsigned i = 0; i < strLength; i++)
		{
			bool finish = true;
			for (unsigned j = 0; j < delLength; j++)
			{
				if ((*this)[i] == delimiters[j])
				{
					start++;
					finish = false;
					break;
				}
			}
			if (finish)
				break;
		}

		for (int i = strLength-1; i >= 0; i--)
		{
			bool finish = true;
			for (unsigned j = 0; j < delLength; j++)
			{
				if ((*this)[i] == delimiters[j])
				{
					end--;
					finish = false;
					break;
				}
			}
			if (finish)
				break;
		}

        return string(c_str() + start, end - start);
	}

    const std::vector<string> string::Split(const char *delimiters) const
	{
		unsigned start = 0;
		unsigned end = Length();
		std::vector<string> res;
		for (unsigned i = 0; i < (unsigned)Length(); i++)
		{
			bool finish = false;
            for (unsigned j = 0; j < strlen(delimiters); j++)
			{
                if (at(i) == delimiters[j])
				{
					end = i;
					finish = true;
				}
			}

			if (finish)
			{
                res.push_back(string(c_str() + start, end - start).Trim(delimiters));
				start = end+1;
			}
		}
		if (start < (unsigned)Length())
		{
            res.push_back(string(c_str() + start, Length() - start).Trim(delimiters));
		}/**/
		return res;
	}

	void* string::operator new(size_t size)
	{
		return malloc(size);
	}

	void string::operator delete(void* pointer, size_t size)
	{
		if (pointer)
			free(pointer);
	}

    bool string::Save(std::ostream& stream) const
	{
	}

	bool string::Load(std::istream& stream)
	{

	}

    const std::string string::ToStdString() const
    {
        std::vector<char> buf = ToAscii();
        return std::string(&buf[0], buf.size());
    }

    const std::wstring string::ToStdWString() const
    {
        return std::wstring();
    }

    bool operator == (const string& l, const string& r)
    {
        return operator == ((std::wstring&)l, (std::wstring&)r);
    }

    const string operator + (const string& l, const string& r)
    {
        return operator + ((std::wstring&)l, (std::wstring&)r);
    }

    std::wostream& operator << (std::wostream& stream, const System::string& value)
    {
        stream << &value.at(0);
        return stream;
    }

    std::ostream& operator << (std::ostream& stream, const System::string& value)
    {
        std::string s = value.ToStdString();
        stream << s;
        return stream;
    }

    const string string::ToLower() const
    {
        string result = *this;

        std::transform(result.begin(), result.end(), result.begin(), [](const wchar_t& c) -> wchar_t
        {
            std::locale loc;
            return std::use_facet<std::ctype<wchar_t>>(loc).tolower(c);
        });

        return result;
    }

    bool string::EndWith(const string &value) const
    {
        auto pos = find(value);
        return pos != npos;
    }

    bool string::StartWith(const string &value) const
    {
        auto pos = find(value);
        return pos != npos;
    }

    string& string::arg(int8_t value) { return *this; }
    string& string::arg(uint8_t value) { return *this; }
    string& string::arg(int16_t value) { return *this; }
    string& string::arg(uint16_t value) { return *this; }
    string& string::arg(int32_t value) { return *this; }
    string& string::arg(uint32_t value) { return *this; }
    string& string::arg(uint64_t value) { return *this; }
    string& string::arg(int64_t value) { return *this; }
    string& string::arg(float value) { return *this; }
    string& string::arg(double value) { return *this; }
    string& string::arg(const string& value) { return *this; }
    string& string::arg(bool value) { return *this; }
    string& string::arg(const char* value) { return *this; }

}/**/
