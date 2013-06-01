#ifdef USE_OPENAL

#include "al_buffer_impl.h"

namespace Audio
{
	BufferImpl::BufferImpl()
		: m_buffer(0)
		, m_has_data(false)
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
		m_has_data = true;
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

	bool BufferImpl::IsValid() const
	{
		bool flag = true;
		flag &= (alIsBuffer(m_buffer) == TRUE);
		flag &= m_has_data;
		return flag;
	}
}

#endif // USE_OPENAL
