#ifndef _H_PUNK_PNG_FILE
#define _H_PUNK_PNG_FILE

#include "image_file.h"

namespace Image
{
	class LIB_IMAGE PngFile : public ImageFile
	{

	public:
		PngFile();

		virtual void Load(const wchar_t* file);
		virtual void Save(const wchar_t* file);

	};
}

#endif