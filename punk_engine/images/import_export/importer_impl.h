#ifndef _H_PUNK_IMAGE_MODULE_IMPORTER_IMPLEMENTATION
#define _H_PUNK_IMAGE_MODULE_IMPORTER_IMPLEMENTATION

#include "importer.h"
#include "../internal_images/image_impl.h"
#include "../formats.h"

namespace ImageModule
{
	struct Importer::ImporterImpl : public Image
	{
		ImageFormat m_format;
		ImporterImpl()
			: Image()
			, m_format(IMAGE_FORMAT_BAD)
		{}

		ImporterImpl(const ImporterImpl& impl)
			: Image(impl)
			, m_format(impl.m_format)
		{}
	};
}

#endif