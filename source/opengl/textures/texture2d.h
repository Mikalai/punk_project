/*
File: Texture2D.h
Author: Abramau Mikalai
Description: Contains a Texture2D class
*/

#ifndef _H_PUNK_TEXTURE_2D
#define _H_PUNK_TEXTURE_2D

#include <iosfwd>
#include "../../config.h"
#include "../../system/resource.h"
#include "../../system/permanent_data.h"
#include "../../system/buffer.h"
#include "../../images/formats.h"

namespace ImageModule
{
	class Image;
}

namespace OpenGL
{
	struct Texture2DImpl;

	class PUNK_ENGINE Texture2D : public System::PermanentData
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
		void Create(int width, int height, int format, const unsigned char* data);
		void CopyFromCPU(int x, int y, int width, int height, int format, const unsigned char* data);
		void Resize(int width, int height);
		void Fill(unsigned char data);
		int GetHeight() const;
		int GetWidth() const;
		unsigned GetCode() const;
		void Create(const ImageModule::Image& image);

		void Load(std::istream& stream);
		void Save(std::ostream& stream);
		void SetSourceFile(const System::string& filename);
		const System::string& GetSourceFile() const;
		void SetIndex(int index);
		int GetIndex() const;

		void Init();
		void Clear();
	};

	typedef Texture2D* Texture2DRef;
}

#endif	// _H_Texture2D
