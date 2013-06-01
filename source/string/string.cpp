#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

#include <vector>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <istream>
#include <ostream>
#include "../system/logger.h"
#include "string.h"

namespace System
{
	struct string::Representation
	{
		wchar_t* m_data;
		int m_length;
		int m_useCount;
		Representation(const wchar_t* data, int length);
		Representation(const char* data, int length);
		Representation(int length);
		~Representation();

		Representation* GetOwnCopy();
		void Assign(const wchar_t* data, int length);
		void Assign(const char* data, int length);
		void Append(const wchar_t* data, int length);
		void Erase(int start, int len);
		void Insert(wchar_t chr, int pos);

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

	private:
		Representation(const Representation&);
		Representation& operator = (const Representation&);
	};


	//StringError::StringError() : std::exception(), m_w_what(0)
	//{
	//}

	//StringError::StringError(const wchar_t* message) : std::exception(), m_w_what(message) {}

	//StringError::~StringError()
	//{
	//}

	//const wchar_t * StringError::w_what() const
	//{
	//	return m_w_what;
	//}

	unsigned string::m_allocs_count = 0;
	unsigned string::m_frees_count = 0;
	unsigned string::m_memory_used = 0;
	unsigned string::m_total_memory_used = 0;

	string& string::Erase(int start, int len)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->Erase(start, len);
		return *this;
	}

	const string operator + (const wchar_t* s1, const string& s2)
	{
		string s3(s1);
		return s3 += s2;
	}

	const string operator + (const string& s1, const wchar_t* s2)
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

	bool operator != (const string& s1, const wchar_t* s2)
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
		return wmemcmp(s1.m_rep->m_data, s2.m_rep->m_data, s1.Length()) == 0;
	}

	bool operator == (const string& s1, const wchar_t* s2)
	{
		if (s1.Length() != wcslen(s2))
			return false;
		return wmemcmp(s1.m_rep->m_data, s2, s1.m_rep->m_length) == 0;
	}

	bool operator < (const string& s1, const string& s2)
	{
		return wcscmp(s1.Data(), s2.Data()) < 0;
	}

	bool operator < (const string& s1, const wchar_t* s2)
	{
		return wcscmp(s1.Data(), s2) < 0;
	}

    void string::ToANSI(char*& buffer, size_t& size) const
	{
		size = m_rep->m_length + 1;
		buffer = new char[size];
		memset(buffer, 0, sizeof(char)*size);
		WideCharToMultiByte(CP_ACP, 0, m_rep->m_data, m_rep->m_length, buffer, size, 0, 0);
	}

    void string::ToANSI(char* buffer, size_t size) const
	{
		memset(buffer, 0, sizeof(char)*size);
		WideCharToMultiByte(CP_ACP, 0, m_rep->m_data, m_rep->m_length, buffer, size, 0, 0);
	}

	string& string::operator+= (const wchar_t* s)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->Append(s, wcslen(s));
		return *this;
	}

	string& string::operator+= (const string& s)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->Append(s.m_rep->m_data, s.m_rep->m_length);
		return *this;
	}

	string& string::Insert(wchar_t chr, int pos)
	{
		if (pos > m_rep->m_length)
			out_error() << L"Index out of range in string::insert" << std::endl;

		m_rep = m_rep->GetOwnCopy();
		m_rep->Insert(chr, pos);
		return *this;
	}

	const string string::Replace(const string& what, const string& with) const
	{
		if (what.Length() == 0)
			return *this;

		int offset = 0;
		const wchar_t* start = m_rep->m_data;
		string s1(*this);

		do
		{
			start = s1.m_rep->m_data;
			const wchar_t* next = wcsstr(s1.m_rep->m_data + offset, what.m_rep->m_data);

			if (!next)
				return s1;
			string s2(s1.m_rep->m_data + (next - start) + what.Length());
			s1 = string(s1.m_rep->m_data, next - start) + with + s2;

			offset = next - start + with.Length();
		}
		while (1);
	}

	const string string::SubString(int start, int end) const
	{
		return string(m_rep->m_data + start, end - start);
	}

    size_t string::Size() const
	{
        return (size_t)(m_rep->m_length*sizeof(wchar_t) + sizeof(int));
	}

    size_t string::Length() const
	{
		return m_rep->m_length;
	}

	wchar_t string::operator[] (int i) const
	{
		return m_rep->m_data[i];
	}

	wchar_t& string::operator [] (int i)
	{
		m_rep = m_rep->GetOwnCopy();
		return m_rep->m_data[i];
	}

	string& string::operator = (const wchar_t* s)
	{
		if (m_rep->m_useCount == 1)
			m_rep->Assign(s, wcslen(s));
		else
		{
			m_rep->m_useCount--;
			m_rep = new Representation(s, wcslen(s));
		}
		return *this;
	}

	string& string::operator = (const char* s)
	{
		if (m_rep->m_useCount == 1)
			m_rep->Assign(s, strlen(s));
		else
		{
			m_rep->m_useCount--;
			m_rep = new Representation(s, strlen(s));
		}
		return *this;
	}

	string::~string()
	{
		if (--m_rep->m_useCount == 0)
		{
			delete m_rep;
			m_rep = 0;
		}
	}

	string::string()
	{
		m_rep = new Representation(L"", 0);
		m_cstring_cache = 0;
	}

    string::string(size_t length)
	{
		m_rep = new Representation(length);
	}

	string::string(const char* s)
	{
		if (s != 0)
		{
			m_rep = new Representation(s, strlen(s));
		}
		else
		{
			const char* tmp = "NULL";
			m_rep = new Representation(tmp, strlen(tmp));
		}
		m_cstring_cache = 0;
	}

	string::string(const wchar_t* s)
	{
		if (s != 0)
		{
			m_rep = new Representation(s, wcslen(s));
			m_cstring_cache = 0;
		}
		else
		{
			const wchar_t* tmp = L"NULL";
			m_rep = new Representation(tmp, wcslen(tmp));
		}
	}

    string::string(const char* s, size_t length)
	{
		m_rep = new Representation(s, length);
		m_cstring_cache = 0;
	}

    string::string(const wchar_t* s, size_t length)
	{
		m_rep = new Representation(s, length);
		m_cstring_cache = 0;
	}

	string::string(const string& s)
	{
		s.m_rep->m_useCount++;
		m_rep = s.m_rep;
		m_cstring_cache = 0;
	}

	string& string::operator = (const string& s)
	{
		if (this != &s)
		{
			if (--m_rep->m_useCount == 0)
				delete m_rep;
			s.m_rep->m_useCount++;
			m_rep = s.m_rep;
		}
		return *this;
	}

	string::Representation* string::Representation::GetOwnCopy()
	{
		if (m_useCount == 1)
			return this;
		m_useCount--;
		return new Representation(m_data, m_length);
	}

	string::Representation::Representation(const wchar_t* data, int length)
	{
		m_length = length;
		m_data = new wchar_t[m_length+1];
		CopyMemory(m_data, data, m_length*sizeof(wchar_t));
		m_data[m_length] = 0;
		m_useCount = 1;
	}

	string::Representation::Representation(int length)
	{
		m_length = length;
		m_data = new wchar_t[m_length+1];
		memset(m_data, 0, sizeof(wchar_t)*m_length);
		m_data[m_length] = 0;
		m_useCount = 1;
	}

	string::Representation::Representation(const char* data, int length)
	{
		m_length = length;
		m_data = new wchar_t[m_length+1];
		MultiByteToWideChar(CP_ACP, 0, data, m_length, m_data, m_length);
		m_data[m_length] = 0;
		m_useCount = 1;
	}

	string::Representation::~Representation()
	{
		delete[] m_data;
	}

	void string::Representation::Assign(const wchar_t* data, int length)
	{
		if (m_length != length+1)
		{
			delete[] m_data;
			m_length = length;
			m_data = new wchar_t[m_length+1];
		}
		CopyMemory(m_data, data, sizeof(wchar_t)*m_length);
		m_data[m_length] = 0;
	}

	void string::Representation::Assign(const char* data, int length)
	{
		if (m_length != length+1)
		{
			delete[] m_data;
			m_length = length;
			m_data = new wchar_t[m_length+1];
		}
		MultiByteToWideChar(CP_ACP, 0, data, m_length, m_data, m_length);
		m_data[m_length] = 0;
	}

	void string::Representation::Append(const wchar_t* data, int length)
	{
		wchar_t * new_data = new wchar_t[m_length + length+1];
		CopyMemory(new_data, m_data, m_length*sizeof(wchar_t));
		CopyMemory(new_data+m_length, data, length*sizeof(wchar_t));
		delete[] m_data;
		m_data = new_data;
		m_length = m_length + length;
		m_data[m_length] = 0;
	}

	void string::Representation::Erase(int start, int len)
	{
		for (int i = 0; i < len; i++)
		{
			for (int j = start; j < m_length; j++)
			{
				m_data[j+i] = m_data[j+i+1];
			}
		}
		m_length--;
	}

	void string::Representation::Insert(wchar_t chr, int pos)
	{
		wchar_t * new_data = new wchar_t[m_length + 2];
		CopyMemory(new_data, m_data, m_length*sizeof(wchar_t));
		delete[] m_data;
		for (int i = m_length; i > pos; i--)
		{
			new_data[i] = new_data[i-1];
		}
		new_data[pos] = chr;
		m_data = new_data;
		m_length = m_length + 1;
		m_data[m_length] = 0;
	}

	bool string::Representation::Save(std::ostream& stream) const
	{
		stream.write(reinterpret_cast<const char*>(&m_length), sizeof(m_length));
		if (m_length)
			stream.write(reinterpret_cast<const char*>(m_data), m_length*sizeof(wchar_t));
		return true;
	}

	bool string::Representation::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(&m_length), sizeof(m_length));
		if (m_length)
		{
			std::vector<wchar_t> data(m_length);
			stream.read(reinterpret_cast<char*>(&data[0]), m_length*sizeof(wchar_t));
			Assign(&data[0], m_length);
		}
		else
		{
			Assign(L"", 0);
		}
		return true;
	}

	const wchar_t* string::Data() const
	{
		return m_rep->m_data;
	}

	int string::ToInt32() const
	{
		return _wtoi(m_rep->m_data);
	}

	int string::ToInt32FromHex() const
	{
		wchar_t allowed_symbols[] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'A', L'a', L'B', L'b', L'C', L'c', L'D', L'd', L'E', L'e', L'F', L'f', L'x', L'X' };
		int allowd_symbols_count = sizeof(allowed_symbols) / sizeof(wchar_t);
		for (int i = 0; i < m_rep->m_length; i++)
		{
			bool ok = false;
			for (int j = 0; j < allowd_symbols_count; j++)
			{
				if (m_rep->m_data[i] == allowed_symbols[j])
				{
					ok = true;
					break;
				}
			}
			if (!ok)
				return 0;
		}
		const wchar_t *end = m_rep->m_data;
		const wchar_t *start = m_rep->m_data + m_rep->m_length-1;
		if (end[0] == L'0' && (end[1] == L'x' || end[1] == L'X'))
			end += 2;
		int res = 0;


		int base = 1;

		while (1)
		{
			switch(*start)
			{
			case L'0': case L'1': case L'2': case L'3': case L'4': case L'5': case L'6': case L'7': case L'8': case L'9':
				res += base*(*start - L'0');
				break;
			case L'a': case L'A':
				res += base*10;
				break;
			case L'b': case L'B':
				res += base*11;
				break;
			case L'c': case L'C':
				res += base*12;
				break;
			case L'd': case L'D':
				res += base*13;
				break;
			case L'e': case L'E':
				res += base*14;
				break;
			case L'f': case L'F':
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
		return (float)_wtof(m_rep->m_data);
	}

	double string::ToDouble() const
	{
		return _wtof(m_rep->m_data);
	}

	const string string::Convert(int32_t value, int radix)
	{
		char buf[128];
		itoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(uint32_t value, int radix)
	{
		char buf[128];
		_ultoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(signed char value)
	{
		wchar_t buf[16];
		buf[0] = value;
		buf[1] = 0;
		return string(buf);
	}

	const string string::Convert(unsigned char value)
	{
		wchar_t buf[16];
		buf[0] = value;
		buf[1] = 0;
		return string(buf);
	}

	const string string::Convert(int16_t value, int radix)
	{
		char buf[128];
		itoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(uint16_t value, int radix)
	{
		char buf[128];
		_ultoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(int8_t value, int radix)
	{
		char buf[128];
		itoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(uint8_t value, int radix)
	{
		char buf[128];
		itoa(value, buf, radix);
		return string(buf);
	}

	const string string::Convert(int64_t value, int radix)
	{
		char buf[128];
		_i64toa_s(value, buf, 128, radix);
		return string(buf);
	}

	const string string::Convert(uint64_t value, int radix)
	{
		wchar_t buf[128];
		_ui64tow_s(value, buf, 128, radix);
		return string(buf);
	}

	const string string::Convert(float value, int precision)
	{
		char buf[128];
		gcvt(value, precision, buf);
		return string(buf);
	}

	const string string::Convert(double value, int precision)
	{
		char buf[128];
		gcvt(value, precision, buf);
		return string(buf);
	}

	const string string::Convert(wchar_t value)
	{
		wchar_t buf[2];
		buf[0] = value;
		buf[1] = 0;
		return string(buf);
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
		wchar_t buf[128];
		_ui64tow_s((__int64)value, buf, 128, 16);
		return string(buf);
#else
		wchar_t buf[128];
		_ultow_s((unsigned)value, buf, 128, 16);
		return string(buf);
#endif
	}

	const string string::Format(const wchar_t* fmt, ...)
	{
#define FORMAT_MAX_LENGTH 8192
		wchar_t buffer[FORMAT_MAX_LENGTH];
		memset(buffer, 0, sizeof(buffer[0])*FORMAT_MAX_LENGTH);
		va_list argumentPointer;
		va_start(argumentPointer, fmt);
		vswprintf_s<FORMAT_MAX_LENGTH>(buffer, fmt, argumentPointer);
		va_end(argumentPointer);
#undef	FORMAT_MAX_LENGTH
		return string(buffer);
	}

	const string string::Trim(const wchar_t* delimiters) const
	{
		unsigned delLength = (unsigned)wcslen(delimiters);
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

		return string(m_rep->m_data + start, end - start);
	}

	const std::vector<string> string::Split(const wchar_t *delimiters) const
	{
		unsigned start = 0;
		unsigned end = Length();
		std::vector<string> res;
		for (unsigned i = 0; i < (unsigned)Length(); i++)
		{
			bool finish = false;
			for (unsigned j = 0; j < wcslen(delimiters); j++)
			{
				if (m_rep->m_data[i] == delimiters[j])
				{
					end = i;
					finish = true;
				}
			}

			if (finish)
			{
				res.push_back(string(m_rep->m_data + start, end - start).Trim(delimiters));
				start = end+1;
			}
		}
		if (start < (unsigned)Length())
		{
			res.push_back(string(m_rep->m_data + start, Length() - start).Trim(delimiters));
		}/**/
		return res;
	}

	wchar_t* string::I_know_what_I_do_just_give_me_the_pointer()
	{
		m_rep = m_rep->GetOwnCopy();
		return m_rep->m_data;
	}

	void* string::operator new(size_t size)
	{
		m_total_memory_used += size;
		m_memory_used += size;
		m_allocs_count++;
		return malloc(size);
	}

	void string::operator delete(void* pointer, size_t size)
	{
		if (pointer)
			free(pointer);
		m_memory_used -= size;
		m_frees_count--;
	}

	unsigned string::GetTotalMemoryUsed() throw()
	{
		return m_total_memory_used;
	}

	unsigned string::GetMemoryUsage() throw()
	{
		return m_memory_used;
	}

	unsigned string::GetAllocationsCount() throw()
	{
		return m_allocs_count;
	}

	unsigned string::GetFreeingCount() throw()
	{
		return m_frees_count;
	}

	bool string::Save(std::ostream& stream) const
	{
		return m_rep->Save(stream);
	}

	bool string::Load(std::istream& stream)
	{
		m_rep = m_rep->GetOwnCopy();
		return m_rep->Load(stream);
	}

    const std::string string::ToStdString() const
    {
        std::vector<char> buffer(Length());

        ToANSI(&buffer[0], buffer.size());

        return std::string(&buffer[0], buffer.size());
    }

    const std::wstring string::ToStdWString() const
    {
        return std::wstring(m_rep->m_data);
    }

	string::iterator string::begin()
	{
		m_rep = m_rep->GetOwnCopy();
		return m_rep->m_data;
	}

	string::const_iterator string::begin() const
	{
		return m_rep->m_data;
	}

	string::iterator string::end()
	{
		m_rep = m_rep->GetOwnCopy();
		return m_rep->m_data + m_rep->m_length;
	}

	string::const_iterator string::end() const
	{
		return m_rep->m_data + m_rep->m_length;
	}

}/**/
