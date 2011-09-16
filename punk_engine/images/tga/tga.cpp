
/* This file is derived from (actually an earlier version of)... */

/* The GIMP -- an ImageFile manipulation program
* Copyright (C) 1995 Spencer Kimball and Peter Mattis
*
* Id: tga.c,v 1.5 1998/05/26 08:46:36 yosh Exp $
* TrueVision Targa loading and saving file filter for the Gimp.
* Targa code Copyright (C) 1997 Raphael FRANCOIS and Gordon Matzigkeit
*
* The Targa reading and writing code was written from scratch by
* Raphael FRANCOIS <fraph@ibm.net> and Gordon Matzigkeit
* <gord@gnu.ai.mit.edu> based on the TrueVision TGA File Format
* Specification, Version 2.0:
*
*   <URL:ftp://ftp.truevision.com/pub/TGA.File.Format.Spec/>
*
* It does not contain any code written for other TGA file loaders.
* Not even the RLE handling. ;)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
//#include <gl3/gl3.h>
//#include "../../system/exception.h"
#include "../image_loader.h"
#include "../error.h"

namespace ImageLoader
{

	typedef struct
	{
		unsigned char idLength;
		unsigned char colorMapType;

		// The ImageFile type.
#define TGA_TYPE_MAPPED 1
#define TGA_TYPE_COLOR 2
#define TGA_TYPE_GRAY 3
#define TGA_TYPE_MAPPED_RLE 9
#define TGA_TYPE_COLOR_RLE 10
#define TGA_TYPE_GRAY_RLE 11
		unsigned char imageType;

		// Color Map Specification.
		// We need to separately specify high and low bytes to avoid endianness
		// and alignment problems.
		unsigned char colorMapIndexLo, colorMapIndexHi;
		unsigned char colorMapLengthLo, colorMapLengthHi;
		unsigned char colorMapSize;

		// ImageFile Specification.
		unsigned char xOriginLo, xOriginHi;
		unsigned char yOriginLo, yOriginHi;

		unsigned char widthLo, widthHi;
		unsigned char heightLo, heightHi;

		unsigned char bpp;

		/* ImageFile descriptor.
		3-0: attribute bpp
		4:   left-to-right ordering
		5:   top-to-bottom ordering
		7-6: zero
		*/
#define TGA_DESC_ABITS 0x0f
#define TGA_DESC_HORIZONTAL 0x10
#define TGA_DESC_VERTICAL 0x20
		unsigned char descriptor;

	}
	TgaHeader;

	typedef struct {
		unsigned int extensionAreaOffset;
		unsigned int developerDirectoryOffset;
#define TGA_SIGNATURE "TRUEVISION-XFILE"
		char signature[16];
		char dot;
		char null;
	}
	TgaFooter;

	static char error[256];
	static unsigned int verbose = 0;
	static int totbytes = 0;

	typedef struct {
		unsigned char *statebuf;
		int statelen;
		int laststate;
	} RLEstate;

	static int
		std_fread(RLEstate *rleInfo, unsigned char *buf, unsigned int datasize, unsigned int nelems, FILE *fp)
	{
		if (verbose > 1) {
			totbytes += nelems * datasize;
			printf("TGA: std_fread %d (total %d)\n",
				nelems * datasize, totbytes);
		}
		return fread(buf, datasize, nelems, fp);
	}

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#define RLE_PACKETSIZE 0x80

	/* Decode a bufferful of file. */
	static int
		rle_fread(RLEstate *rleInfo, unsigned char *vbuf, unsigned int datasize, unsigned int nelems, FILE *fp)
	{

		unsigned char *buf = vbuf;
		int j, k;
		int buflen, count, bytes, curbytes;
		unsigned char *p;

		/* Scale the buffer length. */
		buflen = nelems * datasize;

		j = 0;
		curbytes = totbytes;
		while (j < buflen) {
			if (rleInfo->laststate < rleInfo->statelen) {
				/* Copy bytes from our previously decoded buffer. */
				bytes = MIN(buflen - j, rleInfo->statelen - rleInfo->laststate);
				memcpy(buf + j, rleInfo->statebuf + rleInfo->laststate, bytes);
				j += bytes;
				rleInfo->laststate += bytes;

				/* If we used up all of our state bytes, then reset them. */
				if (rleInfo->laststate >= rleInfo->statelen) {
					rleInfo->laststate = 0;
					rleInfo->statelen = 0;
				}

				/* If we filled the buffer, then exit the loop. */
				if (j >= buflen) break;
			}

			/* Decode the next packet. */
			count = fgetc(fp);
			if (count == EOF) {
				if (verbose) printf("TGA: hit EOF while looking for count\n");
				return j / datasize;
			}

			/* Scale the byte length to the size of the data. */
			bytes = ((count & ~RLE_PACKETSIZE) + 1) * datasize;

			if (j + bytes <= buflen) {
				/* We can copy directly into the ImageFile buffer. */
				p = buf + j;
			} else {
#ifdef PROFILE
				printf("TGA: needed to use statebuf for %d bytes\n", buflen - j);
#endif
				/* Allocate the state buffer if we haven't already. */
				if (!rleInfo->statebuf) {
					rleInfo->statebuf = (unsigned char *) malloc(RLE_PACKETSIZE * datasize);
				}
				p = rleInfo->statebuf;
			}

			if (count & RLE_PACKETSIZE) {
				/* Fill the buffer with the next value. */
				if (fread(p, datasize, 1, fp) != 1) {
					if (verbose) {
						printf("TGA: EOF while reading %d/%d element RLE packet\n",
							bytes, datasize);
					}
					return j / datasize;
				}

				/* Optimized case for single-byte encoded data. */
				if (datasize == 1) {
					memset(p + 1, *p, bytes - 1);
				} else {
					for (k = datasize; k < bytes; k += datasize) {
						memcpy(p + k, p, datasize);
					}
				}
			} else {
				/* Read in the buffer. */
				if (fread(p, bytes, 1, fp) != 1) {
					if (verbose) {
						printf("TGA: EOF while reading %d/%d element raw packet\n",
							bytes, datasize);
					}
					return j / datasize;
				}
			}

			if (verbose > 1) {
				totbytes += bytes;
				if (verbose > 2) {
					printf("TGA: %s packet %d/%d\n",
						(count & RLE_PACKETSIZE) ? "RLE" : "raw",
						bytes, totbytes);
				}
			}

			/* We may need to copy bytes from the state buffer. */
			if (p == rleInfo->statebuf) {
				rleInfo->statelen = bytes;
			} else {
				j += bytes;
			}
		}

		if (verbose > 1) {
			printf("TGA: rle_fread %d/%d (total %d)\n",
				nelems * datasize, totbytes - curbytes, totbytes);
		}
		return nelems;
	}

	void gliReadTGA(FILE *fp, const char *name, ImageFile* ImageFile)
	{
		Texture texture;
		TgaHeader tgaHeader;
		TgaFooter tgaFooter;
		char horzrev, vertrev;
		int width, height, bpp;
		int start, end, dir;
		int i, j, k;
		int pelbytes, wbytes;
		ImageFormat format;
		int components;
		RLEstate rleRec;
		RLEstate *rleInfo;
		int rle;
		int index, colors, length;
		unsigned char *cmap, *pixels, *data;
		int (*myfread)(RLEstate *rleInfo, unsigned char*, size_t, size_t, FILE*);

		/* Check the footer. */
		if (fseek(fp, 0L - sizeof(tgaFooter), SEEK_END)
			|| fread(&tgaFooter, sizeof(tgaFooter), 1, fp) != 1) {
				sprintf(error, "TGA: Cannot read footer from \"%s\"", name);
				throw ImageError();
		}

		/* Check the signature. */
		if (memcmp(tgaFooter.signature, TGA_SIGNATURE,
			sizeof(tgaFooter.signature)) == 0) {
				if (verbose) printf("TGA: found New TGA\n");
		} else {
			if (verbose) printf("TGA: found Original TGA\n");
		}

		if (fseek(fp, 0, SEEK_SET) ||
			fread(&tgaHeader, sizeof(tgaHeader), 1, fp) != 1) {
				sprintf(error, "TGA: Cannot read header from \"%s\"", name);
            throw ImageError(System::string(error));
		}

		if (verbose && tgaHeader.idLength) {
			char *idString = (char*) malloc(tgaHeader.idLength);

			if (fread(idString, tgaHeader.idLength, 1, fp) != 1) {
				sprintf(error, "TGA: Cannot read ID field in \"%s\"", name);
				printf("%s\n", error);
			} else {
				printf("TGA: ID field: \"%*s\"\n", tgaHeader.idLength, idString);
			}
			free(idString);
		} else {
			/* Skip the ImageFile ID field. */
			if (tgaHeader.idLength && fseek(fp, tgaHeader.idLength, SEEK_CUR)) {
				sprintf(error, "TGA: Cannot skip ID field in \"%s\"", name);
				throw ImageError(System::string(error));
			}
		}

		/* Reassemble the multi-byte values correctly, regardless of
		host endianness. */
		width = (tgaHeader.widthHi << 8) | tgaHeader.widthLo;
		height = (tgaHeader.heightHi << 8) | tgaHeader.heightLo;
		bpp = tgaHeader.bpp;
		if (verbose) {
			printf("TGA: width=%d, height=%d, bpp=%d\n", width, height, bpp);
		}

		horzrev = tgaHeader.descriptor & TGA_DESC_HORIZONTAL;
		vertrev = !(tgaHeader.descriptor & TGA_DESC_VERTICAL);
		if (verbose && horzrev) printf("TGA: horizontal reversed\n");
		if (verbose && vertrev) printf("TGA: vertical reversed\n");

		rle = 0;
		switch (tgaHeader.imageType) {
  case TGA_TYPE_MAPPED_RLE:
	  rle = 1;
	  if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_MAPPED:
	  /* Test for alpha channel. */
	  format = IMAGE_FORMAT_RGB;
	  components = 1;
	  if (verbose) {
		  printf("TGA: %d bit indexed ImageFile (%d bit palette)\n",
			  tgaHeader.colorMapSize, bpp);
	  }
	  break;

  case TGA_TYPE_GRAY_RLE:
	  rle = 1;
	  if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_GRAY:
	  format = IMAGE_FORMAT_ALPHA;
	  components = 1;
	  if (verbose) printf("TGA: %d bit grayscale ImageFile\n", bpp);
	  break;

  case TGA_TYPE_COLOR_RLE:
	  rle = 1;
	  if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_COLOR:
	  /* Test for alpha channel. */
	  if (bpp == 32) {
		  format = IMAGE_FORMAT_BGRA;// GL_BGRA_EXT; //GL_RGBA;
		  components = 4;
		  if (verbose) {
			  printf("TGA: %d bit color ImageFile with alpha channel\n", bpp);
		  }
	  } else {
		  format = IMAGE_FORMAT_BGR;
		  components = 3;
		  if (verbose) printf("TGA: %d bit color ImageFile\n", bpp);
	  }
	  break;

  default:
	  sprintf(error,
		  "TGA: unrecognized ImageFile type %d\n", tgaHeader.imageType);
			throw ImageError(System::string(error));
		}

		if ((format == IMAGE_FORMAT_BGRA && bpp != 32) ||
			(format == IMAGE_FORMAT_BGR && bpp != 24) ||
			((format == IMAGE_FORMAT_BGR || format == IMAGE_FORMAT_RGB) && bpp != 8)) {
				/* FIXME: We haven't implemented bit-packed fields yet. */
				sprintf(error, "TGA: channel sizes other than 8 bits are unimplemented");
				throw ImageError(System::string(error));
		}

		/* Check that we have a color map only when we need it. */
		if (format == IMAGE_FORMAT_RGB) {
			if (tgaHeader.colorMapType != 1) {
				sprintf(error, "TGA: indexed ImageFile has invalid color map type %d\n",
					tgaHeader.colorMapType);
				throw ImageError(System::string(error));
			}
		} else if (tgaHeader.colorMapType != 0) {
			sprintf(error, "TGA: non-indexed ImageFile has invalid color map type %d\n",
				tgaHeader.colorMapType);
			throw ImageError(System::string(error));
		}

		if (tgaHeader.colorMapType == 1) {
			/* We need to read in the colormap. */
			index = (tgaHeader.colorMapIndexHi << 8) | tgaHeader.colorMapIndexLo;
			length = (tgaHeader.colorMapLengthHi << 8) | tgaHeader.colorMapLengthLo;

			if (verbose) {
				printf("TGA: reading color map (%d + %d) * (%d / 8)\n",
					index, length, tgaHeader.colorMapSize);
			}
			if (length == 0) {
				sprintf(error, "TGA: invalid color map length %d", length);
				throw ImageError(System::string(error));
			}
			if (tgaHeader.colorMapSize != 24) {
				/* We haven't implemented bit-packed fields yet. */
				sprintf(error, "TGA: channel sizes other than 8 bits are unimplemented");
                throw ImageError(System::string(error));
			}

			pelbytes = tgaHeader.colorMapSize / 8;
			colors = length + index;
			cmap = (unsigned char*)malloc (colors * pelbytes);

			/* Zero the entries up to the beginning of the map. */
			memset(cmap, 0, index * pelbytes);

			/* Read in the rest of the colormap. */
			if (fread(cmap, pelbytes, length, fp) != (size_t) length) {
				sprintf(error, "TGA: error reading colormap (ftell == %ld)\n",
					ftell (fp));
				throw ImageError(System::string(error));
			}

			if (pelbytes >= 3) {
				/* Rearrange the colors from BGR to RGB. */
				int tmp;
				for (j = index; j < length * pelbytes; j += pelbytes) {
					tmp = cmap[j];
					cmap[j] = cmap[j + 2];
					cmap[j + 2] = tmp;
				}
			}
		} else {
			colors = 0;
			cmap = NULL;
		}

		/* Allocate the data. */
		pelbytes = bpp / 8;
		pixels = (unsigned char *) malloc (width * height * pelbytes);

		if (rle) {
			rleRec.statebuf = 0;
			rleRec.statelen = 0;
			rleRec.laststate = 0;
			rleInfo = &rleRec;
			myfread = rle_fread;
		} else {
			rleInfo = NULL;
			myfread = std_fread;
		}

		wbytes = width * pelbytes;

		if (vertrev) {
			start = 0;
			end = height;
			dir = 1;
		} else {
			/* We need to reverse loading order of rows. */
			start = height-1;
			end = -1;
			dir = -1;
		}

		for (i = start; i != end; i += dir) {
			data = pixels + i*wbytes;

			/* Suck in the data one row at a time. */
			if (myfread(rleInfo, data, pelbytes, width, fp) != width) {
				/* Probably premature end of file. */
				if (verbose) {
					printf ("TGA: error reading (ftell == %ld, width=%d)\n",
						ftell(fp), width);
				}
				throw ImageError(L"Error somewhere in tga");
			}

			if (horzrev) {
				/* We need to mirror row horizontally. */
				for (j = 0; j < width/2; j++) {
					unsigned char tmp;

					for (k = 0; k < pelbytes; k++) {
						tmp = data[j*pelbytes+k];
						data[j*pelbytes+k] = data[(width-j-1)*pelbytes+k];
						data[(width-j-1)*pelbytes+k] = tmp;
					}
				}
			}
		}

		if (rle) {
			free(rleInfo->statebuf);
		}

		if (fgetc (fp) != EOF) {
			if (verbose) printf ("TGA: too much input data, ignoring extra...\n");
		}

		//genericImage = (tgaImage*) malloc(sizeof(tgaImage));
		texture.size = width*height*components;
		texture.width = width;
		texture.height = height;
		texture.depth = 1;
		ImageFile->format = format;
		ImageFile->components = components;
		//texture->cmapEntries = colors;
		//texture->cmapFormat = GL_BGR_EXT;  // XXX fix me
		//texture.ImageFile.cmap = cmap;
		texture.surface.Create(width, height, texture.depth, texture.size);
		memcpy(texture.surface.data, pixels, texture.size);

		free(pixels);

		ImageFile->textures.push_back(texture);
	}

	int
		gliVerbose(int newVerbose)
	{
		verbose = newVerbose;
		return verbose;
	}
}
