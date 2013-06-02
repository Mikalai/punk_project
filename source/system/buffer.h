#ifndef _H_PUNK_BUFFER
#define _H_PUNK_BUFFER

#include <cstdint>
#include "../string/string.h"
#include "../config.h"

namespace System
{
	class PUNK_ENGINE_API Buffer
	{
        int m_size;
		unsigned char* m_buffer;		
		unsigned char* m_current;
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
        int64_t ReadSigned64();
        uint64_t ReadUnsigned64();
		string ReadString();
		string ReadLine();
		string ReadWord();
		float ReadReal32();
		double ReadReal64();
		void ReadBuffer(void* buffer, int size);

        void WriteSigned64(int64_t value);
        void WriteUnsigned64(uint64_t value);
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

#endif	//	_H_PUNK_BUFFER
