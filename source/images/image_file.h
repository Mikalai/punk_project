/*
	File: ImageFile.h
	Author: Mikalaj Abramau
	Desc: Class that represents an image file
*/

#ifndef _H_PUNK_IMAGE_FILE
#define _H_PUNK_IMAGE_FILE

#include "../config.h"
#include "formats.h"
#include "../system/buffer.h"

namespace ImageModule
{
	class PUNK_ENGINE ImageFile
	{
	protected:
		struct Rep
		{
			unsigned char* m_data;
			unsigned m_width;
			unsigned m_height;
			unsigned m_depth;
			//unsigned m_channels;
			unsigned m_size;
			unsigned m_bpp;
			ImageFormat m_format;
			unsigned m_used_count;

			Rep();
			Rep(const Rep& rep);
			~Rep();
			void SetSize(int width, int height);
			void SetSize(unsigned size);
			Rep* GetOwnCopy();
		};

		Rep* m_rep;

	public:
		
		ImageFile();
		ImageFile(const ImageFile& file);
		ImageFile& operator = (const ImageFile& file);

		virtual ~ImageFile();

		virtual bool Save(const wchar_t* file) const { return false; }
		virtual bool Load(const wchar_t* file) { return false; }		

		virtual void Store(System::Buffer& buffer);
		virtual void Restore(System::Buffer& buffer);

		unsigned GetWidth() const;
		unsigned GetHeight() const;
		unsigned GetChannels() const;

		void SetSize(unsigned width, unsigned height);
		void SetPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void SetFormat(ImageFormat format);
		ImageFormat GetFormat() const;
		const unsigned char* GetPixel(unsigned x, unsigned y) const;

		void* Lock();
		const void* Lock() const;
		void Unlock(void* p);
		void Unlock(const void* p) const;

		
	};
}

#endif
