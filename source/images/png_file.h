#ifndef _H_PUNK_PNG_FILE
#define _H_PUNK_PNG_FILE

#include "image_file.h"

namespace ImageModule
{
	class PUNK_ENGINE_PUBLIC PngFile : public ImageFile
	{

	public:
		PngFile();

		virtual bool Save(const wchar_t* file) const;
		virtual bool Load(const wchar_t* file);		

	};
}

#endif