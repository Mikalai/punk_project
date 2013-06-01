#ifndef _H_PUNK_MATH_ERROR
#define _H_PUNK_MATH_ERROR

#include <exception>
#include "../config.h"

namespace Math
{
	//
	//	math exceptions
	//

	class PUNK_ENGINE_PUBLIC MathError
	{
	public:
		MathError();
		MathError(const wchar_t* message);
		~MathError();

		virtual const wchar_t* w_what() const;
	private:
		const wchar_t* m_w_what;
	};

	class MathTestFailed : public MathError {};
	class MathIndexOutOfRange : public MathError {};
	class MathDevisionByZero : public MathError {};

}

#endif 