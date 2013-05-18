#ifndef _H_PUNK_GPU_TEXTURE_2D
#define _H_PUNK_GPU_TEXTURE_2D

#include <iosfwd>
#include "../../system/object.h"
#include "../gpu_config.h"
#include "../../images/formats.h"

namespace System { class string; }

namespace ImageModule
{
	class Image;
}

namespace GPU
{
    class VideoDriver;

	class PUNK_ENGINE Texture2D final
	{
	public:		
		virtual ~Texture2D();

        void Bind(int slot = 0) const;
		void Unbind() const;			
		bool CopyFromCPU(int x, int y, int width, int height, const void* data);
		void Resize(int width, int height);
		void Fill(unsigned char data);
		int GetHeight() const;
		int GetWidth() const;
		unsigned GetCode() const;		
		void* Map();
		void Unmap(void* data);

		void SetSourceFile(const System::string& filename);
		const System::string& GetSourceFile() const;
		void SetIndex(int index);
		int GetIndex() const;

		void Init();
		void Clear();

		bool IsValid() const;

		struct Texture2DImpl;
		Texture2DImpl* impl;

    private:
        Texture2D(VideoDriver* driver);
        Texture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, VideoDriver* driver);

        Texture2D(const Texture2D& texture) = delete;
        Texture2D& operator = (const Texture2D& texture) = delete;

        friend class VideoDriver;
	};
}

#endif	//	_H_PUNK_GPU_TEXTURE_2D
