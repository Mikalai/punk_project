/*
File: Texture2D.h
Author: Abramau Mikalaj
Description: Contains a Texture2D class
*/

#ifndef _H_PUNK_TEXTURE_2D
#define _H_PUNK_TEXTURE_2D

#include <iosfwd>
#include "../../../config.h"
#include "../../../system/resource_manager.h"
#include "../../../system/object.h"
#include "../../../system/buffer.h"
#include "../../../images/formats.h"

namespace ImageModule
{
	class Image;
}

namespace GPU
{
	namespace OpenGL
	{
		struct Texture2DImpl;

		class PUNK_ENGINE Texture2D : public System::Object
		{
		protected:
			std::auto_ptr<Texture2DImpl> impl_texture_2d;
		public:
			Texture2D();
			explicit Texture2D(const ImageModule::Image& image);
			Texture2D(const Texture2D& texture);
			Texture2D& operator = (const Texture2D& texture);
			~Texture2D();
			void Bind() const;
			void Unbind() const;	
			bool Create(int width, int height, ImageModule::ImageFormat format, const void* data);
			bool CopyFromCPU(int x, int y, int width, int height, const void* data);
			void Resize(int width, int height);
			void Fill(unsigned char data);
			int GetHeight() const;
			int GetWidth() const;
			unsigned GetCode() const;
			void Create(const ImageModule::Image& image);
			void* Map();
			void Unmap(void* data);

			virtual bool Save(std::ostream& stream) const;
			virtual bool Load(std::istream& stream);		

			void SetSourceFile(const System::string& filename);
			const System::string& GetSourceFile() const;
			void SetIndex(int index);
			int GetIndex() const;

			void Init();
			void Clear();

			static Texture2D* CreateFromFile(const System::string& path);
			static Texture2D* CreateFromStream(std::istream& stream);
		};

		typedef Texture2D* Texture2DRef;
	}

}
//REGISTER_MANAGER(L"resource.textures", L"*.texture", System::Environment::Instance()->GetTextureFolder(), System::ObjectType::TEXTURE_2D, OpenGL, Texture2D, return, return);

#endif	// _H_Texture2D
