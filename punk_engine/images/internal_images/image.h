#ifndef _H_PUNK_IMAGES_IMAGE
#define _H_PUNK_IMAGES_IMAGE

#include "../config.h"
#include "../../system/resource.h"

namespace ImageModule
{
	class MODULE_IMAGE Image
	{
	public:
		typedef unsigned char Component;

		Image();
		Image(const Image& image);
		Image& operator = (const Image& image);
		void Save(System::Buffer& buffer) const;
		void Load(System::Buffer& buffer);				
		const System::Descriptor& GetDescriptor() const;		
		unsigned GetSizeInBytes() const;
		unsigned GetComponentsCount() const;
		unsigned GetWidth() const;
		unsigned GetHeight() const;
		void SetSize(unsigned width, unsigned height);
		void SetSubImage(unsigned x, unsigned y, const Image& image);
		const Component* GetPixelComponent(unsigned x, unsigned y, unsigned component) const;
		Component* GetPixelComponent(unsigned x, unsigned y, unsigned component);
		const Component* GetData() const;
		Component* GetData();
		
		struct ImageImpl;
		std::auto_ptr<ImageImpl> impl_image;		
	};
}

#endif