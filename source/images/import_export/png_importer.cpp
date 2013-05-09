#include <fstream>
#include <istream>
#include <ostream>

#include "../../system/logger.h"

#include "png_importer.h"
#include "../internal_images/image_impl.h"
#include <stdio.h>

#ifdef USE_PNG
#include <png/png.h>
#endif // USE_PNG

namespace ImageModule
{
	PngImporter::PngImporter()
		: Importer()
	{}

#ifdef USE_PNG
	void read(png_structp png, png_bytep data, png_size_t size)
	{
		std::istream& stream = *(std::istream*)(png_get_io_ptr(png));
		stream.read((char*)data, size);
	}
#endif  //  USE_PNG

	bool PngImporter::Load(std::istream& stream, Image* image)
	{
#ifdef USE_PNG
		const int bytesToCheck = 8;

		char sig[bytesToCheck];
		stream.read(sig, bytesToCheck);
		if ( png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck) )
		{
			out_error() << L"It is not a png file: " << std::endl;
			return false;
		}

		png_structp png_ptr;
		png_infop info_ptr;

		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
		{
			out_error() << L"Can't load file: " << std::endl;
			return false;
		}

		info_ptr = png_create_info_struct(png_ptr);

		if (info_ptr == NULL)
		{
			png_destroy_read_struct ( &png_ptr, (png_infopp) NULL, (png_infopp)NULL );
			out_error() <<  L"Can't load file: " << std::endl;
			return false;
		}

		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			out_error() << L"Can't load file: " << std::endl;
			return false;
		}

		png_set_read_fn(png_ptr, &stream, read);
		//png_init_io(png_ptr, );
		png_set_sig_bytes(png_ptr, bytesToCheck);
		png_read_info(png_ptr, info_ptr);

		unsigned width = png_get_image_width(png_ptr, info_ptr);
		unsigned height = png_get_image_height(png_ptr, info_ptr);
		unsigned bpp = png_get_bit_depth(png_ptr, info_ptr);
		int	colorType = png_get_color_type(png_ptr, info_ptr);
		int	rowBytes = png_get_rowbytes(png_ptr, info_ptr);
		unsigned channels = png_get_channels(png_ptr, info_ptr);
		ImageFormat format = IMAGE_FORMAT_ALPHA;
		image->SetDepth(bpp);

		switch ( colorType )
		{
		case PNG_COLOR_TYPE_RGB:
			//channels = bpp / 8;
			format = IMAGE_FORMAT_RGB;
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			//channels = bpp / 8;
			format = IMAGE_FORMAT_RGBA;
			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			//channels = bpp / 8;
			format = IMAGE_FORMAT_ALPHA;
			break;

		case PNG_COLOR_TYPE_PALETTE:
			channels = 3;
			format = IMAGE_FORMAT_RGB;
			break;

		default:
			break;
		}

//		if (colorType == PNG_COLOR_TYPE_PALETTE)
//			png_set_palette_to_rgb(png_ptr);

//		if (colorType == PNG_COLOR_TYPE_GRAY && bpp < 8)
//			png_set_expand_gray_1_2_4_to_8(png_ptr);

//		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
//			png_set_tRNS_to_alpha(png_ptr);

		if ( channels == 0 )
		{
			png_destroy_read_struct ( &png_ptr, &info_ptr, (png_infopp) NULL );
			throw ImageException(L"Can't load file: ");
		}

		image->Create(width, height, channels);
		image->SetFormat(format);
		image->SetNumChannels(channels);
		image->SetDepth(bpp);

		png_bytep * rowPtr  = new png_bytep[height];
		unsigned long     * lineBuf = new unsigned long[width];

		for (unsigned i = 0; i < height; i++ )
			rowPtr [i] = (png_bytep) malloc ( rowBytes );

		png_read_image ( png_ptr, rowPtr );

		Component* offset = image->GetData();

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

					lineBuf [z] = pngPal[ind].red | pngPal[ind].green << 8 | pngPal[ind].blue << 16;
				}
			}
			else
			{
				for ( unsigned x = 0; x < width; x++, ptr++ )
					lineBuf [x] = ptr [0];
			}

			unsigned char* src = (unsigned char*)lineBuf;
			unsigned char* offset = image->GetData() + height*width*channels - (i+1)*width*channels;	//alligned
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

		return true;
#else   //  USE_PNG
        (void)stream; (void)image;
        throw System::PunkNotImplemented(L"Can't import png, because png lib was not included in the project");
#endif  //  USE_PNG
	}

	bool PngImporter::Load(const System::string& file)
	{
		std::ifstream stream(file.ToStdString().c_str(), std::ios_base::binary);
		if (!stream.is_open())
		{
			out_error() << L"Can't open file: " + file << std::endl;
			return false;
		}
		Load(stream, this);
		stream.close();
		return true;
	}
}

