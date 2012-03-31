#ifndef _H_PUNK_IMAGE_MODULE_GRAY_IMAGE_RESOURCE
#define _H_PUNK_IMAGE_MODULE_GRAY_IMAGE_RESOURCE

#include "../../system/resource.h"
#include "../internal_images/rgba_image.h"
#include "../config.h"

namespace ImageModule
{
	class MODULE_IMAGE GrayImageResource : public System::Resource, public RGBAImage
	{
		using System::Resource::Load;
		using System::Resource::Save;

		GrayImageResource(const GrayImageResource&);
		GrayImageResource& operator = (const GrayImageResource&);

	public:

		GrayImageResource(const System::Descriptor& desc);
		virtual void Save(System::Buffer& buffer) const;
		virtual void Load(System::Buffer& buffer);				
		virtual std::auto_ptr<System::Resource> Clone() const;
		virtual const System::Descriptor& GetDescriptor() const;
		virtual	void SetDescriptor(const System::Descriptor& desc);
		virtual ~GrayImageResource();

	};
}

#endif