#ifndef _H_PUNK_IMAGE_MODULE_RGBA_IMAGE_RESOURCE
#define _H_PUNK_IMAGE_MODULE_RGBA_IMAGE_RESOURCE

#include "../../system/resource.h"
#include "../internal_images/rgba_image.h"
#include "../config.h"

namespace ImageModule
{
	class MODULE_IMAGE RGBAImageResource : public System::Resource, public RGBAImage
	{
		using System::Resource::Load;
		using System::Resource::Save;

		RGBAImageResource(const RGBAImageResource&);
		RGBAImageResource& operator = (const RGBAImageResource&);

	public:

		RGBAImageResource(const System::Descriptor& desc);
		virtual void Save(System::Buffer& buffer) const;
		virtual void Load(System::Buffer& buffer);				
		virtual std::auto_ptr<System::Resource> Clone() const;
		virtual const System::Descriptor& GetDescriptor() const;
		virtual	void SetDescriptor(const System::Descriptor& desc);
		virtual ~RGBAImageResource();

	};
}

#endif