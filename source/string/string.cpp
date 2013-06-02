#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

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
    string& string::Erase(int start, int len)
	{
        m_buffer.erase(m_buffer.begin() + start, m_buffer.end() + len);
		return *this;
	}

    const string operator + (const char* s1, const string& s2)
	{
		string s3(s1);
		return s3 += s2;
	}

    const string operator + (const string& s1, const char* s2)
	{
		string s3(s1);
		s3 += s2;
		return s3;
	}

	const string operator + (const string& s1, const string& s2)
	{
		string s3(s1);
		s3 += s2;
		return s3;
	}

    bool operator != (const string& s1, const char* s2)
	{
		return !(s1 == s2);
	}

	bool operator != (const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	bool operator == (const string& s1, const string& s2)
	{
		if (s1.Length() != s2.Length())
			return false;
        return s1.m_buffer == s2.m_buffer;
	}

    bool operator == (const string& s1, const char* s2)
	{        
        if (s1.Length() != strlen(s2))
			return false;
        string temp(s2);
        return s1.m_buffer == temp.m_buffer;
	}

	bool operator < (const string& s1, const string& s2)
	{
        return strncmp(s1.Data(), s2.Data(), s1.Length()) < 0;
	}

    bool operator < (const string& s1, const char* s2)
    {
        return false;
        //return strncmp(s1.Data(), s2, s1.Length()) < 0;
	}

    void string::ToANSI(char*& buffer, size_t& size) const
	{
        size = m_buffer.size()+1;
		buffer = new char[size];
		memset(buffer, 0, sizeof(char)*size);
#ifdef _WIN32
        WideCharToMultiByte(CP_ACP, 0, m_buffer, m_buffer.size(), buffer, size, 0, 0);
#elif defined __linux__
        size_t in_size = (m_buffer.size() + 1) * sizeof(char);
        size_t out_size = size;
        auto handle = iconv_open("WCHAR_T", "ANSI");
        iconv(handle, (char**)&m_buffer, &in_size, (char**)&buffer, &out_size);
        iconv_close(handle);
#endif
	}

    void string::ToANSI(char* buffer, size_t size) const
	{
#ifdef _WIN32
		memset(buffer, 0, sizeof(char)*size);
        WideCharToMultiByte(CP_ACP, 0, m_buffer, m_buffer.size(), buffer, size, 0, 0);
#elif defined __linux__
        size_t in_size = (m_buffer.size() + 1) * sizeof(char);
        size_t out_size = size;
        auto handle = iconv_open("WCHAR_T", "ANSI");
        iconv(handle, (char**)&m_buffer, &in_size, (char**)&buffer, &out_size);
        iconv_close(handle);
#endif
	}

    const std::vector<char> string::ToAscii() const
    {
        std::vector<char> result(m_buffer.size()*sizeof(char));
        size_t in_size = (m_buffer.size() + 1) * sizeof(char);
        size_t out_size = result.size();
        auto handle = iconv_open("WCHAR_T", "ANSI");
        char** in = (char**)&m_buffer;
        char** out = (char**)&result[0];
        iconv(handle, in, &in_size, out, &out_size);
        iconv_close(handle);
        return result;
    }

    const std::vector<char> string::ToUtf8() const
    {
        std::vector<char> result(m_buffer.size()*sizeof(char));
        size_t in_size = (m_buffer.size() + 1) * sizeof(char);
        size_t out_size = result.size();
        auto handle = iconv_open("WCHAR_T", "UTF8");
        char** in = (char**)&m_buffer;
        char** out = (char**)&result[0];
        iconv(handle, in, &in_size, out, &out_size);
        iconv_close(handle);
        return result;
    }

    string& string::operator+= (const char* s)
    {
		return *this;
	}

	string& string::operator+= (const string& s)
	{
        m_buffer.insert(m_buffer.end(), s.begin(), s.end());
		return *this;
	}

    string& string::Insert(char chr, int pos)
	{

		return *this;
	}

	const string string::Replace(const string& what, const string& with) const
    {
        string res;
		if (what.Length() == 0)
			return *this;

        auto start_it = m_buffer.begin();
        auto cur_it = start_it;
        auto end_it = m_buffer.end();
        while ((cur_it = std::search(start_it, end_it, what.m_buffer.begin(), what.m_buffer.end())) != end_it)
        {
            res.m_buffer.insert(res.m_buffer.end(), start_it, cur_it);
            res.m_buffer.insert(res.m_buffer.end(), with.begin(), with.end());

            start_it = cur_it;
        }

        return res;
	}

	const string string::SubString(int start, int end) const
	{
        return string(&m_buffer[0] + start, end - start);
	}

    size_t string::Size() const
	{
        return (size_t)(m_buffer.size()*sizeof(char) + sizeof(int));
	}

    size_t string::Length() const
	{
        return m_buffer.size();
	}

    char string::operator[] (int i) const
	{
        return m_buffer[i];
	}

    char& string::operator [] (int i)
	{

        return m_buffer[i];
	}

	string& string::operator = (const char* s)
	{
        m_buffer.clear();
        m_buffer.insert(m_buffer.end(), s, s+strlen(s));
		return *this;
	}

	string::~string()
	{
	}

	string::string()
	{
	}

    string::string(size_t length)
	{		
	}

	string::string(const char* s)
	{
        m_buffer.insert(m_buffer.begin(), s, s+strlen(s));
	}

    string::string(const char* s, size_t length)
	{
        m_buffer.insert(m_buffer.begin(), s, s + length);
	}

	string::string(const string& s)
	{
        m_buffer = s.m_buffer;
	}

	string& string::operator = (const string& s)
	{
		if (this != &s)
		{
            m_buffer = s.m_buffer;
		}
		return *this;
	}

    const char* string::Data() const
	{
        return &m_buffer[0];
	}

	int string::ToInt32() const
	{
        return atoi(&m_buffer[0]);
	}

	int string::ToInt32FromHex() const
	{
        char allowed_symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'x', 'X' };
        int allowd_symbols_count = sizeof(allowed_symbols) / sizeof(char);
        for (int i = 0; i < m_buffer.size(); i++)
		{
			bool ok = false;
			for (int j = 0; j < allowd_symbols_count; j++)
			{
                if (m_buffer[i] == allowed_symbols[j])
				{
					ok = true;
					break;
				}
			}
			if (!ok)
				return 0;
		}
        const char *end = &m_buffer[0];
        const char *start = &m_buffer[0] + m_buffer.size()-1;
        if (end[0] == '0' && (end[1] == 'x' || end[1] == 'X'))
			end += 2;
		int res = 0;


		int base = 1;

		while (1)
		{
			switch(*start)
			{
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                res += base*(*start - '0');
				break;
            case 'a': case 'A':
				res += base*10;
				break;
            case 'b': case 'B':
				res += base*11;
				break;
            case 'c': case 'C':
				res += base*12;
				break;
            case 'd': case 'D':
				res += base*13;
				break;
            case 'e': case 'E':
				res += base*14;
				break;
            case 'f': case 'F':
				res += base*15;
				break;
			}

			base *= 16;

			if (start-- == end)
				break;
		}
		return res;
	}

	float string::ToFloat() const
	{
        return (float)atof(&m_buffer[0]);
	}

	double string::ToDouble() const
	{
        return atof(&m_buffer[0]);
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

        return string(&m_buffer[0] + start, end - start);
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
                if (m_buffer[i] == delimiters[j])
				{
					end = i;
					finish = true;
				}
			}

			if (finish)
			{
                res.push_back(string(&m_buffer[0] + start, end - start).Trim(delimiters));
				start = end+1;
			}
		}
		if (start < (unsigned)Length())
		{
            res.push_back(string(&m_buffer[0] + start, Length() - start).Trim(delimiters));
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
        return std::string(&m_buffer[0], m_buffer.size());
    }

    const std::wstring string::ToStdWString() const
    {
        return std::wstring();
    }

	string::iterator string::begin()
	{
        return m_buffer.begin();
	}

	string::const_iterator string::begin() const
	{
        return m_buffer.begin();
	}

	string::iterator string::end()
	{

        return m_buffer.end();
	}

	string::const_iterator string::end() const
	{
        return m_buffer.end();
	}

}/**/
