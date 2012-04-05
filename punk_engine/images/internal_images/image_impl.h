#ifndef _H_PUNK_IMAGE_IMAGE_MODULE_IMAGE_IMPL
#define _H_PUNK_IMAGE_IMAGE_MODULE_IMAGE_IMPL

#include "../error.h"
#include "../formats.h"
#include "component.h"
#include "../../system/buffer.h"
#include "../../system/handle.h"

namespace ImageModule
{
	struct ImageImpl
	{
		unsigned m_width;
		unsigned m_height;
		unsigned m_components;
		unsigned m_size;	
		unsigned m_bit_depth;
		ImageFormat m_format;
		std::vector<Component> m_data;
		System::Descriptor m_descriptor;

		ImageImpl()
			: m_width(0)
			, m_height(0)
			, m_components(0)
			, m_size(0)
			, m_data()
			, m_descriptor()
			, m_bit_depth(0)
			, m_format(IMAGE_FORMAT_BAD)
		{}

		ImageImpl(const ImageImpl& impl)
			: m_width(impl.m_width)
			, m_height(impl.m_height)
			, m_components(impl.m_components)
			, m_size(impl.m_size)
			, m_data(impl.m_data.begin(), impl.m_data.end())
			, m_descriptor(impl.m_descriptor)
			, m_bit_depth(impl.m_bit_depth)
			, m_format(impl.m_format)
		{}

		ImageImpl(int width, int height, int components)
			: m_width(width)
			, m_height(height)
			, m_components(components)
			, m_size(m_width*m_height*m_components*sizeof(Component))
			, m_data(m_size)
			, m_bit_depth(0)
			, m_format(IMAGE_FORMAT_BAD)
		{
			std::fill(m_data.begin(), m_data.end(), 0);
		}

		~ImageImpl()
		{}

		void Create(int w, int h, int c)
		{
			m_width = w;
			m_height = h;
			m_components = c;
			m_size = m_width*m_height*m_components*sizeof(Component);
			m_data.resize(m_size);
			//m_bit_depth = 0;
			//m_format = IMAGE_FORMAT_BAD;
			std::fill(m_data.begin(), m_data.end(), 0);
		}

		void Clear()
		{}		

		void PutLine(int y, int width_in_pixel, int components_per_pixel, Component* data)
		{
			if (!m_data.empty())
				throw ImageError(L"Data is not allocated");
			if (width_in_pixel != m_width)
				throw ImageError(L"Impossible to copy line due to different width");
			if (components_per_pixel != m_components)
				throw ImageError(L"Line3D components per pixel count differs from image");

			std::copy(data, data + width_in_pixel*components_per_pixel, m_data.begin() + y*m_width*m_components);
		}

		void Save(System::Buffer& buffer) const
		{
			m_descriptor.Save(buffer);
			buffer.WriteSigned32(m_width);
			buffer.WriteSigned32(m_height);
			buffer.WriteSigned32(m_components);
			buffer.WriteBuffer(&m_data[0], m_size);
		}

		void Load(System::Buffer& buffer)
		{
			m_descriptor.Load(buffer);
			m_width = buffer.ReadSigned32();
			m_height = buffer.ReadSigned32();
			m_components = buffer.ReadSigned32();
			m_size = m_width*m_height*m_components*sizeof(Component);
			m_data.resize(m_size);
			buffer.ReadBuffer(&m_data[0], m_size);
		}

		const Component* At(unsigned x, unsigned y, unsigned component) const
		{
			return &m_data[y*m_width*m_components+x*m_components + component];
		}

		Component* At(unsigned x, unsigned y, unsigned component)
		{
			return const_cast<Component*>(static_cast<const ImageImpl&>(*this).At(x, y, component));
		}

		void SetSubImage(unsigned x, unsigned y, const ImageImpl& impl)
		{
			if (m_components != impl.m_components)
				throw ImageError(L"Can't set sub image due to different components number");

			for (unsigned y_dst = y, y_org = 0; y_dst < m_height && y_org < impl.m_height; ++y_dst, ++y_org)
			{
				for (unsigned x_dst = x, x_org = 0; x_dst < m_width && x_org < impl.m_width; ++x_dst, ++x_org)
				{
					for (unsigned c = 0; c < m_components; ++c)
					{
						*At(x_dst, y_dst, c) = *impl.At(x_org, y_org, c);
					}
				}
			}
		}
	};

}

#endif