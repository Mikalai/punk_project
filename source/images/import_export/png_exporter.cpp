#include "png_exporter.h"
#include "../internal_images/image.h"
#include "../../string/string.h"
#include "../error/module.h"

#ifdef USE_PNG
#include <png/png.h>
#endif // USE_PNG

namespace ImageModule
{
	void PngExporter::Export(const System::string& filename, const Image& image)
	{
	    #ifdef USE_PNG
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;

		/* open the file */
		_wfopen_s(&fp, filename.Data(), L"wb");
		if (fp == NULL)
			throw ImageException(L"Can't open file");

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
			throw ImageException(L"Can't create png structure");
		}

		/* Allocate/initialize the image information data.  REQUIRED */
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr,  NULL);
			throw ImageException(L"Can't create png info structure");
		}

		/* Set error handling.  REQUIRED if you aren't supplying your own
		* error handling functions in the png_create_write_struct() call.
		*/
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			/* If we get here, we had a problem reading the file */
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			throw ImageException(L"Error reading file");
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
		switch (image.GetImageFormat())
		{
		case IMAGE_FORMAT_ALPHA:
			format = PNG_COLOR_TYPE_GRAY;
			break;
		case IMAGE_FORMAT_RGB:
			format = PNG_COLOR_TYPE_RGB;
			break;
		case IMAGE_FORMAT_RGBA:
			format = PNG_COLOR_TYPE_RGBA;
			break;
		}

		png_set_IHDR(png_ptr, info_ptr, image.GetWidth(), image.GetHeight(), image.GetBitDepth(), format,
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
		unsigned mult = 1;
		if (format == PNG_COLOR_TYPE_RGB)
			mult = 3;
		if (format == PNG_COLOR_TYPE_RGBA)
			mult = 4;

		png_bytepp row_pointers = new png_bytep[image.GetHeight()];
		for (int k = 0; k < (int)image.GetHeight(); k++)
		{
			unsigned char *ptr = (unsigned char*)(image.GetData() + k*image.GetWidth()*mult);
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
#else
		throw System::PunkNotImplemented(L"PNG image can't be handled");
#endif  //  USE_PNG
	}
}
