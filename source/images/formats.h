#ifndef _H_PUNK_IMAGE_FORMATS
#define _H_PUNK_IMAGE_FORMATS

namespace ImageModule
{
	enum ImageFormat { IMAGE_FORMAT_ALPHA4,
		IMAGE_FORMAT_ALPHA8,
		IMAGE_FORMAT_ALPHA12,
		IMAGE_FORMAT_ALPHA16,
		IMAGE_FORMAT_DEPTH_COMPONENT16,
		IMAGE_FORMAT_DEPTH_COMPONENT24,
		IMAGE_FORMAT_DEPTH_COMPONENT32,
		IMAGE_FORMAT_LUMINANCE4,
		IMAGE_FORMAT_LUMINANCE8,
		IMAGE_FORMAT_LUMINANCE12,
		IMAGE_FORMAT_LUMINANCE16,
		IMAGE_FORMAT_LUMINANCE4_ALPHA4,
		IMAGE_FORMAT_LUMINANCE6_ALPHA2,
		IMAGE_FORMAT_LUMINANCE8_ALPHA8,
		IMAGE_FORMAT_LUMINANCE12_ALPHA4,
		IMAGE_FORMAT_LUMINANCE12_ALPHA12,
		IMAGE_FORMAT_LUMINANCE16_ALPHA16,
		IMAGE_FORMAT_INTENSITY4,
		IMAGE_FORMAT_INTENSITY8,
		IMAGE_FORMAT_INTENSITY12,
		IMAGE_FORMAT_INTENSITY16,
		IMAGE_FORMAT_R3_G3_B2,
		IMAGE_FORMAT_RGB4,
		IMAGE_FORMAT_RGB5,
		IMAGE_FORMAT_RGB8,
		IMAGE_FORMAT_RGB10,
		IMAGE_FORMAT_RGB12,
		IMAGE_FORMAT_RGB16,
		IMAGE_FORMAT_RGBA2,
		IMAGE_FORMAT_RGBA4,
		IMAGE_FORMAT_RGB5_A1,
		IMAGE_FORMAT_RGBA8,
		IMAGE_FORMAT_RGB10_A2,
		IMAGE_FORMAT_RGBA12,
		IMAGE_FORMAT_RGBA16,
		IMAGE_FORMAT_COLOR_INDEX1,
		IMAGE_FORMAT_COLOR_INDEX2,
		IMAGE_FORMAT_COLOR_INDEX4,
		IMAGE_FORMAT_COLOR_INDEX8,
		IMAGE_FORMAT_COLOR_INDEX12,
		IMAGE_FORMAT_COLOR_INDEX16,
		IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1,
		IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3,
		IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5,
		IMAGE_FORMAT_SIGNED_LUMINANCE8,
		IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8,
		IMAGE_FORMAT_SIGNED_RGB8,
		IMAGE_FORMAT_SIGNED_RGBA8,
		IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8,
		IMAGE_FORMAT_SIGNED_ALPHA8,
		IMAGE_FORMAT_SIGNED_INTENSITY8,
		IMAGE_FORMAT_HILO16,
		IMAGE_FORMAT_SIGNED_HILO16,
		IMAGE_FORMAT_DSDT8,
		IMAGE_FORMAT_DSDT8_MAG8,
		IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8,
		IMAGE_FORMAT_HILO8,
		IMAGE_FORMAT_SIGNED_HILO8,
		IMAGE_FORMAT_FLOAT_R16,
		IMAGE_FORMAT_FLOAT_R32,
		IMAGE_FORMAT_FLOAT_RG16,
		IMAGE_FORMAT_FLOAT_RGB16,
		IMAGE_FORMAT_FLOAT_RGBA16,
		IMAGE_FORMAT_FLOAT_RG32,
		IMAGE_FORMAT_FLOAT_RGB32,
		IMAGE_FORMAT_FLOAT_RGBA32,
		IMAGE_FORMAT_RGBA_FLOAT32,
		IMAGE_FORMAT_RGB_FLOAT32,
		IMAGE_FORMAT_ALPHA_FLOAT32,
		IMAGE_FORMAT_INTENSITY_FLOAT32,
		IMAGE_FORMAT_LUMINANCE_FLOAT32,
		IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32,
		IMAGE_FORMAT_RGBA_FLOAT16,
		IMAGE_FORMAT_RGB_FLOAT16,
		IMAGE_FORMAT_ALPHA_FLOAT16,
		IMAGE_FORMAT_INTENSITY_FLOAT16,
		IMAGE_FORMAT_LUMINANCE_FLOAT16,
		IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16,
		IMAGE_FORMAT_DEPTH24_STENCIL8,
		IMAGE_FORMAT_DEPTH_COMPONENT32F,
		IMAGE_FORMAT_DEPTH32F_STENCIL8,
		IMAGE_FORMAT_SRGB8,
		IMAGE_FORMAT_SRGB8_ALPHA8,
		IMAGE_FORMAT_SLUMINANCE8,
		IMAGE_FORMAT_SLUMINANCE8_ALPHA8,
		IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1,
		IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1,
		IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3,
		IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5,
		IMAGE_FORMAT_RGB9_E5,
		IMAGE_FORMAT_R11F_G11F_B10F,
		IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1,
		IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1,
		IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2,
		IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2,
		IMAGE_FORMAT_RGBA32UI,
		IMAGE_FORMAT_RGB32UI,
		IMAGE_FORMAT_ALPHA32UI,
		IMAGE_FORMAT_INTENSITY32UI,
		IMAGE_FORMAT_LUMINANCE32UI,
		IMAGE_FORMAT_LUMINANCE_ALPHA32UI,
		IMAGE_FORMAT_RGBA16UI,
		IMAGE_FORMAT_RGB16UI,
		IMAGE_FORMAT_ALPHA16UI,
		IMAGE_FORMAT_INTENSITY16UI,
		IMAGE_FORMAT_LUMINANCE16UI,
		IMAGE_FORMAT_LUMINANCE_ALPHA16UI,
		IMAGE_FORMAT_RGBA8UI,
		IMAGE_FORMAT_RGB8UI,
		IMAGE_FORMAT_ALPHA8UI,
		IMAGE_FORMAT_INTENSITY8UI,
		IMAGE_FORMAT_LUMINANCE8UI,
		IMAGE_FORMAT_LUMINANCE_ALPHA8UI,
		IMAGE_FORMAT_RGBA32I,
		IMAGE_FORMAT_RGB32I,
		IMAGE_FORMAT_ALPHA32I,
		IMAGE_FORMAT_INTENSITY32I,
		IMAGE_FORMAT_LUMINANCE32I,
		IMAGE_FORMAT_LUMINANCE_ALPHA32I,
		IMAGE_FORMAT_RGBA16I,
		IMAGE_FORMAT_RGB16I,
		IMAGE_FORMAT_ALPHA16I,
		IMAGE_FORMAT_INTENSITY16I,
		IMAGE_FORMAT_LUMINANCE16I,
		IMAGE_FORMAT_LUMINANCE_ALPHA16I,
		IMAGE_FORMAT_RGBA8I,
		IMAGE_FORMAT_RGB8I,
		IMAGE_FORMAT_ALPHA8I,
		IMAGE_FORMAT_INTENSITY8I,
		IMAGE_FORMAT_LUMINANCE8I,
		IMAGE_FORMAT_LUMINANCE_ALPHA8I,
		IMAGE_FORMAT_RG32UI,
		IMAGE_FORMAT_R32UI,
		IMAGE_FORMAT_RG16UI,
		IMAGE_FORMAT_R16UI,
		IMAGE_FORMAT_RG8UI,
		IMAGE_FORMAT_R8UI,
		IMAGE_FORMAT_RG32I,
		IMAGE_FORMAT_R32I,
		IMAGE_FORMAT_RG16I,
		IMAGE_FORMAT_R16I,
		IMAGE_FORMAT_RG8I,
		IMAGE_FORMAT_R8I,
		IMAGE_FORMAT_RG8,
		IMAGE_FORMAT_R8,
		IMAGE_FORMAT_RG16,
		IMAGE_FORMAT_R16,
		IMAGE_FORMAT_RG16F,
		IMAGE_FORMAT_R16F,
		IMAGE_FORMAT_RG32F,
		IMAGE_FORMAT_R32F,
		IMAGE_FORMAT_BGRA,
		IMAGE_FORMAT_BGR,		
		IMAGE_FORMAT_ALPHA,
		IMAGE_FORMAT_RGBA,
		IMAGE_FORMAT_RGB,
		IMAGE_FORMAT_RED, 
		IMAGE_FORMAT_BAD};
}
#endif