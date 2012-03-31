#include "rgba_image_resource.h"
#include "../internal_images/image_impl.h"
#include "../../system/handle.h"

namespace ImageModule
{
	RGBAImageResource::RGBAImageResource(const System::Descriptor& desc)
		: RGBAImage()
	{
		impl_image->m_descriptor = desc;
	}

	RGBAImageResource::RGBAImageResource(const RGBAImageResource& image)
		: RGBAImage(image)
	{}

	void RGBAImageResource::Save(System::Buffer& buffer) const
	{
		RGBAImage::Save(buffer);
	}

	void RGBAImageResource::Load(System::Buffer& buffer)
	{
		RGBAImage::Load(buffer);
	}

	std::auto_ptr<System::Resource> RGBAImageResource::Clone() const
	{
		return std::auto_ptr<System::Resource>(new RGBAImageResource(*this));
	}

	const System::Descriptor& RGBAImageResource::GetDescriptor() const
	{
		return RGBAImage::GetDescriptor();
	}

	void RGBAImageResource::SetDescriptor(const System::Descriptor& desc)
	{
		impl_image->m_descriptor = desc;
	}

	RGBAImageResource::~RGBAImageResource() {}
}