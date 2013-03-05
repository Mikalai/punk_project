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

	Texture2D::Texture2D()
		: impl(new Texture2DImpl())
	{}

	Texture2D::Texture2D(const ImageModule::Image& image) 
		: impl(new Texture2DImpl(image))
	{}

	Texture2D::Texture2D(const Texture2D& texture)
		: impl(new Texture2DImpl(*texture.impl))
	{}

	Texture2D& Texture2D::operator = (const Texture2D& t)
	{
		Texture2D temp(t);
		std::swap(impl, temp.impl);
		return *this;
	}

	void Texture2D::Bind() const 
	{
		glBindTexture(GL_TEXTURE_2D, impl->m_texture_id);
		CHECK_GL_ERROR(L"Unable to bind texture");
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		CHECK_GL_ERROR(L"Unable to unbind texture");
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

	bool Texture2D::Create(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
	{
		if (impl)
			delete impl;
		impl = new Texture2DImpl;		
		return impl->Create(width, height, ImageFormatToOpenGL(format), data, use_mipmaps);
	}

	void Texture2D::Create(const ImageModule::Image& image, bool use_mipmaps)
	{
		if (impl)
			delete impl;
		impl = new Texture2DImpl;
		impl->CreateFromImage(image, false);
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

	void Texture2D::SetSourceFile(const System::string& filename)
	{
		impl->SetSourceFile(filename);
	}

	const System::string& Texture2D::GetSourceFile() const
	{
		return impl->GetSourceFile();
	}

	void Texture2D::SetIndex(int index)
	{
		impl->SetIndex(index);
	}

	int Texture2D::GetIndex() const
	{
		return impl->GetIndex();
	}

	void Texture2D::Init()
	{
		impl->Init();
	}

	void Texture2D::Clear()
	{
		impl->Clear();
	}

	bool Texture2D::Load(std::istream& stream)
	{
		ImageModule::Image image;
		image.Load(stream);
		Create(image, false);
		return true;
	}

	bool Texture2D::Save(std::ostream& stream) const
	{	
		return false;
	}

	Texture2D* Texture2D::CreateFromFile(const System::string& path, bool use_mip_maps)
	{		
		ImageModule::Importer importer;
		std::auto_ptr<ImageModule::Image> image(importer.LoadAnyImage(path));

		if (image.get())
		{
			std::unique_ptr<Texture2D> result(new Texture2D);//(*image));		
			result->Create(*image, use_mip_maps);
			return result.release();
		}
		else
			throw OpenGLException(L"Can't create texture from " + path);
	}

	Texture2D* Texture2D::CreateFromStream(std::istream& stream, bool use_mip_maps)
	{		
		std::unique_ptr<Texture2D> result(new Texture2D);//(*image));		
		result->Load(stream);
		return result.release();
	}
}
