/*
File: ImageLoader.cpp
Author: Abramau Mikalai
Description: Contains rutines for loading images
JPEG - jpeglib
*/

#include <stdio.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "image_loader.h"
#include "error.h"
//#include "jpeg/jpeglib.h"
#include <assert.h>
//#include "bmp/bmp.h"
//#include "dds/nv_dds.h"
//#include "tga/tga.h"
//#include "png/png.h"
//#include "pngpriv.h"

namespace ImageLoader
{
	/*	void Save(Surface* surface, int numComponents, const char* filename)
	{
	#ifdef __linux__
	FILE* f = fopen(filename, "wb");
	#endif
	#ifdef _WIN32
	FILE* f;
	fopen_s(&f, filename, "wb");
	#endif
	BITMAP_FILEHEADER fileHeader;
	memset(&fileHeader, 0, sizeof(fileHeader));
	fileHeader.Signature= 19778;
	fileHeader.Reserved = 0;
	fileHeader.Size = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER)+surface->width*surface->height*3;
	fileHeader.BitsOffset = sizeof(BITMAP_FILEHEADER)+sizeof(BITMAP_HEADER);
	BITMAP_HEADER infoHeader;
	memset(&infoHeader, 0, sizeof(infoHeader));
	infoHeader.SizeImage = sizeof(infoHeader);
	infoHeader.Width = surface->width;
	infoHeader.Height = surface->height;
	infoHeader.Planes = 1;
	infoHeader.Compression = 0;
	infoHeader.BitCount = 24;
	fwrite(&fileHeader, sizeof(fileHeader), 1, f);
	fwrite(&infoHeader, sizeof(infoHeader), 1, f);
	for (int i = 0; i < surface->width*surface->height; i++)
	{
	fwrite(surface->data + i*4 + 2, sizeof(surface->data[0]), 1, f);
	fwrite(surface->data + i*4 + 1, sizeof(surface->data[0]), 1, f);
	fwrite(surface->data + i*4,     sizeof(surface->data[0]), 1, f);
	}
	fclose(f);
	}
	//****************************************************
	//	common staff, but mostly for dds
	//****************************************************
	inline	unsigned long rgbToInt(unsigned long red, unsigned long green, unsigned long blue)
	{
	return (red << 16) | (green << 8) | (blue);
	}

	inline	unsigned long rgbaToInt (unsigned long red, unsigned long green, unsigned long blue, unsigned long alpha)
	{
	return (red << 16) | (green << 8) | (blue) | (alpha << 24);
	}

	// clamps input size to [1-size]
	int clamp_size(int size)
	{
	if (size <= 0)
	size = 1;

	return size;
	}

	void LoadTGA(const char* filename, ImageFile* ImageFile)
	{
	#ifdef __linux__
	FILE *file;
	file = fopen(filename, "rb");
	#endif
	#ifdef _WIN32
	FILE *file;
	fopen_s(&file, filename, "rb");
	#endif
	gliReadTGA(file, filename, ImageFile);

	fclose(file);

	}
	//******************************************************
	//	Loading...
	//******************************************************
	void LoadDDS(const char* filename, ImageFile* ImageFile)
	{
	DDS_HEADER ddsh;
	char filecode[4];
	FILE *fp = 0;
	int width, height, depth;
	int (ImageFile::*sizefunc)(int, int);

	// clear any previously loaded images
	ImageFile->Clear();

	// open file
	#ifdef __linux__
	fp = fopen(filename, "rb");
	#endif
	#ifdef _WIN32
	fopen_s(&fp, filename, "rb");
	#endif
	if (fp == NULL)
	throw ImageError(System::string(L"Can't find dds file: ") + System::string(filename));

	// read in file marker, make sure its a DDS file
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0)
	{
	fclose(fp);
	throw ImageError(System::string(L"It is not a dds file: ") + System::string(filename));
	return;
	}

	// read in DDS header
	fread(&ddsh, sizeof(ddsh), 1, fp);

	// check if ImageFile is a cubempa
	if (ddsh.dwCaps2 & DDS_CUBEMAP)
	ImageFile->cubemap = true;

	// check if ImageFile is a volume texture
	if ((ddsh.dwCaps2 & DDS_VOLUME) && (ddsh.dwDepth > 0))
	ImageFile->volume = true;

	// figure out what the ImageFile format is
	if (ddsh.ddspf.dwFlags & DDS_FOURCC)
	{
	switch(ddsh.ddspf.dwFourCC)
	{
	case FOURCC_DXT1:
	ImageFile->format = IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1;
	ImageFile->components = 3;
	ImageFile->compressed = true;
	break;
	case FOURCC_DXT3:
	ImageFile->format = IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3;
	ImageFile->components = 4;
	ImageFile->compressed = true;
	break;
	case FOURCC_DXT5:
	ImageFile->format = IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5;
	ImageFile->components = 4;
	ImageFile->compressed = true;
	break;
	default:
	fclose(fp);
	throw ImageError(System::string(L"Unknown compress format: ") + System::string(filename));
	}
	}
	else if (ddsh.ddspf.dwFlags == DDS_RGBA && ddsh.ddspf.dwRGBBitCount == 32)
	{
	ImageFile->format = IMAGE_FORMAT_BGRA;
	ImageFile->compressed = false;
	ImageFile->components = 4;
	}
	else if (ddsh.ddspf.dwFlags == DDS_RGB  && ddsh.ddspf.dwRGBBitCount == 32)
	{
	ImageFile->format = IMAGE_FORMAT_BGRA;
	ImageFile->compressed = false;
	ImageFile->components = 4;
	}
	else if (ddsh.ddspf.dwFlags == DDS_RGB  && ddsh.ddspf.dwRGBBitCount == 24)
	{
	ImageFile->format = IMAGE_FORMAT_BGR;
	ImageFile->compressed = false;
	ImageFile->components = 3;
	}
	else
	{
	fclose(fp);
	throw ImageError(System::string(L"Unknown dds format: ") + System::string(filename));
	}

	// store primary surface width/height/depth
	width = ddsh.dwWidth;
	height = ddsh.dwHeight;
	depth = clamp_size(ddsh.dwDepth);   // set to 1 if 0

	// use correct size calculation function depending on whether ImageFile is
	// compressed
	sizefunc = (ImageFile->compressed ? &ImageFile::size_dxtc : &ImageFile::size_rgb);

	// load all surfaces for the ImageFile (6 surfaces for cubemaps)
	for (int n = 0; n < (ImageFile->cubemap ? 6 : 1); n++)
	{
	int size;

	// calculate surface size
	size = (ImageFile->*sizefunc)(width, height)*depth;

	// load surface
	Texture img(width, height, depth, size);
	fread(img.surface.data, 1, img.size, fp);

	ImageFile->align_memory(&img);

	ImageFile->flip(img.surface.data, img.width, img.height, img.depth, img.size);

	int w = clamp_size(width >> 1);
	int h = clamp_size(height >> 1);
	int d = clamp_size(depth >> 1);

	// store number of mipmaps
	int numMipmaps = ddsh.dwMipMapCount;

	// number of mipmaps in file includes main surface so decrease count
	// by one
	if (numMipmaps != 0)
	numMipmaps--;

	// load all mipmaps for current surface
	for (int i = 0; i < numMipmaps && (w || h); i++)
	{
	// calculate mipmap size
	size = (ImageFile->*sizefunc)(w, h)*d;

	Surface mipmap(w, h, d, size);
	fread(mipmap.data, 1, mipmap.size, fp);

	ImageFile->flip(mipmap.data, mipmap.width, mipmap.height, mipmap.depth,
	mipmap.size);

	img.mipmaps.push_back(mipmap);

	// shrink to next power of 2
	w = clamp_size(w >> 1);
	h = clamp_size(h >> 1);
	d = clamp_size(d >> 1);
	}

	ImageFile->textures.push_back(img);
	}

	// swap cubemaps on y axis (since ImageFile is flipped in OGL)
	if (ImageFile->cubemap)
	{
	Texture tmp;
	tmp = ImageFile->textures[3];
	ImageFile->textures[3] = ImageFile->textures[2];
	ImageFile->textures[2] = tmp;
	}

	fclose(fp);

	//valid = true;
	}

	void LoadBMP(const char* filename, ImageFile* image)
	{
	Texture texture;
	CBitmap bitmap;
	if (!bitmap.Load((char*)filename))
	throw ImageError(System::string(L"Can't load bitmap ")+System::string(filename));
	texture.depth = texture.surface.depth = 1;
	texture.width = texture.surface.width = bitmap.GetWidth();
	texture.height = texture.surface.height = bitmap.GetHeight();

	if (bitmap.GetBitCount() == 32)
	{
	image->components = 4;
	image->format = IMAGE_FORMAT_BGRA;
	bitmap.GetBits(0, texture.size, bitmap.GetBitCount());
	texture.surface.size = texture.size;
	texture.surface.data = new unsigned char[texture.surface.size];
	bitmap.GetBits(texture.surface.data, texture.surface.size, texture.surface.depth);
	bitmap.Dispose();
	}
	if (bitmap.GetBitCount() == 24)
	{
	image->components = 3;
	image->format = IMAGE_FORMAT_BGR;
	bitmap.GetBits(0, texture.size, bitmap.GetBitCount());
	texture.surface.size = texture.size;
	texture.surface.data = new unsigned char[texture.surface.size];
	bitmap.GetBits(texture.surface.data, texture.surface.size, bitmap.GetBitCount());
	bitmap.Dispose();
	}
	if (bitmap.GetBitCount() == 16)
	{
	image->components = 3;
	image->format = IMAGE_FORMAT_BGR;
	bitmap.GetBits(0, texture.size, bitmap.GetBitCount());
	texture.surface.size = texture.size;
	texture.surface.data = new unsigned char[texture.surface.size];
	bitmap.GetBits(texture.surface.data, texture.surface.size, bitmap.GetBitCount());
	bitmap.Dispose();
	}
	if (bitmap.GetBitCount() == 8)
	{
	image->format = IMAGE_FORMAT_RGBA;
	image->components = 4;

	unsigned char* data;
	BGRA* palette;
	unsigned paletteSize;
	bitmap.GetBitsWithPalette(0, texture.size, 8, palette, paletteSize);
	data = new unsigned char[texture.size];
	bitmap.GetBitsWithPalette(data, texture.size, 8, palette, paletteSize);
	texture.size = texture.width*texture.height*image->components;
	texture.surface.size = texture.size;
	texture.surface.data = new unsigned char[texture.width*texture.height*image->components];
	for (int i = 0; i < texture.height; i++)
	{
	for (int j = 0; j < texture.width; j++)
	{
	texture.surface.data[i*4*texture.width+j*4+0] = palette[data[i*texture.width+j]].Red;
	texture.surface.data[i*4*texture.width+j*4+1] = palette[data[i*texture.width+j]].Green;
	texture.surface.data[i*4*texture.width+j*4+2] = palette[data[i*texture.width+j]].Blue;
	texture.surface.data[i*4*texture.width+j*4+3] = palette[data[i*texture.width+j]].Alpha;
	}
	}
	delete[] data;
	delete[] palette;
	bitmap.Dispose();
	}
	image->Clear();
	image->compressed = false;
	image->cubemap = false;
	image->volume = false;
	image->textures.push_back(texture);
	}
	*/

	/* write a png file */
	void SaveToPNG(char *file_name, ImageFile* image)
	{
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;
		png_colorp palette;

		/* open the file */
		fp = fopen(file_name, "wb");
		if (fp == NULL)
			return (ERROR);

		/* Create and initialize the png_struct with the desired error handler
		* functions.  If you want to use the default stderr and longjump method,
		* you can supply NULL for the last three parameters.  We also check that
		* the library version is compatible with the one used at compile time,
		* in case we are using dynamically linked libraries.  REQUIRED.
		*/
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
			png_voidp user_error_ptr, user_error_fn, user_warning_fn);

		if (png_ptr == NULL)
		{
			fclose(fp);
			return (ERROR);
		}

		/* Allocate/initialize the image information data.  REQUIRED */
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
			return (ERROR);
		}

		/* Set error handling.  REQUIRED if you aren't supplying your own
		* error handling functions in the png_create_write_struct() call.
		*/
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			/* If we get here, we had a problem reading the file */
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			return (ERROR);
		}

		/* One of the following I/O initialization functions is REQUIRED */
#ifdef streams /* I/O initialization method 1 */
		/* set up the output control if you are using standard C streams */
		png_init_io(png_ptr, fp);
#else no_streams /* I/O initialization method 2 */
		/* If you are using replacement read functions, instead of calling
		* png_init_io() here you would call */
		png_set_write_fn(png_ptr, (void *)user_io_ptr, user_write_fn,
			user_IO_flush_function);
		/* where user_io_ptr is a structure you want available to the callbacks */
#endif no_streams /* only use one initialization method */

#ifdef hilevel
		/* This is the easy way.  Use it if you already have all the
		* image info living info in the structure.  You could "|" many
		* PNG_TRANSFORM flags into the png_transforms integer here.
		*/
		png_write_png(png_ptr, info_ptr, png_transforms, png_voidp_NULL);
#else
		/* This is the hard way */

		/* Set the image information here.  Width and height are up to 2^31,
		* bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
		* the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
		* PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
		* or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
		* PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
		* currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
		*/
		png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, PNG_COLOR_TYPE_???,
			PNG_INTERLACE_????, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

		/* set the palette if there is one.  REQUIRED for indexed-color images */
		palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH
			* sizeof (png_color));
		/* ... set palette colors ... */
		png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);
		/* You must not free palette here, because png_set_PLTE only makes a link to
		the palette that you malloced.  Wait until you are about to destroy
		the png structure. */

		/* optional significant bit chunk */
		/* if we are dealing with a grayscale image then */
		sig_bit.gray = true_bit_depth;
		/* otherwise, if we are dealing with a color image then */
		sig_bit.red = true_red_bit_depth;
		sig_bit.green = true_green_bit_depth;
		sig_bit.blue = true_blue_bit_depth;
		/* if the image has an alpha channel then */
		sig_bit.alpha = true_alpha_bit_depth;
		png_set_sBIT(png_ptr, info_ptr, sig_bit);


		/* Optional gamma chunk is strongly suggested if you have any guess
		* as to the correct gamma of the image.
		*/
		png_set_gAMA(png_ptr, info_ptr, gamma);

		/* Optionally write comments into the image */
		text_ptr[0].key = "Title";
		text_ptr[0].text = "Mona Lisa";
		text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
		text_ptr[1].key = "Author";
		text_ptr[1].text = "Leonardo DaVinci";
		text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
		text_ptr[2].key = "Description";
		text_ptr[2].text = "<long text>";
		text_ptr[2].compression = PNG_TEXT_COMPRESSION_zTXt;
#ifdef PNG_iTXt_SUPPORTED
		text_ptr[0].lang = NULL;
		text_ptr[1].lang = NULL;
		text_ptr[2].lang = NULL;
#endif
		png_set_text(png_ptr, info_ptr, text_ptr, 3);

		/* other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs, */
		/* note that if sRGB is present the gAMA and cHRM chunks must be ignored
		* on read and must be written in accordance with the sRGB profile */

		/* Write the file header information.  REQUIRED */
		png_write_info(png_ptr, info_ptr);

		/* If you want, you can write the info in two steps, in case you need to
		* write your private chunk ahead of PLTE:
		*
		*   png_write_info_before_PLTE(write_ptr, write_info_ptr);
		*   write_my_chunk();
		*   png_write_info(png_ptr, info_ptr);
		*
		* However, given the level of known- and unknown-chunk support in 1.1.0
		* and up, this should no longer be necessary.
		*/

		/* Once we write out the header, the compression type on the text
		* chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
		* PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
		* at the end.
		*/

		/* set up the transformations you want.  Note that these are
		* all optional.  Only call them if you want them.
		*/

		/* invert monochrome pixels */
		png_set_invert_mono(png_ptr);

		/* Shift the pixels up to a legal bit depth and fill in
		* as appropriate to correctly scale the image.
		*/
		png_set_shift(png_ptr, &sig_bit);

		/* pack pixels into bytes */
		png_set_packing(png_ptr);

		/* swap location of alpha bytes from ARGB to RGBA */
		png_set_swap_alpha(png_ptr);

		/* Get rid of filler (OR ALPHA) bytes, pack XRGB/RGBX/ARGB/RGBA into
		* RGB (4 channels -> 3 channels). The second parameter is not used.
		*/
		png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

		/* flip BGR pixels to RGB */
		png_set_bgr(png_ptr);

		/* swap bytes of 16-bit files to most significant byte first */
		png_set_swap(png_ptr);

		/* swap bits of 1, 2, 4 bit packed pixel formats */
		png_set_packswap(png_ptr);

		/* turn on interlace handling if you are not using png_write_image() */
		if (interlacing)
			number_passes = png_set_interlace_handling(png_ptr);
		else
			number_passes = 1;

		/* The easiest way to write the image (you may have a different memory
		* layout, however, so choose what fits your needs best).  You need to
		* use the first method if you aren't handling interlacing yourself.
		*/
		png_uint_32 k, height, width;
		png_byte image[height][width*bytes_per_pixel];
		png_bytep row_pointers[height];
		for (k = 0; k < height; k++)
			row_pointers[k] = image + k*width*bytes_per_pixel;

		/* One of the following output methods is REQUIRED */
#ifdef entire /* write out the entire image data in one call */
		png_write_image(png_ptr, row_pointers);

		/* the other way to write the image - deal with interlacing */

#else no_entire /* write out the image data by one or more scanlines */
		/* The number of passes is either 1 for non-interlaced images,
		* or 7 for interlaced images.
		*/
		for (pass = 0; pass < number_passes; pass++)
		{
			/* Write a few rows at a time. */
			png_write_rows(png_ptr, &row_pointers[first_row], number_of_rows);

			/* If you are only writing one row at a time, this works */
			for (y = 0; y < height; y++)
			{
				png_write_rows(png_ptr, &row_pointers[y], 1);
			}
		}
#endif no_entire /* use only one output method */

		/* You can write optional chunks like tEXt, zTXt, and tIME at the end
		* as well.  Shouldn't be necessary in 1.1.0 and up as all the public
		* chunks are supported and you can use png_set_unknown_chunks() to
		* register unknown chunks into the info structure to be written out.
		*/

		/* It is REQUIRED to call this to finish writing the rest of the file */
		png_write_end(png_ptr, info_ptr);
#endif hilevel

		/* If you png_malloced a palette, free it here (don't free info_ptr->palette,
		as recommended in versions 1.0.5m and earlier of this example; if
		libpng mallocs info_ptr->palette, libpng will free it).  If you
		allocated it with malloc() instead of png_malloc(), use free() instead
		of png_free(). */
		png_free(png_ptr, palette);
		palette=NULL;

		/* Similarly, if you png_malloced any data that you passed in with
		png_set_something(), such as a hist or trans array, free it here,
		when you can be sure that libpng is through with it. */
		png_free(png_ptr, trans);
		trans=NULL;

		/* clean up after the write, and free any memory allocated */
		png_destroy_write_struct(&png_ptr, &info_ptr);

		/* close the file */
		fclose(fp);

		/* that's it */
		return (OK);
	}
	void LoadPNG(const char* filename, ImageFile* image)
	{
#define bytesToCheck 8
		Texture texture;
		FILE* f = 0;
#ifdef __linux__
		f = fopen(filename, "rb");
#endif
#ifdef _WIN32
		fopen_s(&f, filename, "rb");
#endif
		if (!f)
			throw ImageError(L"Can't open png file");

		char sig[bytesToCheck];
		fread(sig, 1, bytesToCheck, f);
		if ( png_sig_cmp((png_bytep)sig, (png_size_t)0, bytesToCheck) )
			throw ImageError(L"It is not a png file: ");

		png_structp png_ptr;
		png_infop info_ptr;
		png_uint_32 width, height;

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

		width = texture.width = png_get_image_width(png_ptr, info_ptr);
		height = texture.height = png_get_image_height(png_ptr, info_ptr);
		int	bpp = png_get_bit_depth(png_ptr, info_ptr);
		int	colorType = png_get_color_type(png_ptr, info_ptr);
		int	rowBytes = png_get_rowbytes(png_ptr, info_ptr);
		int	numComponents = 0;

		switch ( colorType )
		{
		case PNG_COLOR_TYPE_RGB:
			numComponents = image->components = 3;
			image->format = IMAGE_FORMAT_RGB;
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			numComponents = image->components = 4;
			image->format = IMAGE_FORMAT_RGBA;
			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			numComponents = image->components = 1;
			image->format = IMAGE_FORMAT_ALPHA;
			break;

		case PNG_COLOR_TYPE_PALETTE:
			numComponents = image->components = 3;
			break;

		default:
			break;
		}

		if ( numComponents == 0 )
		{
			png_destroy_read_struct ( &png_ptr, &info_ptr, (png_infopp) NULL );
			throw ImageError(L"Can't load file: ");
		}

		texture.size = texture.width*texture.height*image->components;
		texture.depth = 1;
		texture.surface.Create(texture.width, texture.height, texture.depth, texture.size);

		//Texture * texture = new Texture ( width, height, numComponents );

		//		if ( texture == NULL || texture -> getData () == NULL )
		//		{
		//			png_destroy_read_struct ( &png_ptr, &info_ptr, (png_infopp) NULL );
		//
		//			return NULL;
		//		}


		png_bytep * rowPtr  = new png_bytep[height];
		unsigned long     * lineBuf = new unsigned long[width];

		for (unsigned i = 0; i < height; i++ )
			rowPtr [i] = (png_bytep) malloc ( rowBytes );

		png_read_image ( png_ptr, rowPtr );

		unsigned char* offset = texture.surface.data;

		// now rebuild the ImageFile
		for (unsigned i = 0; i < height; i++ )
		{
			png_bytep	ptr = rowPtr [i];

			if ( colorType == PNG_COLOR_TYPE_RGB )
			{
				for ( unsigned x = 0; x < width; x++, ptr += 3 )
					lineBuf [x] = rgbToInt ( ptr [2], ptr [1], ptr [0] );
			}
			else
				if ( colorType == PNG_COLOR_TYPE_RGB_ALPHA )
				{
					for ( unsigned x = 0; x < width; x++, ptr += 4 )
						lineBuf [x] = rgbaToInt ( ptr [2], ptr [1], ptr [0], ptr [3] );
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

							for (int i = 0; i < numColors; i++)
								pngPal [i].red   =
								pngPal [i].green =
								pngPal [i].blue  = (i * 255) / numEntries;
						}
						else
						{
							for (int i = 0; i < numColors; i++ )
							{
								pngPal [i].red   = (pngPal [i].red   * 255) / numEntries;
								pngPal [i].green = (pngPal [i].green * 255) / numEntries;
								pngPal [i].blue  = (pngPal [i].blue  * 255) / numEntries;
							}
						}

						for ( i = 0; i < width; i++ )
						{
							int	ind = ptr [i];

							lineBuf [i] = rgbToInt ( pngPal [ind].blue, pngPal [ind].green, pngPal [ind].red );
						}
					}
					else
					{
						for ( unsigned x = 0; x < width; x++, ptr++ )
							lineBuf [x] = ptr [0];
					}

					texture.surface.PutLine(i, image->components, lineBuf);

					free ( rowPtr [i] );
		}

		delete[] lineBuf;
		delete[] rowPtr;

		png_read_end            ( png_ptr, end_info );
		png_destroy_read_struct ( &png_ptr, &info_ptr, &end_info );

		//return texture;
		image->textures.push_back(texture);/**/

	}

	void LoadJPEG(const char* filename, ImageFile* ImageFile)
	{
		//
		//	ImageFile parameters
		//
		ImageFile->compressed = false;
		ImageFile->cubemap = false;
		ImageFile->volume = false;
		ImageFile->format = IMAGE_FORMAT_RGB;
		Texture texture;

		jpeg_decompress_struct ds;
		jpeg_error_mgr errorManager;

		ds.err = jpeg_std_error(&errorManager);

		jpeg_create_decompress(&ds);

		FILE* f = 0;
#ifdef __linux__
		f = fopen(filename, "rb");
#endif
#ifdef _WIN32
		fopen_s(&f, filename, "rb");
#endif

		jpeg_stdio_src(&ds, f);

		jpeg_read_header(&ds, TRUE);

		jpeg_start_decompress(&ds);

		texture.width = texture.surface.width = ds.output_width;
		texture.height = texture.surface.height = ds.output_height;
		ImageFile->components = ds.out_color_components;

		texture.surface.data = new unsigned char[ds.output_width*ds.output_components*ds.output_height];
		texture.surface.size = ds.output_width*ds.output_components*ds.output_height;
		texture.surface.depth = ds.out_color_components*8;
		texture.size = ds.output_width*ds.output_components*ds.output_height;
		texture.depth = ds.out_color_components*8;
		int row_stride = ds.output_width*ds.output_components;
		JSAMPARRAY buffer = (*ds.mem->alloc_sarray)
			((j_common_ptr) &ds, JPOOL_IMAGE, row_stride, 1);

		while (ds.output_scanline < ds.output_height)
		{
			jpeg_read_scanlines(&ds, buffer, 1);
			memcpy(texture.surface.data + (ds.output_height - ds.output_scanline)*row_stride, buffer[0], row_stride);
		}

		jpeg_finish_decompress(&ds);

		jpeg_destroy_decompress(&ds);

		fclose(f);

		ImageFile->Clear();
		ImageFile->textures.push_back(texture);
	}

	ImageFile* Load(const char* filename)
	{
		ImageFile* result = new ImageFile();
		std::string file = filename;
		if (file.rfind(".jpg") != std::string::npos)
			LoadJPEG(filename, result);
		else if (file.rfind(".jpeg") != std::string::npos)
			LoadJPEG(filename, result);
		//		else if (file.rfind(".bmp") != std::string::npos)
		//			LoadBMP(filename, result);
		//		else if (file.rfind(".tga") != std::string::npos)
		//			LoadTGA(filename, result);
		//		else if (file.rfind(".dds") != std::string::npos)
		//			LoadDDS(filename, result);
		else if (file.rfind(".png") != std::string::npos)
			LoadPNG(filename, result);
		else
			throw ImageError(L"Unsupported file format");
		/*if (file.rfind(".gif") != std::string::npos)
		LoadJPEG(filename, &result);*/
		return result;
	}

	void Free(ImageFile* ImageFile)
	{
		delete ImageFile;
	}

	ImageFile* ConvertHeightMapToNormalMap(const ImageFile* image, float scale)
	{
		ImageFile* result = new ImageFile;
		result->components = 4;
		result->format = IMAGE_FORMAT_RGBA;
		for (std::vector<Texture>::const_iterator texture = image->textures.begin(); texture != image->textures.end(); texture++)
		{
			float oneOver255 = 1.0f / 255.0f;
			Texture normalMap(texture->width, texture->height, texture->depth, texture->width*texture->height*4);
			unsigned char* out = normalMap.surface.data;
			if ( out == NULL )
			{
				delete result;
				throw ImageError(L"Can't create normal map from height map");
			}
			int	offs = 0;					// offset to normalMap
			const unsigned char* pixels = texture->surface.data;
			int width = texture->width;
			int height = texture->height;

			for ( int i = 0; i < height; i++ )
			{
				for ( int j = 0; j < width; j++ )
				{
					// convert height values to [0,1] range
					float	c  = pixels [i*width              + j]           * oneOver255;
					float	cx = pixels [i*width              + (j+1)%width] * oneOver255;
					float	cy = pixels [((i+1)%height)*width + j]           * oneOver255;

					// find derivatives
					float	dx = (c - cx) * scale;
					float	dy = (c - cy) * scale;

					// normalize
					float	len = (float) sqrt ( dx*dx + dy*dy + 1 );

					// get normal
					float	nx = dy   / len;
					float	ny = -dx  / len;
					float	nz = 1.0f / len;

					// now convert to color and store in map
					out [offs    ] = (unsigned char)(128 + 127*nx);
					out [offs + 1] = (unsigned char)(128 + 127*ny);
					out [offs + 2] = (unsigned char)(128 + 127*nz);
					out [offs + 3] = 255;

					offs += 4;
				}
			}
			result->textures.push_back(normalMap);
		}
		return result;
	}

	void BuildMipMapsForNormalMap(ImageFile* image)
	{
		double EPS = 1e-10;
		for (std::vector<Texture>::iterator texture = image->textures.begin(); texture != image->textures.end(); texture++)
		{
			if (texture->mipmaps.size() != 0)
				continue;
			int width = texture->width;
			int height = texture->height;
			int components = image->components;
			width /= 2;
			height /= 2;

			Surface prevSurface = texture->surface;
			while (width && height)
			{
				Surface surface(width, height, 1, width*height*components);

				float	oneOver127 = 1.0f / 127.0f;
				float	oneOver255 = 1.0f / 255.0f;

				unsigned char* in  = prevSurface.data;
				unsigned char* out = surface.data;
				int	w = prevSurface.width;
				int	h = prevSurface.height;
				float v [3];						// here we will store x, y, z components

				for ( int i = 0; i < h; i += 2 )
				{
					for ( int j = 0; j < w; j += 2 )
					{
						int	iNext = (i+1) % h;
						int	jNext = (j+1) % w;

						float mag00 = oneOver255 * in [3 + i*w + j];
						float mag01 = oneOver255 * in [3 + i*w + jNext];
						float mag10 = oneOver255 * in [3 + iNext*w + j];
						float mag11 = oneOver255 * in [3 + iNext*w + jNext];

						// sum up values for RGB components, converting to [-1,1]
						for ( int k = 0; k < 3; k++ )
						{
							v [k]  = mag00 * (oneOver127 * in [k + i*w     + j]     - 1.0f);
							v [k] += mag01 * (oneOver127 * in [k + i*w     + jNext] - 1.0f);
							v [k] += mag10 * (oneOver127 * in [k + iNext*w + j]     - 1.0f);
							v [k] += mag11 * (oneOver127 * in [k + iNext*w + jNext] - 1.0f);
						}

						// compute length of (x,y,z)
						float	length = (float)sqrt ( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );

						// check for degenerated case
						if ( length < EPS )
						{
							v [0] = 0;
							v [1] = 0;
							v [2] = 1;
						}
						else
						{
							v [0] /= length;
							v [1] /= length;
							v [2] /= length;
						}

						int	index = (i >> 1)*width + (j >> 1);

						// pack normalized vector into color values
						out[index]     = (unsigned char)(128 + 127*v[0]);
						out[index + 1] = (unsigned char)(128 + 127*v[1]);
						out[index + 2] = (unsigned char)(128 + 127*v[2]);

						// store averaged length as alpha component
						length *= 0.25;		// since it was build on 2x2 summed values

						if ( length > 1.0f - EPS )
							out[index + 3] = 255;
						else
							out[index + 3] = (unsigned char)(255 * length);
					}
				}
				prevSurface = surface;
				texture->mipmaps.push_back(surface);
				width /= 2;
				height /= 2;
			}
		}
	}
}
