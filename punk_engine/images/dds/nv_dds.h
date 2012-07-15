/*
	File: nv_dds.h
	Author: nvidia
*/
#ifndef __NV_DDS_H__
#define __NV_DDS_H__

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <string>
#include <vector>

using namespace std;

#define DDS_FOURCC 0x00000004
#define DDS_RGB    0x00000040
#define DDS_RGBA   0x00000041
#define DDS_DEPTH  0x00800000

#define DDS_COMPLEX 0x00000008
#define DDS_CUBEMAP 0x00000200
#define DDS_VOLUME  0x00200000

#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3

#define GL_BGR_EXT  0x80E0
#define GL_BGRA_EXT 0x80E1

#define FOURCC_DXT1 0x31545844 //(MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT3 0x33545844 //(MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT5 0x35545844 //(MAKEFOURCC('D','X','T','5'))

struct DDS_PIXELFORMAT
{
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwFourCC;
    unsigned long dwRGBBitCount;
    unsigned long dwRBitMask;
    unsigned long dwGBitMask;
    unsigned long dwBBitMask;
    unsigned long dwABitMask;
};

struct DXTColBlock
{
	unsigned short col0;
	unsigned short col1;

	unsigned char row[4];
};

struct DXT3AlphaBlock
{
	unsigned short row[4];
};

struct DXT5AlphaBlock
{
	unsigned char alpha0;
	unsigned char alpha1;

    unsigned char row[6];
};

struct DDS_HEADER
{
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwHeight;
    unsigned long dwWidth;
    unsigned long dwPitchOrLinearSize;
    unsigned long dwDepth;
    unsigned long dwMipMapCount;
    unsigned long dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    unsigned long dwCaps1;
    unsigned long dwCaps2;
    unsigned long dwReserved2[3];
};

#endif
