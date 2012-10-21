#ifndef _H_PUNK_PNG_FILE
#define _H_PUNK_PNG_FILE

#include "image_file.h"

namespace ImageModule
{
	class PUNK_ENGINE PngFile : public ImageFile
	{

	public:
		PngFile();

		virtual bool Load(const wchar_t* file);
		virtual bool Save(const wchar_t* file);

	};
}

#endif