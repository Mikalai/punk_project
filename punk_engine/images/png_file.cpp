#include <stdio.h>
#include "png_file.h"
#include "error.h"
#include <png.h>

namespace Image
{
	PngFile::PngFile() : ImageFile() 
	{
	}

	void PngFile::Load(const wchar_t *file)
	{
		m_rep = m_rep->GetOwnCopy();

#define bytesToCheck 8
		FILE* f = 0;
#ifdef __linux__
		f = fopen(filename, "rb");
#endif
#ifdef _WIN32
		_wfopen_s(&f, file, L"rb");
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
		m_rep->m_bpp = bpp;

		switch ( colorType )
		{
		case PNG_COLOR_TYPE_RGB:
			channels = 3;
			format = IMAGE_FORMAT_RGBA;
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

		m_rep->m_format = format;
		m_rep->SetSize(width, height);

		png_bytep * rowPtr  = new png_bytep[height];
		unsigned long     * lineBuf = new unsigned long[width];

		for (unsigned i = 0; i < height; i++ )
			rowPtr [i] = (png_bytep) malloc ( rowBytes );

		png_read_image ( png_ptr, rowPtr );

		unsigned char* offset = m_rep->m_data;

		// now rebuild the ImageFile
		for (int i = 0; i < height; i++ )
		{
			png_bytep	ptr = rowPtr [i];

			if ( colorType == PNG_COLOR_TYPE_RGB )
			{
				for ( unsigned x = 0; x < width; x++, ptr += 3 )
					lineBuf [x] = ptr[2] << 16 | ptr[1] << 8 | ptr[0];
			}
			else
				if ( colorType == PNG_COLOR_TYPE_RGB_ALPHA )
				{
					for ( unsigned x = 0; x < width; x++, ptr += 4 )
						lineBuf [x] = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
				}
				else
					if ( colorType == PNG_COLOR_TYPE_PALETTE )
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

						for (int z = 0; z < width; z++ )
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
					unsigned char* offset = m_rep->m_data + i*width*4;	//alligned
					for (int k = 0; k < width; k++, src += 4)
					{
						if (channels == 3)
						{							
							*offset++ = src[0];
							*offset++ = src[1];
							*offset++ = src[2];
							*offset++ = 0xFF;
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

	void PngFile::Save(const wchar_t *file)
	{
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;

		/* open the file */
		_wfopen_s(&fp, file, L"wb");
		if (fp == NULL)
			throw ImageError(L"Can't open file");

		/* Create and initialize the png_struct with the desired error handler
		* functions.  If you want to use the default stderr and longjump method,
		* you can supply NULL for the last three parameters.  We also check that
		* the library version is compatible with the one used at compile time,
		* in case we are using dynamically linked libraries.  REQUIRED.
		*/
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
		{
			fclose(fp);
			throw ImageError(L"Can't create png structure");
		}

		/* Allocate/initialize the image information data.  REQUIRED */
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr,  NULL);
			throw ImageError(L"Can't create png info structure");
		}

		/* Set error handling.  REQUIRED if you aren't supplying your own
		* error handling functions in the png_create_write_struct() call.
		*/
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			/* If we get here, we had a problem reading the file */
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			throw ImageError(L"Error reading file");
		}

		/* set up the output control if you are using standard C streams */
		png_init_io(png_ptr, fp);

		/* This is the hard way */

		/* Set the image information here.  m_width and m_height are up to 2^31,
		* bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
		* the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
		* PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
		* or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
		* PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
		* currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
		*/

		int format;
		switch (m_rep->m_format)
		{
		case IMAGE_FORMAT_ALPHA:
			format = PNG_COLOR_TYPE_GRAY_ALPHA;
			break;
		case IMAGE_FORMAT_RGB:
			format = PNG_COLOR_TYPE_RGB;
			break;
		case IMAGE_FORMAT_RGBA:
			format = PNG_COLOR_TYPE_RGBA;
			break;
		}

		png_set_IHDR(png_ptr, info_ptr, m_rep->m_width, m_rep->m_height, m_rep->m_bpp, format,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);


		/* Write the file header information.  REQUIRED */
		png_write_info(png_ptr, info_ptr);

		/* invert monochrome pixels */
		//png_set_invert_mono(png_ptr);

		/* pack pixels into bytes */
		//png_set_packing(png_ptr);

		/* swap location of alpha bytes from ARGB to RGBA */
//		png_set_swap_alpha(png_ptr);

		/* Get rid of filler (OR ALPHA) bytes, pack XRGB/RGBX/ARGB/RGBA into
		* RGB (4 channels -> 3 channels). The second parameter is not used.
		*/
		//png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

		/* flip BGR pixels to RGB */
		//png_set_bgr(png_ptr);

		/* swap bytes of 16-bit files to most significant byte first */
		png_set_swap(png_ptr);

		/* swap bits of 1, 2, 4 bit packed pixel formats */
		//png_set_packswap(png_ptr);

		int number_passes = 1;

		/* The easiest way to write the image (you may have a different memory
		* layout, however, so choose what fits your needs best).  You need to
		* use the first method if you aren't handling interlacing yourself.
		*/
		png_bytepp row_pointers = new png_bytep[m_rep->m_height];
		for (int k = 0; k < m_rep->m_height; k++)
		{
			unsigned char *ptr = (unsigned char*)(m_rep->m_data + k*m_rep->m_width*4);
			row_pointers[k] = ptr;
		}

		png_write_image(png_ptr, row_pointers);

		/* It is REQUIRED to call this to finish writing the rest of the file */
		png_write_end(png_ptr, info_ptr);

		delete[] row_pointers;


		/* clean up after the write, and free any memory allocated */
		png_destroy_write_struct(&png_ptr, &info_ptr);

		/* close the file */
		fclose(fp);
	}
}