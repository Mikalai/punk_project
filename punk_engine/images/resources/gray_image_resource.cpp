#include "gray_image_resource.h"
#include "../internal_images/image_impl.h"
#include "../../system/handle.h"

namespace ImageModule
{
	GrayImageResource::GrayImageResource(const System::Descriptor& desc)
		: RGBAImage()
	{
		impl_image->m_descriptor = desc;
	}

	GrayImageResource::GrayImageResource(const GrayImageResource& image)
		: RGBAImage(image)
	{}

	void GrayImageResource::Save(System::Buffer& buffer) const
	{
		RGBAImage::Save(buffer);
	}

	void GrayImageResource::Load(System::Buffer& buffer)
	{
		RGBAImage::Load(buffer);
	}

	std::auto_ptr<System::Resource> GrayImageResource::Clone() const
	{
		return std::auto_ptr<System::Resource>(new GrayImageResource(*this));
	}

	const System::Descriptor& GrayImageResource::GetDescriptor() const
	{
		return RGBAImage::GetDescriptor();
	}

	void GrayImageResource::SetDescriptor(const System::Descriptor& desc)
	{
		impl_image->m_descriptor = desc;
	}

	GrayImageResource::~GrayImageResource() {}
}