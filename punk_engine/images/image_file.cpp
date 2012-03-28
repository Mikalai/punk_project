#include <memory.h>
#include "image_file.h"

namespace ImageModule
{
	ImageFile::Rep::Rep() : m_data(0), 
		m_width(0), 
		m_height(0),
		m_depth(0),
		//m_channels(0),
		m_size(0), 
		m_bpp(0),
		m_format(IMAGE_FORMAT_BAD), 
		m_used_count(1) 
	{}

	ImageFile::Rep::Rep(const Rep& rep)
	{
		m_width = rep.m_width;
		m_height = rep.m_height;
		m_depth = rep.m_depth;
//		m_channels = rep.m_channels;
		m_size = rep.m_size;
		m_bpp = rep.m_bpp;
		m_format = rep.m_format;
		m_used_count = rep.m_used_count;
		m_data = new unsigned char[m_size];
		memcpy(m_data, rep.m_data, m_size);
	}

	void ImageFile::Rep::SetSize(unsigned size)
	{
		m_size = size;
		if (m_data)
			delete[] m_data;
		m_data = new unsigned char[m_size];
	}

	void ImageFile::Rep::SetSize(int width, int height)
	{
		if (m_width == width && m_height == height)
			return;

		m_width = width;
		m_height = height;
		m_size = m_width*m_height*4;		//alligned
		m_bpp = 8;

		if (m_data)
			delete[] m_data;

		m_data = new unsigned char[m_size];
	}

	ImageFile::Rep* ImageFile::Rep::GetOwnCopy()
	{
		if (m_used_count == 1)
			return this;
		else
		{
			Rep* rep = new Rep(*this);
			m_used_count--;
			rep->m_used_count = 1;
			return rep;
		}
	}

	ImageFile::Rep::~Rep()
	{
		delete[] m_data;
	}

	ImageFile::ImageFile() : m_rep(new ImageFile::Rep())
	{
	}

	ImageFile::ImageFile(const ImageModule::ImageFile &file)
	{
		m_rep = file.m_rep;
		m_rep->m_used_count++;
	}

	ImageFile& ImageFile::operator = (const ImageFile& file)
	{
		if (this != &file)
		{
			m_rep = file.m_rep;
			m_rep->m_used_count++;
		}
		return *this;
	}

	ImageFile::~ImageFile()
	{
		if (--m_rep->m_used_count == 0)
		{
			delete m_rep;
			m_rep = 0;
		}
	}

	unsigned ImageFile::GetWidth() const
	{
		return m_rep->m_width;
	}

	unsigned ImageFile::GetHeight() const
	{
		return m_rep->m_height;
	}

	unsigned ImageFile::GetChannels() const
	{
		return 4;//m_rep->m_channels;
	}

	void ImageFile::SetPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_rep = m_rep->GetOwnCopy();

		unsigned char* p = &m_rep->m_data[(y*m_rep->m_width + x)*4];		//must be alligned
		if (m_rep->m_format == IMAGE_FORMAT_ALPHA)
		{
			p[0] = a;
		}
		else if (m_rep->m_format == IMAGE_FORMAT_RGBA)
		{
			p[0] = r;
			p[1] = g;
			p[2] = b;
			p[3] = a;

/*			p[0] = a;
			p[1] = r;
			p[2] = g;
			p[3] = b;/**/		
		}
		else
		{
			p[0] = r;
			p[1] = g;
			p[2] = b;
		}			
	}

	void ImageFile::Store(System::Buffer& buffer)
	{
		buffer.WriteUnsigned32(m_rep->m_size);
		buffer.WriteBuffer((void*)m_rep->m_data, m_rep->m_size);
		buffer.WriteUnsigned32(m_rep->m_width);
		buffer.WriteUnsigned32(m_rep->m_height);
		buffer.WriteUnsigned32(m_rep->m_depth);
		buffer.WriteUnsigned32(m_rep->m_bpp);
		buffer.WriteBuffer(&m_rep->m_format, sizeof(m_rep->m_format));
	}

	void ImageFile::Restore(System::Buffer& buffer)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->m_size = buffer.ReadUnsigned32();
		m_rep->SetSize(m_rep->m_size);
		buffer.ReadBuffer((void*)m_rep->m_data, m_rep->m_size);
		m_rep->m_width = buffer.ReadUnsigned32();
		m_rep->m_height = buffer.ReadUnsigned32();
		m_rep->m_depth = buffer.ReadUnsigned32();
		m_rep->m_bpp = buffer.ReadUnsigned32();
		buffer.ReadBuffer(&m_rep->m_format, sizeof(m_rep->m_format));
	}


	void ImageFile::SetSize(unsigned width, unsigned height)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->SetSize(width, height);	//always alligned
	}

	void ImageFile::SetFormat(ImageFormat format)
	{
		m_rep = m_rep->GetOwnCopy();
		m_rep->m_format = format;		
	}

	ImageFormat ImageFile::GetFormat() const
	{
		return m_rep->m_format;
	}

	const unsigned char* ImageFile::GetPixel(unsigned x, unsigned y) const
	{
		return &m_rep->m_data[y*m_rep->m_width*4 + x*4];	//alligned
	}

	//
	//	not implemented yet
	void* ImageFile::Lock()
	{
		m_rep = m_rep->GetOwnCopy();
		return (void*)m_rep->m_data;
	}

	const void* ImageFile::Lock() const
	{
		return (void*)m_rep->m_data;
	}

	//
	//	not implemented yet
	void ImageFile::Unlock(void* p)
	{
		if (p == m_rep->m_data)
			return;
		return;
	}

		//
	//	not implemented yet
	void ImageFile::Unlock(const void* p) const
	{
		if (p == m_rep->m_data)
			return;
		return;
	}
}