#ifndef _H_PUNK_IMAGE_MODULE_RGB_RESOURCE
#define _H_PUNK_IMAGE_MODULE_RGB_RESOURCE

#include "../../system/resource.h"
#include "../internal_images/rgb_image.h"
#include "../config.h"

namespace ImageModule
{
	class MODULE_IMAGE RGBImageResource : public System::Resource, public RGBImage
	{
		using System::Resource::Load;
		using System::Resource::Save;

		RGBImageResource(const RGBImageResource&);
		RGBImageResource& operator = (const RGBImageResource&);

	public:

		RGBImageResource(const System::Descriptor& desc);
		virtual void Save(System::Buffer& buffer) const;
		virtual void Load(System::Buffer& buffer);				
		virtual std::auto_ptr<System::Resource> Clone() const;
		virtual const System::Descriptor& GetDescriptor() const;
		virtual	void SetDescriptor(const System::Descriptor& desc);
		virtual ~RGBImageResource();

	};
}

#endif