#ifndef _H_STATIC_STRING
#define _H_STATIC_STRING

//#undef _STRICT_ANSI
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string.h>
#include <stdarg.h>
//#include "../exception.h"
#include "static_array.h"

namespace System
{
template<unsigned Size>
class stack_basic_string : public array<wchar_t, Size>
{
protected:
    int m_actual_length;
public:
    stack_basic_string() : array<wchar_t, Size>() {}

    stack_basic_string(const wchar_t* s) throw () : array<wchar_t, Size>() // throw(NotEnoughSize)
    {
        m_actual_length = wcslen(s);
        if (m_actual_length < Size)
        {
            memcpy(array<wchar_t, Size>::m_item, s, sizeof(wchar_t)*m_actual_length);
        }
    }

    explicit stack_basic_string(const char* s)
    {
        MultiByteToWideChar(CP_ACP, 0, s, strlen(s), array<wchar_t, Size>::m_data, Size);
    }

    stack_basic_string(const char* s, int length)
    {
        MultiByteToWideChar(CP_ACP, 0, s, Length, array<wchar_t, Size>::m_data, Size);
    }

    stack_basic_string(const wchar_t* s, int length)
    {
        if (Size > length)
        {
            memcpy(array<wchar_t, Size>::m_data, s, length*sizeof(wchar_t));
        }
        else
        {
            memcpy(array<wchar_t, Size>::m_data, s, Size*sizeof(wchar_t));
        }
    }

    template<int Size2>
    stack_basic_string(const stack_basic_string<Size2>& s)
    {
        if (s.m_actual_length < Size)
        {
            m_actual_length = s.m_actual_length;
            memcpy(array<wchar_t, Size>::m_item, s.m_item, sizeof(wchar_t)*m_actual_length);
        }
    }

    stack_basic_string& operator = (const wchar_t* s) throw ()
    {
        m_actual_length = wcslen(s);
        if (m_actual_length < Size)
        {
            memcpy(array<wchar_t, Size>::m_item, s, sizeof(wchar_t)*m_actual_length);
        }
        return *this;
    }

    template<int Size2>
    stack_basic_string& operator = (const stack_basic_string<Size2>& s) throw ()
    {
        m_actual_length = wcslen(s);
        if (&s != this && s.m_actual_length < Size)
        {
            memcpy(array<wchar_t, Size>::m_item, s.m_item, sizeof(wchar_t)*m_actual_length);
        }
        return *this;
    }

    stack_basic_string& format(const wchar_t* fmt, ...) throw()
    {
        va_list argumentPointer;
        va_start(argumentPointer, fmt);
        vsnwprintf(array<wchar_t, Size>::m_item, Size, fmt, argumentPointer);
        va_end(argumentPointer);
        m_actual_length = wcslen(array<wchar_t, Size>::m_item);
        return *this;
    }

    int Length(void) const throw()
    {
        return m_actual_length;
    }

    const wchar_t* Data() const throw()
    {
        return array<wchar_t, Size>::m_item;
    }

    stack_basic_string& Erase(int start, int len)
    {
        if (start + len >= m_actual_length)
            return *this;
        for (int i = 0; i < len; i++)
        {
            array<wchar_t, Size>::m_item[start + i] = array<wchar_t, Size>::m_item[start + i + len];
        }

        m_actual_length -= len;
    }

    stack_basic_string& Insert(wchar_t chr, int pos)
    {
        if (m_actual_length + 1 >= Size)
            return;
        for (int i = m_actual_length; i >= pos; --i)
        {
            array<wchar_t, Size>::m_item[i] = array<wchar_t, Size>::m_item[i - 1];
        }
        array<wchar_t, Size>::m_iten[pos] = chr;
        m_actual_length++;
        array<wchar_t, Size>::m_iten[m_actual_length] = 0;

    }

    template<int Size2>
    stack_basic_string& operator += (const stack_basic_string<Size2>& s)
    {
        if (m_actual_length + s.m_actual_length >= Size)
            return *this;
        memcpy(array<wchar_t, Size>::m_item + m_actual_length, s.Data(), s.m_actual_length);
        m_actual_length += s.m_actual_length;
        array<wchar_t, Size>::m_item[m_actual_length] = 0;
    }

    stack_basic_string& operator += (const wchar_t* s)
    {
        if (m_actual_length + wcslen(s) >= Size)
            return *this;
        memcpy(array<wchar_t, Size>::m_item + m_actual_length, s, wcslen(s));
        m_actual_length += wcslen(s);
        array<wchar_t, Size>::m_item[m_actual_length] = 0;
    }

    void ToANSI(char* buffer, int size, int* length)
    {
        if (size < m_actual_length+1)
        {
            *buffer = 0;
            *length = 0;
            return;
        }
        *length = m_actual_length + 1;
        WideCharToMultiByte(CP_ACP, 0, array<wchar_t, Size>::m_item, m_actual_length, buffer, size, 0, 0);
    }

    int ToInt32() const
    {
        return _wtoi(array<wchar_t, Size>::m_item);
    }

    float ToFloat() const
    {
        return (float)_wtof(array<wchar_t, Size>::m_item);
    }

    double ToDouble() const
    {
        return _wtof(array<wchar_t, Size>::m_item);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(__int32 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _itow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(unsigned __int32 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _ultow((unsigned long)value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    static stack_basic_string Convert(signed char value)
    {
        wchar_t buf[16];
        buf[0] = value;
        buf[1] = 0;
        return stack_basic_string<Size>(buf);
    }

    static stack_basic_string Convert(unsigned char value)
    {
        wchar_t buf[16];
        buf[0] = value;
        buf[1] = 0;
        return stack_basic_string<Size>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(__int16 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _itow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string Convert(unsigned __int16 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _itow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(__int8 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _itow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(unsigned __int8 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _itow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(__int64 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _i64tow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(unsigned __int64 value, int radix = 10)
    {
        wchar_t buf[Size1];
        _ui64tow(value, buf, radix);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(float value, int precision)
    {
        char buf[Size1];
        _gcvt(buf, value, precision);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(double value, int precision)
    {
        char buf[Size1];
        _gcvt(buf, value, precision);
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(wchar_t value)
    {
        wchar_t buf[2];
        buf[0] = value;
        buf[1] = 0;
        return stack_basic_string<Size1>(buf);
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(bool value)
    {
        if (value)
            return L"True";
        return L"False";
    }

    template<int Size1>
    static stack_basic_string<Size1> Convert(void* value)
    {
        wchar_t buf[Size1];
#ifdef _WIN64
        _ui64tow(__int64)value, buf, 16);
        return stack_basic_string<Size1>(buf);
#else
        _ultow((unsigned)value, array<wchar_t, Size1>::m_item, 16);
        return stack_basic_string<Size1>(buf);
#endif
    }

    template<int Size1>
    static stack_basic_string<Size1> Format(const wchar_t* fmt, ...)
    {
        wchar_t buffer[Size1];
        memset(buffer, 0, sizeof(buffer[0])*Size1);
        va_list argumentPointer;
        va_start(argumentPointer, fmt);
        vswprintf(buffer, fmt, argumentPointer);
        va_end(argumentPointer);
        return stack_basic_string<Size1>(buffer);
    }

    template<int Size1, int Size2>
    friend bool operator == (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2);
    template<int Size1>
    friend bool operator == (const stack_basic_string<Size1>& s1, const wchar_t* s2);

    template<int Size1, int Size2>
    friend bool operator != (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2);
    template<int Size1>
    friend bool operator != (const stack_basic_string<Size1>& s1, const wchar_t* s2);

    template<int Size1, int Size2>
    friend bool operator < (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2);
    template<int Size1>
    friend bool operator < (const stack_basic_string<Size1>& s1, const wchar_t* s2);
};

template<int Size1, int Size2>
bool operator == (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2)
{
    if (s1.m_actual_size != s2.m_actual_size)
        return false;
    return wcscmp(s1.Data(), s2.Data()) == 0;
}

template<int Size1>
bool operator == (const stack_basic_string<Size1>& s1, const wchar_t* s2)
{
    if (s1.m_actual_size != wcslen(s2))
        return false;
    return wcscmp(s1.Data(), s2) == 0;
}

template<int Size1, int Size2>
bool operator != (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2)
{
    return !(s1 == s2);
}

template<int Size1>
bool operator != (const stack_basic_string<Size1>& s1, const wchar_t* s2)
{
    return !(s1 == s2);
}

template<int Size1, int Size2>
bool operator < (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2)
{
    return wcscmp(s1.Data(), s2.Data) == -1;
}

template<int Size1>
bool operator < (const stack_basic_string<Size1>& s1, const wchar_t* s2)
{
    return wcscmp(s1.Data(), s2) == -1;
}

template<int Size1, int Size2>
stack_basic_string<Size1 + Size2> operator + (const stack_basic_string<Size1>& s1, const stack_basic_string<Size2>& s2)
{
    stack_basic_string<Size1 + Size2> res(s1);
    res += s2;
    return res;
}

/*template<int Size1, int Size2>
stack_basic_string<Size2> operator + (const stack_basic_string<Size1>& s1, const wchar_t* s2)
{
    stack_basic_string<2*Size1> res(s1);
    res += s2;
    return res;
}*/

/*	template<int Size1>
stack_basic_string<Size1> operator + (const wchar_t* s1, const stack_basic_string<Size1>& s2)
{
    stack_basic_string<Size1> res(s1);
    res += s2;
    return res;
}*/

//typedef stack_basic_string<1024> string;
}

#endif
