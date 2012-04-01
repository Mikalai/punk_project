#include "png_importer.h"
#include "../internal_images/image_impl.h"
#include <png.h>
#include <stdio.h>

namespace ImageModule
{
	PngImporter::PngImporter()
		: Importer()
	{}

	void PngImporter::Load(const System::string& file)
	{

#define bytesToCheck 8
		FILE* f = 0;
#ifdef __linux__
		f = fopen(filename, "rb");
#endif
#ifdef _WIN32
		_wfopen_s(&f, file.Data(), L"rb");
#endif
		if (!f)
			throw ImageError(L"Can't open png file");

		char sig[bytesToCheck];
		fread(sig, 1, bytesToCheck, f);
		if ( png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck) )
			throw ImageError(L"It is not a png file: ");

		png_structp png_ptr;
		png_infop info_ptr;

		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
			throw ImageError(L"Can't load file: ");

		info_ptr = png_create_info_struct(png_ptr);

		if (info_ptr == NULL)
		{
			png_destroy_read_struct ( &png_ptr, (png_infopp) NULL, (png_infopp)NULL );
			throw ImageError(L"Can't load file: ");
		}

		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			throw ImageError(L"Can't load file: ");
		}

		png_init_io(png_ptr, f);
		png_set_sig_bytes(png_ptr, bytesToCheck);
		png_read_info(png_ptr, info_ptr);

		unsigned width = png_get_image_width(png_ptr, info_ptr);
		unsigned height = png_get_image_height(png_ptr, info_ptr);
		unsigned bpp = png_get_bit_depth(png_ptr, info_ptr);
		int	colorType = png_get_color_type(png_ptr, info_ptr);
		int	rowBytes = png_get_rowbytes(png_ptr, info_ptr);
		unsigned channels = 0;
		ImageFormat format = IMAGE_FORMAT_ALPHA;
		impl_image->m_components = bpp / 8;

		switch ( colorType )
		{
		case PNG_COLOR_TYPE_RGB:
			channels = 3;
			format = IMAGE_FORMAT_RGB;
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			channels = 4;
			format = IMAGE_FORMAT_RGBA;
			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			channels = 1;
			format = IMAGE_FORMAT_ALPHA;
			break;

		case PNG_COLOR_TYPE_PALETTE:
			channels = 3;
			break;

		default:
			break;
		}

		if ( channels == 0 )
		{
			png_destroy_read_struct ( &png_ptr, &info_ptr, (png_infopp) NULL );
			throw ImageError(L"Can't load file: ");
		}
				
		impl_image->Create(width, height, channels);
		impl_image->m_format = format;
		impl_image->m_components = channels;

		png_bytep * rowPtr  = new png_bytep[height];
		unsigned long     * lineBuf = new unsigned long[width];

		for (unsigned i = 0; i < height; i++ )
			rowPtr [i] = (png_bytep) malloc ( rowBytes );

		png_read_image ( png_ptr, rowPtr );

		Component* offset = GetData();

		// now rebuild the ImageFile
		for (int i = 0; i < (int)height; i++ )
		{
			png_bytep	ptr = rowPtr [i];

			if ( colorType == PNG_COLOR_TYPE_RGB )
			{
				for ( unsigned x = 0; x < width; x++, ptr += 3 )
					lineBuf [x] = ptr[2] << 16 | ptr[1] << 8 | ptr[0];
			}
			else if ( colorType == PNG_COLOR_TYPE_RGB_ALPHA )
			{
				for ( unsigned x = 0; x < width; x++, ptr += 4 )
					lineBuf [x] = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
			}
			else if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY)
			{
				for ( unsigned x = 0; x < width; x++, ptr += 1)
					lineBuf [x] = ptr[0];
			}
			else if ( colorType == PNG_COLOR_TYPE_PALETTE )
			{
				png_color * pngPal = NULL;
				png_color   pal [256];
				int			numColors;
				int			numEntries = (1 << bpp) - 1;

				if (!png_get_PLTE ( png_ptr, info_ptr, (png_colorp *)&pngPal, &numColors ) )
				{
					// This is a grayscale ImageFile, build a grayscale palette
					numColors = numEntries + 1;
					pngPal    = pal;

					for (int z = 0; z < numColors; z++)
						pngPal [z].red   =
						pngPal [z].green =
						pngPal [z].blue  = (z * 255) / numEntries;
				}
				else
				{
					for (int z = 0; z < numColors; z++ )
					{
						pngPal [z].red   = (pngPal [z].red   * 255) / numEntries;
						pngPal [z].green = (pngPal [z].green * 255) / numEntries;
						pngPal [z].blue  = (pngPal [z].blue  * 255) / numEntries;
					}
				}

				for (int z = 0; z < (int)width; z++ )
				{
					int	ind = ptr [z];

					lineBuf [z] = pngPal[ind].blue | pngPal[ind].green << 8 | pngPal[ind].red << 16;
				}
			}
			else
			{
				for ( unsigned x = 0; x < width; x++, ptr++ )
					lineBuf [x] = ptr [0];
			}

			unsigned char* src = (unsigned char*)lineBuf;
			unsigned char* offset = GetData() + i*width*channels;	//alligned
			for (int k = 0; k < (int)width; k++, src += 4)
			{
				if (channels == 1)
				{
					*offset++ = src[0];
				}
				else if (channels == 3)
				{							
					*offset++ = src[0];
					*offset++ = src[1];
					*offset++ = src[2];
					//*offset++ = 0xFF;
				}
				else
				{
					*offset++ = src[0];
					*offset++ = src[1];
					*offset++ = src[2];
					*offset++ = src[3];
				}						
			}

			free ( rowPtr [i] );
		}

		delete[] lineBuf;
		delete[] rowPtr;

		png_read_end            ( png_ptr, end_info );
		png_destroy_read_struct ( &png_ptr, &info_ptr, &end_info );
	}
}

