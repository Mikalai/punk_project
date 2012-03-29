#include "error.h"

namespace ImageModule
{
	ImageError::ImageError() : std::exception(), m_w_what(0)
	{
	}

	ImageError::ImageError(const wchar_t* message) : std::exception(), m_w_what(message) {}

	ImageError::~ImageError()
	{
	}

	const wchar_t * ImageError::w_what() const
	{
		return m_w_what.Data();
	}
}