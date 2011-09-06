#ifdef _WIN32
#include <windows.h>
#include <exception>
#endif

#include <stdio.h>
#include "jpeglib.h"
#include "image.h"
#include "driver.h"

TImage::TImage(Driver* driver) : m_data(0), m_driver(driver)
{
}

TImage::~TImage()
{
	DELETE_ARRAY(m_data);
}

void TImage::LoadJPEG(const char* filename)
{
	jpeg_decompress_struct ds;
	jpeg_error_mgr errorManager;

	ds.err = jpeg_std_error(&errorManager);

	jpeg_create_decompress(&ds);

	FILE* f = 0;
	fopen_s(&f, filename, "rb");

	jpeg_stdio_src(&ds, f);

	jpeg_read_header(&ds, TRUE);

	jpeg_start_decompress(&ds);

	m_width = ds.output_width;
	m_height = ds.output_height;
	m_bitPerPixel = ds.out_color_components;

	//unsigned char* data = new unsigned char[ds.output_width*ds.output_components*ds.output_height];
	DELETE_ARRAY(m_data);

	m_data = new unsigned char[ds.output_width*ds.output_components*ds.output_height];
	int row_stride = ds.output_width*ds.output_components;
	JSAMPARRAY buffer = (*ds.mem->alloc_sarray)
		((j_common_ptr) &ds, JPOOL_IMAGE, row_stride, 1);

	while (ds.output_scanline < ds.output_height)
	{
		jpeg_read_scanlines(&ds, buffer, 1);
		memcpy(m_data + (ds.output_height - ds.output_scanline)*row_stride, buffer[0], row_stride);
	}

	jpeg_finish_decompress(&ds);

	jpeg_destroy_decompress(&ds);

	fclose(f);
}

void TImage::LoadTGA(const char *filename)
{
}

void TImage::LoadBMP(const char *filename)
{
}

void TImage::LoadDDS(const char *filename)
{
}


unsigned char* TImage::GetData()
{
	return m_data;
}

int TImage::GetWidth() const
{
	return m_width;
}

int TImage::GetHeight() const
{
	return m_height;
}

int TImage::GetBitsPerPixel() const
{
	return m_bitPerPixel;
}

bool TImage::Render(float x, float y)
{
	if (m_data == NULL)
		return false;

	glDisable(GL_TEXTURE_2D);

	glRasterPos2f(x, y);

	glDrawPixels(m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_data);

	return true;
}

IImage& TImage::operator =(const IImage &image)
{
	if (this != &image)
	{
		TImage* img = (TImage*)&image;
		m_width = img->m_width;
		m_height = img->m_height;
		m_bitPerPixel = img->m_bitPerPixel;
		m_driver = img->m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img->m_data, m_width*m_height*3);
	}
	return *this;
}

TImage::TImage(const IImage &image)
{
	if (this != &image)
	{
		TImage* img = (TImage*)&image;
		m_width = img->m_width;
		m_height = img->m_height;
		m_bitPerPixel = img->m_bitPerPixel;
		m_driver = img->m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img->m_data, m_width*m_height*3);
	}
}

TImage::TImage(const TImage &img)
{
	if (this != &img)
	{
		m_width = img.m_width;
		m_height = img.m_height;
		m_bitPerPixel = img.m_bitPerPixel;
		m_driver = img.m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img.m_data, m_width*m_height*3);
	}
}
#include <windows.h>
#include <stdio.h>
#include <jpeglib.h>
#include <exception>
#include "Image.h"
#include "Driver.h"

TImage::TImage(TDriver* driver) : m_data(0), m_driver(driver)
{
}

TImage::~TImage()
{
	DELETE_ARRAY(m_data);
}

void TImage::LoadJPEG(const char* filename)
{
	jpeg_decompress_struct ds;
	jpeg_error_mgr errorManager;

	ds.err = jpeg_std_error(&errorManager);

	jpeg_create_decompress(&ds);

	FILE* f = 0;
	fopen_s(&f, filename, "rb");

	jpeg_stdio_src(&ds, f);

	jpeg_read_header(&ds, TRUE);

	jpeg_start_decompress(&ds);
	
	m_width = ds.output_width;
	m_height = ds.output_height;
	m_bitPerPixel = ds.out_color_components;

	//unsigned char* data = new unsigned char[ds.output_width*ds.output_components*ds.output_height];
	DELETE_ARRAY(m_data);

	m_data = new unsigned char[ds.output_width*ds.output_components*ds.output_height];
	int row_stride = ds.output_width*ds.output_components;
	JSAMPARRAY buffer = (*ds.mem->alloc_sarray)
		((j_common_ptr) &ds, JPOOL_IMAGE, row_stride, 1);

	while (ds.output_scanline < ds.output_height)
	{
		jpeg_read_scanlines(&ds, buffer, 1);
		memcpy(m_data + (ds.output_height - ds.output_scanline)*row_stride, buffer[0], row_stride); 		
	}

	jpeg_finish_decompress(&ds);

	jpeg_destroy_decompress(&ds);

	fclose(f);
}

void TImage::LoadTGA(const char *filename)
{
}

void TImage::LoadBMP(const char *filename)
{
}

void TImage::LoadDDS(const char *filename)
{
}


unsigned char* TImage::GetData()
{
	return m_data;
}

int TImage::GetWidth() const
{
	return m_width;
}

int TImage::GetHeight() const
{
	return m_height;
}

int TImage::GetBitsPerPixel() const
{
	return m_bitPerPixel;
}

bool TImage::Render(float x, float y)
{
	if (m_data == NULL)
		return false;

	glDisable(GL_TEXTURE_2D);

	glRasterPos2f(x, y);

	glDrawPixels(m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_data);

	return true;
}

IImage& TImage::operator =(const IImage &image)
{
	if (this != &image)
	{
		TImage* img = (TImage*)&image;
		m_width = img->m_width;
		m_height = img->m_height;
		m_bitPerPixel = img->m_bitPerPixel;
		m_driver = img->m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img->m_data, m_width*m_height*3);
	}
	return *this;
}

TImage::TImage(const IImage &image)
{
	if (this != &image)
	{
		TImage* img = (TImage*)&image;
		m_width = img->m_width;
		m_height = img->m_height;
		m_bitPerPixel = img->m_bitPerPixel;
		m_driver = img->m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img->m_data, m_width*m_height*3);
	}	
}

TImage::TImage(const TImage &img)
{
	if (this != &img)
	{
		m_width = img.m_width;
		m_height = img.m_height;
		m_bitPerPixel = img.m_bitPerPixel;
		m_driver = img.m_driver;
		DELETE_ARRAY(m_data);
		m_data = new unsigned char[m_width*m_height*3];
		memcpy(m_data, img.m_data, m_width*m_height*3);
	}	
}