/*
File: Texture2D.cpp
Author: Abramau Mikalai
Description: Texture2D implementation
*/

#include "texture2d.h"
#include "texture2d_impl.h"

namespace OpenGL
{
	Texture2D::Texture2D()
		: impl_texture_2d(new Texture2DImpl())
	{}

	Texture2D::Texture2D(const ImageModule::Image& image) 
		: impl_texture_2d(new Texture2DImpl(image))
	{}

	Texture2D::Texture2D(const Texture2D& texture)
		: impl_texture_2d(new Texture2DImpl(*texture.impl_texture_2d))
	{}

	Texture2D& Texture2D::operator = (const Texture2D& t)
	{
		Texture2D temp(t);
		std::swap(impl_texture_2d, temp.impl_texture_2d);
		return *this;
	}

	void Texture2D::Bind() const 
	{
		glBindTexture(GL_TEXTURE_2D, impl_texture_2d->m_id);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		impl_texture_2d.reset(0);
	}

	void Texture2D::CopyFromCPU(int x, int y, int width, int height, GLenum format, const unsigned char* data)
	{
		impl_texture_2d->CopyFromCPU(x, y, width, height, format, data);
	}

	void Texture2D::Resize(int width, int height)
	{
		impl_texture_2d->Resize(width, height);
	}

	void Texture2D::Create(int width, int height, GLenum format, const unsigned char* data)
	{
		impl_texture_2d->Create(width, height, format, data);
	}

	void Texture2D::Fill(unsigned char byte)
	{
		impl_texture_2d->Fill(byte);
	}

	int Texture2D::GetWidth() const
	{
		return impl_texture_2d->m_width;
	}

	int Texture2D::GetHeight() const
	{
		return impl_texture_2d->m_height;
	}

	/*void Texture2D::Create(const ImageModule::ImageFile& file)
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);

		m_width = file.GetWidth();
		m_height = file.GetHeight();
		m_format = ToInternalFormat(file.GetFormat());
		glGenTextures(1, &m_id);
		//SMART_LOG(CheckError("glGenTexture2Ds() failed"), LOG_LOCATION, true);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//SMART_LOG(CheckError("glBindTexture2D() failed"), LOG_LOCATION, true);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//SMART_LOG(CheckError("glTexParameterf() failed"), LOG_LOCATION, true);

		const unsigned char* data = (const unsigned char*)file.Lock();

		if (data != 0)
		{
			if (m_format == GL_COMPRESSED_SRGB_S3TC_DXT1_EXT) //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
			{
				int w = m_width;
				int h = m_height;
				int offs = 0;
				int blockSize = 8;
				int size = ((w+3)/4)*((h+3)/4)*blockSize;
				glCompressedTexImage2D(GL_TEXTURE_2D, 0, m_format, w, h, 0, size, data+offs);
				offs += size;
			}
			else
			{
				if (m_format == GL_ALPHA)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				}
				else if (m_format == GL_RGB)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					glGenerateMipmap(GL_TEXTURE_2D);
				}
				else if (m_format == GL_RGBA)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					glGenerateMipmap(GL_TEXTURE_2D);
				}
			}
		}

		file.Unlock(data);
		//glGenerateMipmap(GL_Texture2D_2D);
	}
	//*/
	//Texture2D::~Texture2D()
	//{
	//	glDeleteTextures(1, &m_id);
	//	//SMART_LOG(CheckError("glDeleteTexture2Ds() failed"), LOG_LOCATION, true);
	//}

	//void Texture2D::Store(System::Buffer& buffer)
	//{
	//	throw System::SystemError(L"Not implemented");
	//}

	//void Texture2D::Restore(System::Buffer& buffer)
	//{
	//	throw System::SystemError(L"Not implemented");
	//}

	

}