#ifndef _H_PUNK_BUFFER_WIN32
#define _H_PUNK_BUFFER_WIN32

#include "../../string/string.h"
#include "../../config.h"

namespace System
{
	class PUNK_ENGINE Buffer
	{
		unsigned char* m_buffer;		
		unsigned char* m_current;
		int m_size;
	public:

		Buffer();
		Buffer(int size);
		~Buffer();
		void SetPosition(int pos);
		int GetPosition() const;
		int GetSize() const;
		void SetSize(int size);
		void* StartPointer();
		const void* StartPointer() const;
		bool IsEnd() const;
		int LeftCapacity() const;
		void Reset();

		int ReadSigned32();
		unsigned ReadUnsigned32();
		short ReadSigned16();
		unsigned short ReadUnsigned16();
		signed char ReadSigned8();
		unsigned char ReadUnsigned8();
		__int64 ReadSigned64();
		unsigned __int64 ReadUnsigned64();
		string ReadString();
		string ReadLine();
		string ReadWord();
		float ReadReal32();
		double ReadReal64();
		void ReadBuffer(void* buffer, int size);

		void WriteSigned64(__int64 value);
		void WriteUnsigned64(unsigned __int64 value);
		void WriteSigned32(int value);
		void WriteUnsigned32(unsigned value);
		void WriteSigned16(short value);
		void WriteUnsigned16(unsigned short value);
		void WriteSigned8(signed char value);
		void WriteUnsigned8(unsigned char value);
		void WriteString(const string& value);
		void WriteReal32(float value);
		void WriteReal64(double value);
		void WriteBuffer(const void* buffer, int size);

		void* Release();

		template<typename T>
		T* begin() { return reinterpret_cast<T*>(m_buffer); }
		
		template<typename T>
		const T* begin() const { return reinterpret_cast<const T*>(m_buffer); }

		template<typename T>
		T* end() { return reinterpret_cast<T*>(m_buffer) + m_size / sizeof(T); }

		template<typename T>
		const T* end() const { return reinterpret_cast<const T*>(m_buffer) + m_size / sizeof(T); }

	private:
		void Resize(unsigned new_size);
		void WriteData(const void* data, unsigned size);	
	};
}

#endif