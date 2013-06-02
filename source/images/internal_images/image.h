#ifndef _H_PUNK_IMAGES_IMAGE
#define _H_PUNK_IMAGES_IMAGE

#include <memory>
#include <iosfwd>
#include "../../config.h"
#include "../formats.h"
#include "component.h"

namespace System
{
	class Buffer;
	class Descriptor;
}

namespace ImageModule
{
	struct ImageImpl;

	class PUNK_ENGINE_API Image
	{
	public:

		Image();
        Image(size_t width, size_t height, int channels, ComponentType type, ImageFormat format);
		Image(const Image& image);
		Image& operator = (const Image& image);
		~Image();

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
		unsigned GetSizeInBytes() const;
		unsigned GetComponentsCount() const;
		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetBitDepth() const;
        ComponentType GetComponentType() const;
        void Create(int width, int height, int channels, ComponentType type, ImageFormat format);
        void SetSize(unsigned width, unsigned height);
		void SetSubImage(unsigned x, unsigned y, const Image& image);
        const void* GetPixelComponent(unsigned x, unsigned y, unsigned component) const;
        void* GetPixelComponent(unsigned x, unsigned y, unsigned component);
        void SetPixelComponent(unsigned x, unsigned y, unsigned component, const void* value);
        const void* GetData() const;
        void* GetData();
		ImageFormat GetImageFormat() const;
		std::unique_ptr<ImageImpl> impl_image;

        const Image ToAlpha() const;
        const Image ToRGB() const;
        const Image ToRGBA() const;

	};
}

#endif
