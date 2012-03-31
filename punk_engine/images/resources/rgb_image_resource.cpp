#include "rgb_image_resource.h"
#include "../internal_images/image_impl.h"
#include "../../system/handle.h"

namespace ImageModule
{
	RGBImageResource::RGBImageResource(const System::Descriptor& desc)
		: RGBImage()
	{
		impl_image->m_descriptor = desc;
	}

	RGBImageResource::RGBImageResource(const RGBImageResource& image)
		: RGBImage(image)
	{}

	void RGBImageResource::Save(System::Buffer& buffer) const
	{
		RGBImage::Save(buffer);
	}

	void RGBImageResource::Load(System::Buffer& buffer)
	{
		RGBImage::Load(buffer);
	}

	std::auto_ptr<System::Resource> RGBImageResource::Clone() const
	{
		return std::auto_ptr<System::Resource>(new RGBImageResource(*this));
	}

	const System::Descriptor& RGBImageResource::GetDescriptor() const
	{
		return RGBImage::GetDescriptor();
	}

	void RGBImageResource::SetDescriptor(const System::Descriptor& desc)
	{
		impl_image->m_descriptor = desc;
	}

	RGBImageResource::~RGBImageResource() {}
}