#ifndef _H_PUNK_IMAGES_IMAGE
#define _H_PUNK_IMAGES_IMAGE

#include <memory>
#include "../config.h"
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

	class MODULE_IMAGE Image
	{		
	public:
		
		Image();
		Image(const Image& image);
		Image& operator = (const Image& image);
		~Image();

		void Save(System::Buffer& buffer) const;
		void Load(System::Buffer& buffer);				
		const System::Descriptor& GetDescriptor() const;		
		unsigned GetSizeInBytes() const;
		unsigned GetComponentsCount() const;
		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetBitDepth() const;
		void SetSize(unsigned width, unsigned height);
		void SetSubImage(unsigned x, unsigned y, const Image& image);
		const Component* GetPixelComponent(unsigned x, unsigned y, unsigned component) const;
		Component* GetPixelComponent(unsigned x, unsigned y, unsigned component);
		const Component* GetData() const;
		Component* GetData();
		ImageFormat GetImageFormat() const;
		std::auto_ptr<ImageImpl> impl_image;		
	};
}

#endif