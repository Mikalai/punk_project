#ifndef _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
#define _H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL

#include "../../../images/module.h"
#include "../driver/module.h"
#include "../buffers/module.h"
#include "../error/module.h"
#include "internal_formats.h"

namespace GPU
{
	using namespace OpenGL;

	struct Texture2D::Texture2DImpl
	{
        VideoDriverImpl* m_driver;
        int m_bind_slot;
        GLuint m_texture_id;
		int m_index;
		System::string m_location;		
		int m_width;
		int m_height;
        GLenum m_format;
		int m_pixel_size;
        bool m_use_mip_maps;
		GLenum m_internal_format;
		GLenum m_internal_type;
        OpenGL::PixelBufferObject* m_pbo;

        Texture2DImpl(VideoDriver* driver)
            : m_driver(driver->impl)
            , m_texture_id(0)
			, m_use_mip_maps(false)
			, m_width(0)
			, m_height(0)
			, m_format(0)
			, m_index(-1)
			, m_location(L"/")
			, m_pbo(nullptr)
		{
			//Create(64, 64, GL_RED, 0);
		}

        Texture2DImpl(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, VideoDriver* driver)
            : m_driver(driver->impl)
        {
            Create(width, height, ImageFormatToOpenGL(format), data, use_mipmaps);
        }

        Texture2DImpl(const ImageModule::Image& image, bool use_mipmaps, VideoDriver* driver)
            : m_driver(driver->impl)
            , m_texture_id(0)
            , m_use_mip_maps(use_mipmaps)
		{
			CreateFromImage(image, m_use_mip_maps);
		}

		Texture2DImpl(const Texture2DImpl& impl)
            : m_driver(impl.m_driver)
            , m_width(impl.m_width)
			, m_height(impl.m_height)
			, m_format(impl.m_format)
			, m_texture_id(impl.m_texture_id)
		{}

		~Texture2DImpl()
		{
			Clear();
		}

        void Bind(int slot)
        {
            m_bind_slot = slot;
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_texture_id);
            ValidateOpenGL(L"Unable to bind texture");
        }

        void Unbind()
        {
            glActiveTexture(GL_TEXTURE0 + m_bind_slot);
            glBindTexture(GL_TEXTURE_2D, 0);
            ValidateOpenGL(L"Unable to unbind texture");
        }

		void SetSourceFile(const System::string& filename)
		{
			m_location = filename;
		}

		const System::string& GetSourceFile() const
		{
			return m_location;
		}

		void SetIndex(int index)
		{
			m_index = index;
		}

		int GetIndex() const
		{
			return m_index;
		}

		void Init()
		{
			ImageModule::Importer import;
			std::unique_ptr<ImageModule::Image> image(import.LoadAnyImage(m_location));
			CreateFromImage(*image, true);
		}

		void Clear()
		{
            m_driver->GetVideoMemory()->FreePixelBuffer(m_pbo);

			if (m_texture_id)
			{
				glDeleteTextures(1, &m_texture_id);
				ValidateOpenGL(L"Can't delete texture");
				m_texture_id = 0;
			}
		}

		void CreateFromImage(const ImageModule::Image& image, bool use_mipmaps)
		{
			Create(image.GetWidth(), image.GetHeight(), ToInternalFormat(image.GetImageFormat()), image.GetData(), use_mipmaps);
			//m_use_mip_maps = use_mipmaps;

			//if (!image.GetData())
			//{
			//	out_error() << L"Not data in the image" << std::endl;
			//	return;
			//}


			//if (m_texture_id != 0)
			//{
			//	glDeleteTextures(1, &m_texture_id);
			//	ValidateOpenGL(L"Can't delete texture");
			//}

			//m_width = image.GetWidth();
			//m_height = image.GetHeight();
			//m_format = ToInternalFormat(image.GetImageFormat());
			//m_pixel_size = 1;
			//m_internal_format = GL_RED;
			//m_internal_type = GL_UNSIGNED_BYTE;

			//if (GL_RED ==  m_format)
			//{
			//	m_pixel_size = 1;
			//	m_internal_format = GL_RED;
			//	m_internal_type = GL_UNSIGNED_BYTE;
			//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//	ValidateOpenGL(L"Can't pixel store i");
			//}
			//else if (GL_R32F == m_format || GL_RGBA == m_format)
			//{
			//	m_pixel_size = 4;
			//	if (GL_R32F == m_format)
			//	{
			//		m_internal_format = GL_RED;
			//		m_internal_type = GL_FLOAT;
			//	}
			//	else if (GL_RGBA == m_format)
			//	{
			//		m_internal_format = GL_RGBA;
			//		m_internal_type = GL_UNSIGNED_BYTE;
			//	}
			//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			//	ValidateOpenGL(L"Can't pixel store i");
			//}
			//else if (GL_RGB == m_format)
			//{
			//	m_pixel_size = 3;
			//	m_internal_format = GL_RGB;
			//	m_internal_type = GL_UNSIGNED_BYTE;
			//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//	ValidateOpenGL(L"Can't pixel store i");
			//}

			//glGenTextures(1, &m_texture_id);
			//ValidateOpenGL(L"Can't generate texture");
			//glBindTexture(GL_TEXTURE_2D, m_texture_id);
			//ValidateOpenGL(L"Can't bind texture");

			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//ValidateOpenGL(L"Can't set up texture min filter");
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//ValidateOpenGL(L"Can't set up mag filter");
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			//ValidateOpenGL(L"Can't set up wrap s");
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
			//ValidateOpenGL(L"Can't set up wrap r");

			//glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, 0);
			//ValidateOpenGL(L"Can't copy data from PBO to texture");

			//glBindTexture(GL_TEXTURE_2D, 0);
			//ValidateOpenGL(L"Can't unbind texture");

			//m_pbo = VideoMemory::Instance()->AllocatePixelBuffer(m_width * m_height * m_pixel_size);
			////m_pbo->Bind();


			//void* data = Map();
			//ValidateOpenGL(L"Can't map buffer");
			//if (data)
			//{
			//	memcpy(data, image.GetData(), image.GetSizeInBytes());
			//	Unmap(0);
			//	ValidateOpenGL(L"Can't unmap buffer");
			//}

			////glBindTexture(GL_TEXTURE_2D, m_texture_id);
			////ValidateOpenGL(L"Can't bind texture");
			////m_pbo->Bind();
			////glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_format, m_internal_type, 0);
			////ValidateOpenGL(L"Can't copy data from PBO to texture object");
			////m_pbo->Unbind();

			//if (m_use_mip_maps)
			//{
			//	glBindTexture(GL_TEXTURE_2D, m_texture_id);
			//	ValidateOpenGL(L"Can't bind texture");
			//	glGenerateMipmap(GL_TEXTURE_2D);
			//	ValidateOpenGL(L"Can't generate mip map levels for texture");
			//	glBindTexture(GL_TEXTURE_2D, 0);
			//	ValidateOpenGL(L"Can't ubind texture");
			//}
		}

		bool CopyFromCPU(int x, int y, int width, int height, const void* data)
		{
			if (x < 0)
				return false;
			if (y < 0)
				return false;
			if (x + width > m_width)
				return false;
			if (y + height > m_height)
				return false;


			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			ValidateOpenGL(L"Can't bind texture");
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, m_format, m_internal_type, data);
			ValidateOpenGL(L"Can't copy data to texture");
			glBindTexture(GL_TEXTURE_2D, 0);
			ValidateOpenGL(L"Can't unbind texture");

			//void* dst = Map();


			//for (int c_y = 0; c_y < height; ++c_y)
			//{
			//	for (int c_x = 0; c_x < width; ++c_x)
			//	{
			//		int dst_x = c_x + x;
			//		int dst_y = c_y + y;

			//	}
			//}

			//for (int c_y = 0; c_y < height; ++c_y)
			//{
			//	int dst_x = x;
			//	int dst_y = c_y + y;
			//	if (m_internal_format == GL_R32F)
			//	{
			//		float* dst_ptr = (float*)dst + dst_x + c_y * m_width;
			//		float* src_ptr = (float*)data + width * c_y;
			//		memcpy_s(dst_ptr, (m_width - dst_x)*sizeof(float), src_ptr, width*sizeof(float));
			//	}
			//	else
			//	{
			//		unsigned char* dst_ptr = (unsigned char*)dst + dst_x + c_y * m_width;
			//		unsigned char* src_ptr = (unsigned char*)data + width * c_y;
			//		memcpy_s(dst_ptr, (m_width - dst_x)*sizeof(unsigned char), src_ptr, width*sizeof(unsigned char));
			//	}
			//}

			//Unmap(dst);

			if (m_use_mip_maps)
			{
				glBindTexture(GL_TEXTURE_2D, m_texture_id);
				ValidateOpenGL(L"Can't bind texture");
				glGenerateMipmap(GL_TEXTURE_2D);
				ValidateOpenGL(L"Can't generate mipmaps");
				glBindTexture(GL_TEXTURE_2D, 0);
				ValidateOpenGL(L"Can't unbind texture");
			}

			return true;
		}

		void Resize(int width, int height)
		{
			if (m_texture_id != 0)
			{
				glDeleteTextures(1, &m_texture_id);
				ValidateOpenGL(L"Can't delete texture");
			}

			m_width = width;
			m_height = height;
			glGenTextures(1, &m_texture_id);
			ValidateOpenGL(L"Can't generate texture");
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			ValidateOpenGL(L"Can't bind texture");
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			ValidateOpenGL(L"Can't pixel store i");
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			ValidateOpenGL(L"Can't tex paramter f");
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			ValidateOpenGL(L"Can't tex prarameter f");
			glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_internal_format, GL_UNSIGNED_BYTE, 0);
			ValidateOpenGL(L"Can't tex image");
			Fill(0);
		}

		bool Create(int width, int height, GLenum format, const void* source, bool use_mipmaps)
		{
			m_use_mip_maps = use_mipmaps;
			if (m_texture_id != 0)
			{
				glDeleteTextures(1, &m_texture_id);
				ValidateOpenGL(L"Can't delete texture");
			}


			m_width = width;
			m_height = height;
			m_internal_format = format;
			m_pixel_size = 1;
			m_format = GL_RED;
			m_internal_type = GL_UNSIGNED_BYTE;

			if (GL_RED ==  m_internal_format)
			{
				m_pixel_size = 1;
				m_format = GL_RED;
				m_internal_type = GL_UNSIGNED_BYTE;
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				ValidateOpenGL(L"Can't pixel store i");
			}
			else if (GL_R32F == m_internal_format || GL_RGBA == m_internal_format)
			{
				m_pixel_size = 4;
				if (GL_R32F == m_internal_format)
				{
					m_internal_type = GL_FLOAT;
					m_format = GL_RED;
				}
				else if (GL_RGBA == m_internal_format)
				{
					m_format = GL_RGBA;
					m_internal_type = GL_UNSIGNED_BYTE;
				}
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				ValidateOpenGL(L"Can't pixel store i");
			}
			else if (GL_RGB == m_internal_format)
			{
				m_pixel_size = 3;
				m_format = GL_RGB;
				m_internal_type = GL_UNSIGNED_BYTE;
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				ValidateOpenGL(L"Can't pixel store i");
			}
			else if (GL_RGBA8 == m_internal_format)
			{
				m_pixel_size = 4;
				m_format = GL_RGBA;
				m_internal_type = GL_UNSIGNED_BYTE;
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				ValidateOpenGL(L"Can't pixel store i");
			}

			glGenTextures(1, &m_texture_id);
			ValidateOpenGL(L"Can't generate texture");
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			ValidateOpenGL(L"Can't bind texture");

			if (use_mipmaps)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				ValidateOpenGL(L"Can't set up texture min filter");
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				ValidateOpenGL(L"Can't set up texture min filter");
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			ValidateOpenGL(L"Can't set up mag filter");
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			ValidateOpenGL(L"Can't set up wrap s");
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
			ValidateOpenGL(L"Can't set up wrap r");

			glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, 0);
			ValidateOpenGL(L"Can't copy data from PBO to texture");

			glBindTexture(GL_TEXTURE_2D, 0);
			ValidateOpenGL(L"Can't unbind texture");

            m_pbo = m_driver->GetVideoMemory()->AllocatePixelBuffer(m_width * m_height * m_pixel_size);
			//m_pbo->Bind();

			//	if data available than copy them
			if (source)
			{
				void* data = Map();
				ValidateOpenGL(L"Can't map buffer");
				if (data)
				{
					memcpy(data, source, m_width * m_height * m_pixel_size);
					Unmap(0);
					ValidateOpenGL(L"Can't unmap buffer");
				}
			}
			//m_pbo->Unbind();
			//glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, m_internal_type, 0);
			//ValidateOpenGL(L"Can't copy data from PBO to texture");
			if (m_use_mip_maps)
				UpdateMipMaps();

			return true;
		}

		void UpdateMipMaps()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			ValidateOpenGL(L"Can't bind texture");
			glGenerateMipmap(GL_TEXTURE_2D);
			ValidateOpenGL(L"Can't generate mip map levels for texture");
			glBindTexture(GL_TEXTURE_2D, 0);
			ValidateOpenGL(L"Can't unbind texture");
		}

		void* Map()
		{
			if (m_pbo)
				return m_pbo->Map();
			return nullptr;
		}

		void Unmap(void*)
		{
			m_pbo->Unmap();
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			ValidateOpenGL(L"Can't bind texture");
			m_pbo->Bind();
			glTexSubImage2D(GL_TEXTURE_2D, 0,0, 0, m_width, m_height, m_format, m_internal_type, 0);
			ValidateOpenGL(L"Can't transfer data from PBO to texture");
			m_pbo->Unbind();
			glBindTexture(GL_TEXTURE_2D, 0);
			ValidateOpenGL(L"Can't unbind texture");
			if (m_use_mip_maps)
				UpdateMipMaps();
		}

		void Fill(unsigned char byte)
		{
			void* dst = Map();
			if (dst)
			{
				memset(dst, byte, m_width*m_height*m_pixel_size);
				Unmap(dst);

				if (m_use_mip_maps)
					UpdateMipMaps();
			}
		}



		int ToInternalFormat(ImageModule::ImageFormat format)
		{
			switch (format)
			{
				//case ImageModule::IMAGE_FORMAT_ALPHA4 : return GL_ALPHA4_EXT ;
				//case ImageModule::IMAGE_FORMAT_ALPHA8 : return GL_ALPHA8_EXT ;
				//case ImageModule::IMAGE_FORMAT_ALPHA12 : return GL_ALPHA12_EXT ;
				//case ImageModule::IMAGE_FORMAT_ALPHA16 : return GL_ALPHA16_EXT ;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT16 : return GL_DEPTH_COMPONENT16 ;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT24 : return GL_DEPTH_COMPONENT24 ;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32 : return GL_DEPTH_COMPONENT32 ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE4 : return GL_LUMINANCE4_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE8 : return GL_LUMINANCE8_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE12 : return GL_LUMINANCE12_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE16 : return GL_LUMINANCE16_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE4_ALPHA4 : return GL_LUMINANCE4_ALPHA4_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE6_ALPHA2 : return GL_LUMINANCE6_ALPHA2_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE8_ALPHA8 : return GL_LUMINANCE8_ALPHA8_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA4 : return GL_LUMINANCE12_ALPHA4_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA12 : return GL_LUMINANCE12_ALPHA12_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE16_ALPHA16 : return GL_LUMINANCE16_ALPHA16_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY4 : return GL_INTENSITY4_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY8 : return GL_INTENSITY8_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY12 : return GL_INTENSITY12_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY16 : return GL_INTENSITY16_EXT ;
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
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX1 : return GL_COLOR_INDEX1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX2 : return GL_COLOR_INDEX2_EXT ;
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX4 : return GL_COLOR_INDEX4_EXT ;
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX8 : return GL_COLOR_INDEX8_EXT ;
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX12 : return GL_COLOR_INDEX12_EXT ;
				//case ImageModule::IMAGE_FORMAT_COLOR_INDEX16 : return GL_COLOR_INDEX16_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1 : return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3 : return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5 : return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8 : return GL_SIGNED_LUMINANCE8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8 : return GL_SIGNED_LUMINANCE8_ALPHA8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_RGB8 : return GL_SIGNED_RGB8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_RGBA8 : return GL_SIGNED_RGBA8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8 : return GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_ALPHA8 : return GL_SIGNED_ALPHA8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_INTENSITY8 : return GL_SIGNED_INTENSITY8_NV ;
				//case ImageModule::IMAGE_FORMAT_HILO16 : return GL_HILO16_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_HILO16 : return GL_SIGNED_HILO16_NV ;
				//case ImageModule::IMAGE_FORMAT_DSDT8 : return GL_DSDT8_NV ;
				//case ImageModule::IMAGE_FORMAT_DSDT8_MAG8 : return GL_DSDT8_MAG8_NV ;
				//case ImageModule::IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8 : return GL_DSDT8_MAG8_INTENSITY8_NV ;
				//case ImageModule::IMAGE_FORMAT_HILO8 : return GL_HILO8_NV ;
				//case ImageModule::IMAGE_FORMAT_SIGNED_HILO8 : return GL_SIGNED_HILO8_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_R16 : return GL_FLOAT_R16_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_R32 : return GL_FLOAT_R32_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RG16 : return GL_FLOAT_RG16_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RGB16 : return GL_FLOAT_RGB16_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RGBA16 : return GL_FLOAT_RGBA16_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RG32 : return GL_FLOAT_RG32_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RGB32 : return GL_FLOAT_RGB32_NV ;
				//case ImageModule::IMAGE_FORMAT_FLOAT_RGBA32 : return GL_FLOAT_RGBA32_NV ;
				//case ImageModule::IMAGE_FORMAT_RGBA_FLOAT32 : return GL_RGBA_FLOAT32_ATI ;
				//case ImageModule::IMAGE_FORMAT_RGB_FLOAT32 : return GL_RGB_FLOAT32_ATI ;
				//case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT32 : return GL_ALPHA_FLOAT32_ATI ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT32 : return GL_INTENSITY_FLOAT32_ATI ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT32 : return GL_LUMINANCE_FLOAT32_ATI ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32 : return GL_LUMINANCE_ALPHA_FLOAT32_APPLE ;
				//case ImageModule::IMAGE_FORMAT_RGBA_FLOAT16 : return GL_RGBA_FLOAT16_ATI ;
				//case ImageModule::IMAGE_FORMAT_RGB_FLOAT16 : return GL_RGB_FLOAT16_ATI ;
				//case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT16 : return GL_ALPHA_FLOAT16_ATI ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT16 : return GL_INTENSITY_FLOAT16_ATI ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT16 : return GL_LUMINANCE_FLOAT16_ATI ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16 : return GL_LUMINANCE_ALPHA_FLOAT16_ATI ;
			case ImageModule::IMAGE_FORMAT_DEPTH24_STENCIL8 : return GL_DEPTH24_STENCIL8 ;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32F : return GL_DEPTH_COMPONENT32F ;
			case ImageModule::IMAGE_FORMAT_DEPTH32F_STENCIL8 : return GL_DEPTH32F_STENCIL8 ;
			case ImageModule::IMAGE_FORMAT_SRGB8 : return GL_SRGB8 ;
			case ImageModule::IMAGE_FORMAT_SRGB8_ALPHA8 : return GL_SRGB8_ALPHA8 ;
				//case ImageModule::IMAGE_FORMAT_SLUMINANCE8 : return GL_SLUMINANCE8 ;
				//case ImageModule::IMAGE_FORMAT_SLUMINANCE8_ALPHA8 : return GL_SLUMINANCE8_ALPHA8 ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1 : return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5 : return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT ;
			case ImageModule::IMAGE_FORMAT_RGB9_E5 : return GL_RGB9_E5 ;
			case ImageModule::IMAGE_FORMAT_R11F_G11F_B10F : return GL_R11F_G11F_B10F ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1 : return GL_COMPRESSED_LUMINANCE_LATC1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1 : return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2 : return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT ;
				//case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2 : return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA32UI : return GL_RGBA32UI ;
			case ImageModule::IMAGE_FORMAT_RGB32UI : return GL_RGB32UI ;
				//case ImageModule::IMAGE_FORMAT_ALPHA32UI : return GL_ALPHA32UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY32UI : return GL_INTENSITY32UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE32UI : return GL_LUMINANCE32UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32UI : return GL_LUMINANCE_ALPHA32UI_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA16UI : return GL_RGBA16UI ;
			case ImageModule::IMAGE_FORMAT_RGB16UI : return GL_RGB16UI ;
				//case ImageModule::IMAGE_FORMAT_ALPHA16UI : return GL_ALPHA16UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY16UI : return GL_INTENSITY16UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE16UI : return GL_LUMINANCE16UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16UI : return GL_LUMINANCE_ALPHA16UI_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA8UI : return GL_RGBA8UI ;
			case ImageModule::IMAGE_FORMAT_RGB8UI : return GL_RGB8UI ;
				//case ImageModule::IMAGE_FORMAT_ALPHA8UI : return GL_ALPHA8UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY8UI : return GL_INTENSITY8UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE8UI : return GL_LUMINANCE8UI_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8UI : return GL_LUMINANCE_ALPHA8UI_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA32I : return GL_RGBA32I ;
			case ImageModule::IMAGE_FORMAT_RGB32I : return GL_RGB32I ;
				//case ImageModule::IMAGE_FORMAT_ALPHA32I : return GL_ALPHA32I_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY32I : return GL_INTENSITY32I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE32I : return GL_LUMINANCE32I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32I : return GL_LUMINANCE_ALPHA32I_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA16I : return GL_RGBA16I ;
			case ImageModule::IMAGE_FORMAT_RGB16I : return GL_RGB16I ;
				//case ImageModule::IMAGE_FORMAT_ALPHA16I : return GL_ALPHA16I_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY16I : return GL_INTENSITY16I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE16I : return GL_LUMINANCE16I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16I : return GL_LUMINANCE_ALPHA16I_EXT ;
			case ImageModule::IMAGE_FORMAT_RGBA8I : return GL_RGBA8I ;
			case ImageModule::IMAGE_FORMAT_RGB8I : return GL_RGB8I ;
				//case ImageModule::IMAGE_FORMAT_ALPHA8I : return GL_ALPHA8I_EXT ;
				//case ImageModule::IMAGE_FORMAT_INTENSITY8I : return GL_INTENSITY8I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE8I : return GL_LUMINANCE8I_EXT ;
				//case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8I : return GL_LUMINANCE_ALPHA8I_EXT ;
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
				throw OpenGLException(L"Unbelievable, but image format is not supported");
			}
		}
	};
}

#endif	//	_H_PUNK_OPENGL_TEXTURE_2D_PBO_IMPL
