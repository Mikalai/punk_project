#include "internal_formats.h"
#ifdef _WIN32
#include <Windows.h>
#endif  //  _WIN32

#include "../gl/glcorearb.h"

namespace Gpu
{
	namespace OpenGL
	{
        int ImageDataTypeToOpenGL(ImageModule::DataType type)
        {
            switch (type)
            {
            case ImageModule::IMAGE_DATA_TYPE_BYTE:
                return GL_UNSIGNED_BYTE;
                break;
            case ImageModule::IMAGE_DATA_TYPE_SIGNED_SHORT:
            case ImageModule::IMAGE_DATA_TYPE_UNSIGNED_SHORT:
                return GL_UNSIGNED_SHORT;
            case ImageModule::IMAGE_DATA_TYPE_UNSIGNED_INT:
            case ImageModule::IMAGE_DATA_TYPE_SIGNED_INT:
                return GL_UNSIGNED_INT;
            case ImageModule::IMAGE_DATA_TYPE_FLOAT:
                return GL_FLOAT;
            default:
                return -1;
            }
        }

		int ImageFormatToOpenGL(ImageModule::ImageFormat format)
		{
			switch (format)
			{
			case ImageModule::IMAGE_FORMAT_ALPHA4:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA12:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA16:
				break;
            case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT:
                return GL_DEPTH_COMPONENT;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT16:
                return GL_DEPTH_COMPONENT16;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT24:
                return GL_DEPTH_COMPONENT24;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32:
                return GL_DEPTH_COMPONENT32;
			case ImageModule::IMAGE_FORMAT_LUMINANCE4:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE8:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE12:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE16:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE4_ALPHA4:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE6_ALPHA2:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE8_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA4:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE12_ALPHA12:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE16_ALPHA16:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY4:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY8:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY12:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY16:
				break;
			case ImageModule::IMAGE_FORMAT_R3_G3_B2:
				break;
			case ImageModule::IMAGE_FORMAT_RGB4:
				break;
			case ImageModule::IMAGE_FORMAT_RGB5:
				break;
			case ImageModule::IMAGE_FORMAT_RGB8:
				break;
			case ImageModule::IMAGE_FORMAT_RGB10:
				break;
			case ImageModule::IMAGE_FORMAT_RGB12:
				break;
			case ImageModule::IMAGE_FORMAT_RGB16:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA2:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA4:
				break;
			case ImageModule::IMAGE_FORMAT_RGB5_A1:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA8:
				return GL_RGBA8;
				break;
			case ImageModule::IMAGE_FORMAT_RGB10_A2:
                return GL_RGB10_A2;
				break;
			case ImageModule::IMAGE_FORMAT_RGBA12:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA16:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX1:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX2:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX4:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX8:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX12:
				break;
			case ImageModule::IMAGE_FORMAT_COLOR_INDEX16:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_LUMINANCE8_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_RGB8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_RGBA8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_RGB8_UNSIGNED_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_INTENSITY8:
				break;
			case ImageModule::IMAGE_FORMAT_HILO16:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_HILO16:
				break;
			case ImageModule::IMAGE_FORMAT_DSDT8:
				break;
			case ImageModule::IMAGE_FORMAT_DSDT8_MAG8:
				break;
			case ImageModule::IMAGE_FORMAT_DSDT8_MAG8_INTENSITY8:
				break;
			case ImageModule::IMAGE_FORMAT_HILO8:
				break;
			case ImageModule::IMAGE_FORMAT_SIGNED_HILO8:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_R16:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_R32:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RG16:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RGB16:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RGBA16:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RG32:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RGB32:
				break;
			case ImageModule::IMAGE_FORMAT_FLOAT_RGBA32:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_RGB_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT32:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_RGB_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA_FLOAT16:
				break;
			case ImageModule::IMAGE_FORMAT_DEPTH24_STENCIL8:
				break;
			case ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT32F:
                return GL_DEPTH_COMPONENT32F;
			case ImageModule::IMAGE_FORMAT_DEPTH32F_STENCIL8:
				break;
			case ImageModule::IMAGE_FORMAT_SRGB8:
				break;
			case ImageModule::IMAGE_FORMAT_SRGB8_ALPHA8:
                return GL_SRGB8_ALPHA8;
			case ImageModule::IMAGE_FORMAT_SLUMINANCE8:
				break;
			case ImageModule::IMAGE_FORMAT_SLUMINANCE8_ALPHA8:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_S3TC_DXT1:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:
				break;
			case ImageModule::IMAGE_FORMAT_RGB9_E5:
				break;
			case ImageModule::IMAGE_FORMAT_R11F_G11F_B10F:
                return GL_R11F_G11F_B10F;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_LATC1:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_LATC1:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_LUMINANCE_ALPHA_LATC2:
				break;
			case ImageModule::IMAGE_FORMAT_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA32UI:
				break;
			case ImageModule::IMAGE_FORMAT_RGB32UI:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA32UI:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY32UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE32UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32UI:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA16UI:
				break;
            case ImageModule::IMAGE_FORMAT_RGBA16F:
                return GL_RGBA16F;
            case ImageModule::IMAGE_FORMAT_RGBA32F:
                return GL_RGBA32F;
			case ImageModule::IMAGE_FORMAT_RGB16UI:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA16UI:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY16UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE16UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16UI:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA8UI:
				break;
			case ImageModule::IMAGE_FORMAT_RGB8UI:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA8UI:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY8UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE8UI:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8UI:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA32I:
				break;
			case ImageModule::IMAGE_FORMAT_RGB32I:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA32I:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY32I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE32I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA32I:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA16I:
				break;
			case ImageModule::IMAGE_FORMAT_RGB16I:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA16I:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY16I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE16I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA16I:
				break;
			case ImageModule::IMAGE_FORMAT_RGBA8I:
				break;
			case ImageModule::IMAGE_FORMAT_RGB8I:
				break;
			case ImageModule::IMAGE_FORMAT_ALPHA8I:
				break;
			case ImageModule::IMAGE_FORMAT_INTENSITY8I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE8I:
				break;
			case ImageModule::IMAGE_FORMAT_LUMINANCE_ALPHA8I:
				break;
			case ImageModule::IMAGE_FORMAT_RG32UI:
				break;
			case ImageModule::IMAGE_FORMAT_R32UI:
				break;
			case ImageModule::IMAGE_FORMAT_RG16UI:
				break;
			case ImageModule::IMAGE_FORMAT_R16UI:
				break;
			case ImageModule::IMAGE_FORMAT_RG8UI:
				break;
			case ImageModule::IMAGE_FORMAT_R8UI:
				break;
			case ImageModule::IMAGE_FORMAT_RG32I:
				break;
			case ImageModule::IMAGE_FORMAT_R32I:
				break;
			case ImageModule::IMAGE_FORMAT_RG16I:
				break;
			case ImageModule::IMAGE_FORMAT_R16I:
				break;
			case ImageModule::IMAGE_FORMAT_RG8I:
				break;
			case ImageModule::IMAGE_FORMAT_R8I:
				break;
			case ImageModule::IMAGE_FORMAT_RG8:
				break;
			case ImageModule::IMAGE_FORMAT_R8:
				break;
			case ImageModule::IMAGE_FORMAT_RG16:
				break;
			case ImageModule::IMAGE_FORMAT_R16:
				break;
			case ImageModule::IMAGE_FORMAT_RG16F:
				break;
			case ImageModule::IMAGE_FORMAT_R16F:
				break;
			case ImageModule::IMAGE_FORMAT_RG32F:
				break;
			case ImageModule::IMAGE_FORMAT_R32F:
				return GL_R32F;
			case ImageModule::IMAGE_FORMAT_BGRA:
				return GL_BGRA;
			case ImageModule::IMAGE_FORMAT_BGR:
				return GL_BGR;
			case ImageModule::IMAGE_FORMAT_ALPHA:
				return GL_ALPHA;
			case ImageModule::IMAGE_FORMAT_RGBA:
				return GL_RGBA;
			case ImageModule::IMAGE_FORMAT_RGB:
				return GL_RGB;
			case ImageModule::IMAGE_FORMAT_RED:
				return GL_RED;
			case ImageModule::IMAGE_FORMAT_BAD:
				break;
			default:
				break;
			}
			return -1;
		}
	}
}
