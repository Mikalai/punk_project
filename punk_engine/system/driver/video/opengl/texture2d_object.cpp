/*
File: Texture2D.cpp
Author: Abramov Nickolai
Description: Texture2D implementation
*/

#include "texture2d_object.h"
#include "driver.h"
#include "../../../../images/image_file.h"
#include "../../../../system/system.h"
#include "../../../../images/images.h"

namespace OpenGL
{
	Texture2D::Texture2D() : m_id(0), m_width(0), m_height(0)
	{
	}

	Texture2D::Texture2D(const Texture2D& texture)
	{
		if (this != &texture)
		{
			m_id = texture.m_id;
			m_height = texture.m_format;
			m_width = texture.m_width;
			m_format = texture.m_format;
		}
	}

	Texture2D& Texture2D::operator= (const Texture2D& texture)
	{
		if (this != &texture)
		{
			m_id = texture.m_id;
			m_height = texture.m_format;
			m_width = texture.m_width;
			m_format = texture.m_format;
		}
		return *this;
	}

	int Texture2D::GetHeight() const
	{
		return m_height;
	}

	int Texture2D::GetWidth() const
	{
		return m_width;
	}

	void Texture2D::Bind() const 
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::CopyFromCPU(int x, int y, int width, int height, ImageModule::ImageFormat format, const unsigned char* data)
	{
		if (x < 0)
			return;
		if (y < 0)
			return;
		if (x + width > m_width)
			return;
		if (y + height > m_height)
			return;

		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);			
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RED, GL_UNSIGNED_BYTE, (void*)data);
		//CheckError(L"Copy from cpu memory to texture");
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Resize(int width, int height)
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);

		m_width = width;
		m_height = height;
		glGenTextures(1, &m_id);
		//SMART_LOG(CheckError("glGenTexture2Ds() failed"), LOG_LOCATION, true);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//SMART_LOG(CheckError("glBindTexture2D() failed"), LOG_LOCATION, true);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//unsigned char* data = new unsigned char[width*height];
		//memset(data, 0, width*height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		Fill(0);
		//CheckError(L"Creating 2d texture with data == 0");
		//delete[] data;

		//glGenerateMipmap(GL_Texture2D_2D);
	}

	void Texture2D::Create(int width, int height, ImageModule::ImageFormat format, const unsigned char* data)
	{
		if (m_id != 0)
			glDeleteTextures(1, &m_id);

		m_width = width;
		m_height = height;
		m_format = ToInternalFormat(format);
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		if (data != 0)
		{
			if (format == ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1) //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
			{
				int w = m_width;
				int h = m_height;
				int offs = 0;
				int blockSize = 8;
				int size = ((w+3)/4)*((h+3)/4)*blockSize;
				glCompressedTexImage2D(GL_TEXTURE_2D, 0, ToInternalFormat(format), w, h, 0, size, data+offs);
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
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);					
				}
			}
		}
		glGenerateMipmap(GL_TEXTURE_2D);
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
	*/
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_id);
		//SMART_LOG(CheckError("glDeleteTexture2Ds() failed"), LOG_LOCATION, true);
	}

	unsigned Texture2D::GetID() const
	{
		return m_id;
	}

	void Texture2D::Store(System::Buffer& buffer)
	{
		throw System::SystemError(L"Not implemented");
	}

	void Texture2D::Restore(System::Buffer& buffer)
	{
		throw System::SystemError(L"Not implemented");
	}

	void Texture2D::Fill(unsigned char byte)
	{
		const int size = 64;
		//CheckError(L"1Fillie 2d texture with data == 0");
		unsigned char data[size*size];
		memset(data, byte, size*size);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (int i = 0; i < m_height/size+1; i ++)
		{
			for (int j = 0; j < m_width/size+1; j ++ )
			{
				int width;
				int height;

				if ((j + 1) * size < m_width)
					width = size;
				else
					width = size - ((j+1) * size - m_width );

				if ((i+1) * size < m_height)
					height = size;
				else
					height = size - ((i+1) * size - m_height);

				glTexSubImage2D(GL_TEXTURE_2D, 0, j*size, i*size, width, height, GL_RED, GL_UNSIGNED_BYTE, (void*)data);
			}
		}

		//CheckError(L"Fillie 2d texture with data == 0");
	}

	int Texture2D::ToInternalFormat(ImageModule::ImageFormat format)
	{
		switch (format)
		{
		case ImageModule::IMAGE_FORMAT_ALPHA4 : return GL_ALPHA4_EXT ;
		case ImageModule::IMAGE_FORMAT_ALPHA8 : return GL_ALPHA8_EXT ;
		case ImageModule::IMAGE_FORMAT_ALPHA12 : return GL_ALPHA12_EXT ;
		case ImageModule::IMAGE_FORMAT_ALPHA16 : return GL_ALPHA16_EXT ;
		case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT16 : return GL_DEPTH_COMPONENT16 ;
		case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT24 : return GL_DEPTH_COMPONENT24 ;
		case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32 : return GL_DEPTH_COMPONENT32 ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE4 : return GL_LUMINANCE4_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE8 : return GL_LUMINANCE8_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE12 : return GL_LUMINANCE12_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE16 : return GL_LUMINANCE16_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE4_ALPHA4 : return GL_LUMINANCE4_ALPHA4_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE6_ALPHA2 : return GL_LUMINANCE6_ALPHA2_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE8_ALPHA8 : return GL_LUMINANCE8_ALPHA8_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA4 : return GL_LUMINANCE12_ALPHA4_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA12 : return GL_LUMINANCE12_ALPHA12_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE16_ALPHA16 : return GL_LUMINANCE16_ALPHA16_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY4 : return GL_INTENSITY4_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY8 : return GL_INTENSITY8_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY12 : return GL_INTENSITY12_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY16 : return GL_INTENSITY16_EXT ;
		case ImageModule::IMAGE_FORMAT_R3_G3_B2 : return GL_R3_G3_B2 ;
		case ImageModule::IMAGE_FORMAT_RGB4 : return GL_RGB4 ;
		case ImageModule::IMAGE_FORMAT_RGB5 : return GL_RGB5 ;
		case ImageModule::IMAGE_FORMAT_RGB8 : return GL_RGB8 ;
		case ImageModule::IMAGE_FORMAT_RGB10 : return GL_RGB10 ;
		case ImageModule::IMAGE_FORMAT_RGB12 : return GL_RGB12 ;
		case ImageModule::IMAGE_FORMAT_RGB16 : return GL_RGB16 ;
		case ImageModule::IMAGE_FORMAT_RGBA2 : return GL_RGBA2 ;
		case ImageModule::IMAGE_FORMAT_RGBA4 : return GL_RGBA4 ;
		case ImageModule::IMAGE_FORMAT_RGB5_A1 : return GL_RGB5_A1 ;
		case ImageModule::IMAGE_FORMAT_RGBA8 : return GL_RGBA8 ;
		case ImageModule::IMAGE_FORMAT_RGB10_A2 : return GL_RGB10_A2 ;
		case ImageModule::IMAGE_FORMAT_RGBA12 : return GL_RGBA12 ;
		case ImageModule::IMAGE_FORMAT_RGBA16 : return GL_RGBA16 ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX1 : return GL_COLOR_INDEX1_EXT ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX2 : return GL_COLOR_INDEX2_EXT ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX4 : return GL_COLOR_INDEX4_EXT ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX8 : return GL_COLOR_INDEX8_EXT ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX12 : return GL_COLOR_INDEX12_EXT ;
		case ImageModule::IMAGE_FORMAT_COLOR_INDEX16 : return GL_COLOR_INDEX16_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1 : return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3 : return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5 : return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ;
		case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8 : return GL_SIGNED_LUMINANCE8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8 : return GL_SIGNED_LUMINANCE8_ALPHA8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_RGB8 : return GL_SIGNED_RGB8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_RGBA8 : return GL_SIGNED_RGBA8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8 : return GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_ALPHA8 : return GL_SIGNED_ALPHA8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_INTENSITY8 : return GL_SIGNED_INTENSITY8_NV ;
		case ImageModule::IMAGE_FORMAT_HILO16 : return GL_HILO16_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_HILO16 : return GL_SIGNED_HILO16_NV ;
		case ImageModule::IMAGE_FORMAT_DSDT8 : return GL_DSDT8_NV ;
		case ImageModule::IMAGE_FORMAT_DSDT8_MAG8 : return GL_DSDT8_MAG8_NV ;
		case ImageModule::IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8 : return GL_DSDT8_MAG8_INTENSITY8_NV ;
		case ImageModule::IMAGE_FORMAT_HILO8 : return GL_HILO8_NV ;
		case ImageModule::IMAGE_FORMAT_SIGNED_HILO8 : return GL_SIGNED_HILO8_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_R16 : return GL_FLOAT_R16_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_R32 : return GL_FLOAT_R32_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RG16 : return GL_FLOAT_RG16_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RGB16 : return GL_FLOAT_RGB16_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RGBA16 : return GL_FLOAT_RGBA16_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RG32 : return GL_FLOAT_RG32_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RGB32 : return GL_FLOAT_RGB32_NV ;
		case ImageModule::IMAGE_FORMAT_FLOAT_RGBA32 : return GL_FLOAT_RGBA32_NV ;
		case ImageModule::IMAGE_FORMAT_RGBA_FLOAT32 : return GL_RGBA_FLOAT32_ATI ;
		case ImageModule::IMAGE_FORMAT_RGB_FLOAT32 : return GL_RGB_FLOAT32_ATI ;
		case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT32 : return GL_ALPHA_FLOAT32_ATI ;
		case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT32 : return GL_INTENSITY_FLOAT32_ATI ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT32 : return GL_LUMINANCE_FLOAT32_ATI ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32 : return GL_LUMINANCE_ALPHA_FLOAT32_APPLE ;
		case ImageModule::IMAGE_FORMAT_RGBA_FLOAT16 : return GL_RGBA_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_RGB_FLOAT16 : return GL_RGB_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT16 : return GL_ALPHA_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT16 : return GL_INTENSITY_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT16 : return GL_LUMINANCE_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16 : return GL_LUMINANCE_ALPHA_FLOAT16_ATI ;
		case ImageModule::IMAGE_FORMAT_DEPTH24_STENCIL8 : return GL_DEPTH24_STENCIL8 ;
		case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32F : return GL_DEPTH_COMPONENT32F ;
		case ImageModule::IMAGE_FORMAT_DEPTH32F_STENCIL8 : return GL_DEPTH32F_STENCIL8 ;
		case ImageModule::IMAGE_FORMAT_SRGB8 : return GL_SRGB8 ;
		case ImageModule::IMAGE_FORMAT_SRGB8_ALPHA8 : return GL_SRGB8_ALPHA8 ;
		case ImageModule::IMAGE_FORMAT_SLUMINANCE8 : return GL_SLUMINANCE8 ;
		case ImageModule::IMAGE_FORMAT_SLUMINANCE8_ALPHA8 : return GL_SLUMINANCE8_ALPHA8 ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1 : return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT ;
		case ImageModule::IMAGE_FORMAT_RGB9_E5 : return GL_RGB9_E5 ;
		case ImageModule::IMAGE_FORMAT_R11F_G11F_B10F : return GL_R11F_G11F_B10F ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1 : return GL_COMPRESSED_LUMINANCE_LATC1_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1 : return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2 : return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT ;
		case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2 : return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA32UI : return GL_RGBA32UI ;
		case ImageModule::IMAGE_FORMAT_RGB32UI : return GL_RGB32UI ;
		case ImageModule::IMAGE_FORMAT_ALPHA32UI : return GL_ALPHA32UI_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY32UI : return GL_INTENSITY32UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE32UI : return GL_LUMINANCE32UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32UI : return GL_LUMINANCE_ALPHA32UI_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA16UI : return GL_RGBA16UI ;
		case ImageModule::IMAGE_FORMAT_RGB16UI : return GL_RGB16UI ;
		case ImageModule::IMAGE_FORMAT_ALPHA16UI : return GL_ALPHA16UI_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY16UI : return GL_INTENSITY16UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE16UI : return GL_LUMINANCE16UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16UI : return GL_LUMINANCE_ALPHA16UI_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA8UI : return GL_RGBA8UI ;
		case ImageModule::IMAGE_FORMAT_RGB8UI : return GL_RGB8UI ;
		case ImageModule::IMAGE_FORMAT_ALPHA8UI : return GL_ALPHA8UI_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY8UI : return GL_INTENSITY8UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE8UI : return GL_LUMINANCE8UI_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8UI : return GL_LUMINANCE_ALPHA8UI_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA32I : return GL_RGBA32I ;
		case ImageModule::IMAGE_FORMAT_RGB32I : return GL_RGB32I ;
		case ImageModule::IMAGE_FORMAT_ALPHA32I : return GL_ALPHA32I_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY32I : return GL_INTENSITY32I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE32I : return GL_LUMINANCE32I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32I : return GL_LUMINANCE_ALPHA32I_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA16I : return GL_RGBA16I ;
		case ImageModule::IMAGE_FORMAT_RGB16I : return GL_RGB16I ;
		case ImageModule::IMAGE_FORMAT_ALPHA16I : return GL_ALPHA16I_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY16I : return GL_INTENSITY16I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE16I : return GL_LUMINANCE16I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16I : return GL_LUMINANCE_ALPHA16I_EXT ;
		case ImageModule::IMAGE_FORMAT_RGBA8I : return GL_RGBA8I ;
		case ImageModule::IMAGE_FORMAT_RGB8I : return GL_RGB8I ;
		case ImageModule::IMAGE_FORMAT_ALPHA8I : return GL_ALPHA8I_EXT ;
		case ImageModule::IMAGE_FORMAT_INTENSITY8I : return GL_INTENSITY8I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE8I : return GL_LUMINANCE8I_EXT ;
		case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8I : return GL_LUMINANCE_ALPHA8I_EXT ;
		case ImageModule::IMAGE_FORMAT_RG32UI : return GL_RG32UI ;
		case ImageModule::IMAGE_FORMAT_R32UI : return GL_R32UI ;
		case ImageModule::IMAGE_FORMAT_RG16UI : return GL_RG16UI ;
		case ImageModule::IMAGE_FORMAT_R16UI : return GL_R16UI ;
		case ImageModule::IMAGE_FORMAT_RG8UI : return GL_RG8UI ;
		case ImageModule::IMAGE_FORMAT_R8UI : return GL_R8UI ;
		case ImageModule::IMAGE_FORMAT_RG32I : return GL_RG32I ;
		case ImageModule::IMAGE_FORMAT_R32I : return GL_R32I ;
		case ImageModule::IMAGE_FORMAT_RG16I : return GL_RG16I ;
		case ImageModule::IMAGE_FORMAT_R16I : return GL_R16I ;
		case ImageModule::IMAGE_FORMAT_RG8I : return GL_RG8I ;
		case ImageModule::IMAGE_FORMAT_R8I : return GL_R8I ;
		case ImageModule::IMAGE_FORMAT_RG8 : return GL_RG8 ;
		case ImageModule::IMAGE_FORMAT_R8 : return GL_R8 ;
		case ImageModule::IMAGE_FORMAT_RG16 : return GL_RG16 ;
		case ImageModule::IMAGE_FORMAT_R16 : return GL_R16 ;
		case ImageModule::IMAGE_FORMAT_RG16F : return GL_RG16F ;
		case ImageModule::IMAGE_FORMAT_R16F : return GL_R16F ;
		case ImageModule::IMAGE_FORMAT_RG32F : return GL_RG32F ;
		case ImageModule::IMAGE_FORMAT_R32F : return GL_R32F ;
		case ImageModule::IMAGE_FORMAT_BGRA : return GL_BGRA;
		case ImageModule::IMAGE_FORMAT_BGR : return GL_BGR;
		case ImageModule::IMAGE_FORMAT_ALPHA: return GL_ALPHA;
		case ImageModule::IMAGE_FORMAT_RGBA: return GL_RGBA;
		case ImageModule::IMAGE_FORMAT_RGB: return GL_RGB;
		case ImageModule::IMAGE_FORMAT_RED: return GL_RED;
		default:
			throw System::SystemError(L"Unbelievable, but image format is not supported" + LOG_LOCATION_STRING);
		}
	}
}