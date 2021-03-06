
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "../logger.h"
#include "buffer_win32.h"

namespace System
{
	Buffer::Buffer() : m_size(0), m_buffer(0), m_current(0)
	{
	}

	Buffer::Buffer(int size)
	{
		m_size = size;
		m_current = m_buffer = new unsigned char[m_size];
	}

	Buffer::~Buffer()
	{
		delete[] m_buffer;
	}

	void Buffer::Reset()
	{
		m_current = m_buffer;
	}

	int Buffer::LeftCapacity() const
	{
		return m_size - (m_current - m_buffer);
	}

	void Buffer::SetPosition(int pos)
	{
		if (pos < m_size)
			m_current = m_buffer + pos;
		else
			m_current = m_buffer + m_size;
	}

	bool Buffer::IsEnd() const
	{
		return m_current - m_buffer >= m_size;
	}

	int Buffer::GetPosition() const
	{
		return m_current - m_buffer;
	}

	int Buffer::GetSize() const
	{
		return m_size;
	}

	void Buffer::SetSize(int size)
	{
		m_size = size;
		if (m_buffer)
			delete[] m_buffer;
		m_current = m_buffer = new unsigned char[m_size];
	}

	void* Buffer::StartPointer()
	{
		return (void*)m_buffer;
	}

	const void* Buffer::StartPointer() const
	{
		return (const void*)m_buffer;
	}

	unsigned __int64 Buffer::ReadUnsigned64()
	{
		unsigned __int64 res = *(unsigned __int64*)(m_current);
		m_current += sizeof(unsigned __int64);
		return res;
	}

	__int64 Buffer::ReadSigned64()
	{
		__int64 res = *(__int64*)(m_current);
		m_current += sizeof(__int64);
		return res;
	}

	int Buffer::ReadSigned32()
	{
		int res = *(int*)(m_current);
		m_current += sizeof(int);
		return res;
	}

	unsigned Buffer::ReadUnsigned32()
	{
		unsigned res = *(unsigned*)(m_current);
		m_current += sizeof(unsigned);
		return res;
	}

	short Buffer::ReadSigned16()
	{
		short res = *(short*)(m_current);
		m_current += sizeof(short);
		return res;
	}

	unsigned short Buffer::ReadUnsigned16()
	{
		unsigned short res = *(unsigned short*)(m_current);
		m_current += sizeof(unsigned short);
		return res;
	}

	signed char Buffer::ReadSigned8()
	{
		signed char res = *(signed char*)(m_current);
		m_current += sizeof(signed char);
		return res;
	}

	unsigned char Buffer::ReadUnsigned8()
	{
		int res = *(unsigned*)(m_current);
		m_current += sizeof(unsigned char);
		return res;
	}

	string Buffer::ReadString()
	{
		string res((char*)m_current+sizeof(int), *(int*)m_current);
		m_current = m_current + sizeof(int) + *(int*)m_current;
		return res;
	}

	string Buffer::ReadLine()
	{
		int len = 0;
		for (unsigned char* p = m_current; *p != '\n' && p < m_buffer + m_size; p++, len++);		
		string res((char*)m_current, len);
		m_current += len;
		return res;
	}

	string Buffer::ReadWord()
	{
		//
		//	skip spaces
		//
		unsigned char* p = 0;
		for (p = m_current; (*p == '\n' || *p == '\r' || *p == '\t' || *p == ' ') && p < m_buffer + m_size; p++);		
		m_current = p;
		int len = 0;
		for (unsigned char* p = m_current; *p != '\n' && *p != '\r' && *p !='\t' && *p != ' ' && p < m_buffer + m_size; p++, len++);		
		string res((char*)m_current, len);
		for (unsigned char* p = m_current+len; (*p == '\n' || *p =='\t' || *p == '\r' || *p == ' ') && p < m_buffer + m_size; p++, len++);		
		m_current += len;
		return res;
	}

	float Buffer::ReadReal32()
	{
		float res = *(float*)(m_current);
		m_current += sizeof(float);
		return res;
	}

	double Buffer::ReadReal64()
	{
		double res = *(double*)(m_current);
		m_current += sizeof(double);
		return res;
	}

	void Buffer::ReadBuffer(void* buffer, int size)
	{
		memcpy(buffer, m_current, size);
		m_current += size;
	}

	void Buffer::WriteUnsigned64(unsigned __int64 value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteSigned64(__int64 value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteSigned32(int value)
	{		
		WriteData(&value, sizeof(value));	
	}

	void Buffer::WriteUnsigned32(unsigned value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteSigned16(short value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteUnsigned16(unsigned short value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteSigned8(signed char value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteUnsigned8(unsigned char value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteString(const string& value)
	{
		unsigned len = value.Length();
		WriteData(&len, sizeof(len));
		WriteData((void*)value.Data(), sizeof(wchar_t)*len);
	}

	void Buffer::WriteReal32(float value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteReal64(double value)
	{
		WriteData(&value, sizeof(value));
	}

	void Buffer::WriteBuffer(const void* buffer, int size)
	{
		WriteData(buffer, size);
	}

	void* Buffer::Release()
	{
		void* result = m_buffer;
		m_size = 0;
		m_current = nullptr;
		m_buffer = nullptr;
		return result;
	}

	void Buffer::Resize(unsigned new_size)
	{
		unsigned char* tmp = new unsigned char[new_size];
		memcpy_s(tmp, new_size, m_buffer, m_size);
		m_current = tmp + (m_current - m_buffer);
		delete[] m_buffer;
		m_buffer = tmp;
		m_size = new_size;		
	}

	void Buffer::WriteData(const void* data, unsigned size)
	{
		if (m_buffer == 0)
		{
			m_buffer = new unsigned char[size];
			m_current = m_buffer;
		}

		if (m_current + size >= m_buffer + m_size)
			Resize(m_size+2*size);
		memcpy(m_current, data, size);
		m_current += size;
	}
}