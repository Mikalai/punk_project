/*
File: Texture2D.cpp
Author: Abramau Mikalaj
Description: Texture2D implementation
*/

#include <istream>
#include <ostream>
#include "texture2d.h"
#include "texture2d_pbo_impl.h"
#include "internal_formats.h"

//IMPLEMENT_MANAGER(L"resource.textures", L"*.texture", System::Environment::Instance()->GetTextureFolder(), System::ObjectType::TEXTURE_2D, OpenGL, Texture2D);

namespace GPU
{
	namespace OpenGL
	{
		Texture2D::Texture2D()
			: impl_texture_2d(new Texture2DImpl())
		{}

		Texture2D::Texture2D(const ImageModule::Image& image) 
			: impl_texture_2d(new Texture2DImpl(image))
		{}

		Texture2D::Texture2D(const Texture2D& texture)
			: impl_texture_2d(new Texture2DImpl(*texture.impl_texture_2d))
		{}

		Texture2D& Texture2D::operator = (const Texture2D& t)
		{
			Texture2D temp(t);
			std::swap(impl_texture_2d, temp.impl_texture_2d);
			return *this;
		}

		void Texture2D::Bind() const 
		{
			glBindTexture(GL_TEXTURE_2D, impl_texture_2d->m_texture_id);
			CHECK_GL_ERROR(L"Unable to bind texture");
		}

		void Texture2D::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			CHECK_GL_ERROR(L"Unable to unbind texture");
		}

		Texture2D::~Texture2D()
		{
			impl_texture_2d.reset(0);
		}

		bool Texture2D::CopyFromCPU(int x, int y, int width, int height, const void* data)
		{
			return impl_texture_2d->CopyFromCPU(x, y, width, height, data);
		}

		bool Texture2D::IsValid() const
		{
			return impl_texture_2d->m_texture_id != 0;
		}

		void Texture2D::Resize(int width, int height)
		{
			impl_texture_2d->Resize(width, height);
		}

		bool Texture2D::Create(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps)
		{
			impl_texture_2d.reset(new Texture2DImpl);		
			return impl_texture_2d->Create(width, height, ImageFormatToOpenGL(format), data, use_mipmaps);
		}

		void Texture2D::Create(const ImageModule::Image& image, bool use_mipmaps)
		{
			impl_texture_2d.reset(new Texture2DImpl);
			impl_texture_2d->CreateFromImage(image, false);
		}

		void Texture2D::Fill(unsigned char byte)
		{
			impl_texture_2d->Fill(byte);
		}

		int Texture2D::GetWidth() const
		{
			return impl_texture_2d->m_width;
		}

		int Texture2D::GetHeight() const
		{
			return impl_texture_2d->m_height;
		}

		unsigned Texture2D::GetCode() const
		{
			return impl_texture_2d->m_texture_id;
		}

		void* Texture2D::Map()
		{
			return impl_texture_2d->Map();
		}

		void Texture2D::Unmap(void* data)
		{
			impl_texture_2d->Unmap(data);
		}

		void Texture2D::SetSourceFile(const System::string& filename)
		{
			impl_texture_2d->SetSourceFile(filename);
		}

		const System::string& Texture2D::GetSourceFile() const
		{
			return impl_texture_2d->GetSourceFile();
		}

		void Texture2D::SetIndex(int index)
		{
			impl_texture_2d->SetIndex(index);
		}

		int Texture2D::GetIndex() const
		{
			return impl_texture_2d->GetIndex();
		}

		void Texture2D::Init()
		{
			impl_texture_2d->Init();
		}

		void Texture2D::Clear()
		{
			impl_texture_2d->Clear();
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

		System::Proxy<Texture2D> Texture2D::CreateFromFile(const System::string& path)
		{		
			ImageModule::Importer importer;
			std::auto_ptr<ImageModule::Image> image(importer.LoadAnyImage(path));

			if (image.get())
			{
				System::Proxy<Texture2D> result(new Texture2D);//(*image));		
				result->Create(*image, false);
				return result;
			}
			else
				throw OpenGLException(L"Can't create texture from " + path);
		}

		System::Proxy<Texture2D> Texture2D::CreateFromStream(std::istream& stream)
		{		
			System::Proxy<Texture2D> result(new Texture2D);//(*image));		
			result->Load(stream);
			return result;
		}
	}
}
