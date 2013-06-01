/*
File: Texture2D.cpp
Author: Abramau Mikalaj
Description: Texture2D implementation
*/

#include <istream>
#include <ostream>
#include "../../common/texture2d.h"
#include "texture2d_pbo_impl.h"
#include "internal_formats.h"
#include "../../../system/buffer.h"


namespace GPU
{
	using namespace OpenGL;

    Texture2D::Texture2D(VideoDriver* driver)
        : impl(new Texture2DImpl(driver))
	{}


    Texture2D::Texture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, VideoDriver* driver)
        : impl(new Texture2DImpl(width, height, internal_format, format, data, use_mipmaps, driver))
    {}

    void Texture2D::Bind(int slot) const
	{
        impl->Bind(slot);
	}

	void Texture2D::Unbind() const
	{
        impl->Unbind();
	}

	Texture2D::~Texture2D()
	{
		delete impl;
		impl = nullptr;
	}

	bool Texture2D::CopyFromCPU(int x, int y, int width, int height, const void* data)
	{
		return impl->CopyFromCPU(x, y, width, height, data);
	}

	bool Texture2D::IsValid() const
	{
		return impl->m_texture_id != 0;
	}

	void Texture2D::Resize(int width, int height)
	{
		impl->Resize(width, height);
	}

	void Texture2D::Fill(unsigned char byte)
	{
		impl->Fill(byte);
	}

	int Texture2D::GetWidth() const
	{
		return impl->m_width;
	}

	int Texture2D::GetHeight() const
	{
		return impl->m_height;
	}

	unsigned Texture2D::GetCode() const
	{
		return impl->m_texture_id;
	}

	void* Texture2D::Map()
	{
		return impl->Map();
	}

	void Texture2D::Unmap(void* data)
	{
		impl->Unmap(data);
	}

	void Texture2D::Init()
	{
		impl->Init();
	}

	void Texture2D::Clear()
	{
		impl->Clear();
	}
}
