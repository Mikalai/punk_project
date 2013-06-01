
#ifdef USE_VORBIS
#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>
#endif  //  USE_VORBIS

#include <sstream>
#include "../system/errors/exceptions.h"
#include "../string/string.h"
#include "audio_buffer.h"
#include "audio_ogg_loader.h"

namespace Audio
{
    #ifdef USE_VORBIS

	struct OggLoaderImpl
	{
		Buffer* m_buffer;
		OggVorbis_File m_file;
		int m_rate;
		int m_channels;
		int m_size;
		System::string m_c;

		OggLoaderImpl(Buffer* buffer, const System::string& filename);
		~OggLoaderImpl();
		void Load();
		void Decompress(void** data, unsigned* size);
	};

	OggLoaderImpl::OggLoaderImpl(Buffer* buffer, const System::string& filename)
		: m_buffer(buffer)
	{
		char buf[2048];
		filename.ToANSI(buf, 2048);
		if (ov_fopen(buf, &m_file) < 0)
			throw System::PunkException(L"Input does not appear to be an Ogg bitstream.");
	}

	OggLoaderImpl::~OggLoaderImpl()
	{
		ov_clear(&m_file);
	}

	void OggLoaderImpl::Load()
	{
		vorbis_comment* comment = ov_comment(&m_file, -1);
		std::stringstream stream;
		char **ptr= ov_comment(&m_file,-1)->user_comments;
		vorbis_info *vi=ov_info(&m_file,-1);
		while(*ptr)
		{
			stream << *ptr << std::endl;
			++ptr;
		}
		m_channels = vi->channels;
		m_rate = vi->rate;

		char buffer[4096];
		int current_section = 0;

		std::vector<char> data;
#ifdef _WIN32
		long read = 0;
		do
		{
			read = ov_read(&m_file, buffer, 4096, 0, 2, 1, &current_section);
			if (read == OV_HOLE)
				throw System::PunkException(L"Can't read ogg file");
			else if (read == OV_EBADLINK)
				throw System::PunkException(L"Can't read ogg file");
			else if (read == OV_EINVAL)
				throw System::PunkException(L"Can't read ogg file");
			else if (read != 0)
				data.insert(data.end(), buffer, buffer + read);
		}
		while (read != 0);
#else	//	_WIN32
		error;
#endif
		m_buffer->SetData(Format::STEREO16, reinterpret_cast<void*>(&data[0]), static_cast<int>(data.size()), m_rate);
		m_buffer->SetDescription(System::string(stream.str().c_str()));
	}

	void OggLoaderImpl::Decompress(void** data, unsigned* size)
	{}

    #endif  //  USE_VORBIS

	OggLoader::OggLoader(Buffer* buffer, const System::string& filename)
	#ifdef USE_VORBIS
		: impl(new OggLoaderImpl(buffer, filename))
    #else    
        : impl(nullptr)
    #endif
    {
#ifndef USE_VORBIS
        (void)buffer; (void)filename;
#endif
    }

	OggLoader::~OggLoader()
	{
	    #ifdef USE_VORBIS
		delete impl;
		impl = nullptr;
		#endif
	}

	System::StreamingStepResult OggLoader::Load()
	{
	    #ifdef USE_VORBIS
		try
		{
			impl->Load();
			return System::StreamingStepResult::STREAM_OK;
		}
		catch(...)
		{
			return System::StreamingStepResult::STREAM_ERROR;
		}
		#else
		return System::StreamingStepResult::STREAM_ERROR;
		#endif
	}

	System::StreamingStepResult OggLoader::Decompress(void** data, unsigned* size)
	{
	    #ifdef USE_VORBIS
		try
		{
			impl->Decompress(data, size);
			return System::StreamingStepResult::STREAM_OK;
		}
		catch(...)
		{
			return System::StreamingStepResult::STREAM_ERROR;
		}
		#else
        (void)data; (void)size;
		return System::StreamingStepResult::STREAM_ERROR;
		#endif
	}
}

