#ifndef _H_PUNK_IMAGES_IMAGE
#define _H_PUNK_IMAGES_IMAGE

#include <memory>
#include <iosfwd>
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

		void Save(std::ostream& stream) const;
		void Load(std::istream& stream);				
		const System::Descriptor& GetDescriptor() const;		
		unsigned GetSizeInBytes() const;
		unsigned GetComponentsCount() const;
		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetBitDepth() const;
		void Create(int width, int height, int channels);
		void SetFormat(int format);
		void SetNumChannels(int channels);
		void SetDepth(int bpp);
		void SetSize(unsigned width, unsigned height);
		void SetSubImage(unsigned x, unsigned y, const Image& image);
		const Component* GetPixelComponent(unsigned x, unsigned y, unsigned component) const;
		Component* GetPixelComponent(unsigned x, unsigned y, unsigned component);
		void SetPixelComponent(unsigned x, unsigned y, unsigned component, Component value);
		const Component* GetData() const;
		Component* GetData();
		ImageFormat GetImageFormat() const;
		std::auto_ptr<ImageImpl> impl_image;		
	};
}

#endif