#ifndef _H_PUNK_IMAGE_ERROR
#define _H_PUNK_IMAGE_ERROR

#include <exception>
#include "config.h"

namespace Image
{
	class LIB_IMAGE ImageError : public std::exception
	{
	public:
		ImageError();
		ImageError(const wchar_t* message);
		~ImageError();

		virtual const wchar_t* w_what() const;
	private:
		const wchar_t* m_w_what;
	};
}

#endif