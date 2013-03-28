#ifndef _H_PUNK_AUDIO_OPENAL_BUFFER
#define _H_PUNK_AUDIO_OPENAL_BUFFER

#include "openal.h"
#include "../audio_buffer.h"

namespace Audio
{
	struct BufferImpl
	{
		ALuint m_buffer;
		System::string m_description;

		BufferImpl();
		~BufferImpl();
		void Destroy();
		void Create();
		void SetData(Format format, void* data, int size, int frequency);
		int GetFrequency() const;
		int GetBits() const;
		int GetChannels() const;
		int GetSize() const;
		void* GetData() const;
		void SetDescription(const System::string& value);
		const System::string& GetDescription() const; 
	};

	BufferImpl::BufferImpl()
		: m_buffer(0)
	{
		Create();
	}

	BufferImpl::~BufferImpl()
	{
		Destroy();
	}

	void BufferImpl::Destroy()
	{
		if (alIsBuffer(m_buffer))
			alDeleteBuffers(1, &m_buffer);
	}

	void BufferImpl::Create()
	{
		alGenBuffers(1, &m_buffer);
		ValidateOpenAL(L"Can't create audio buffer");
	}

	void BufferImpl::SetData(Format format, void* data, int size, int frequency)
	{
		alBufferData(m_buffer, AudioFormatToOpenALFormat(format), reinterpret_cast<ALvoid*>(data), static_cast<ALsizei>(size), static_cast<ALsizei>(frequency));
		ValidateOpenAL(L"Unable to set data to the OpenAL buffer");
	}

	int BufferImpl::GetFrequency() const
	{
		ALint value;
		alGetBufferi(m_buffer, AL_FREQUENCY, &value);
		ValidateOpenAL(L"Can't get buffer frequency");
		return static_cast<int>(value);
	}

	int BufferImpl::GetBits() const
	{
		ALint value;
		alGetBufferi(m_buffer, AL_BITS, &value);
		ValidateOpenAL(L"Can't get buffer bits");
		return static_cast<int>(value);
	}

	int BufferImpl::GetChannels() const
	{
		ALint value;
		alGetBufferi(m_buffer, AL_CHANNELS, &value);
		ValidateOpenAL(L"Can't get buffer channels");
		return static_cast<int>(value);
	}

	int BufferImpl::GetSize() const
	{
		ALint value;
		alGetBufferi(m_buffer, AL_SIZE, &value);
		ValidateOpenAL(L"Can't get buffer size");
		return static_cast<int>(value);
	}

	void* BufferImpl::GetData() const
	{
		ALint value;
		alGetBufferi(m_buffer, AL_FREQUENCY, &value);
		ValidateOpenAL(L"Can't get buffer data");
		return reinterpret_cast<void*>(value);
	}

	void BufferImpl::SetDescription(const System::string& value)
	{
		m_description = value;
	}

	const System::string& BufferImpl::GetDescription() const
	{
		return m_description;
	}
}

#endif	//	_H_PUNK_AUDIO_OPENAL_BUFFER