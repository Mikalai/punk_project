#ifndef _H_PUNK_IMAGE_ERROR
#define _H_PUNK_IMAGE_ERROR

#include <exception>
#include "config.h"
#include "../system/string.h"

namespace ImageModule
{
	class MODULE_IMAGE ImageError : public std::exception
	{
	public:
		ImageError();
		ImageError(const wchar_t* message);
		~ImageError();

		virtual const wchar_t* w_what() const;
	private:
		const System::string m_w_what;
	};
}

#endif