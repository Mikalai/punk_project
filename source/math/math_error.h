#ifndef _H_PUNK_MATH_ERROR
#define _H_PUNK_MATH_ERROR

#include <exception>
#include "../system/errors/exceptions.h"
#include "../config.h"

namespace Math
{
    //
    //	math exceptions
    //

    class PUNK_ENGINE_API MathError : public System::PunkException
    {
    };

    class MathTestFailed : public MathError
    {
    };

    class MathIndexOutOfRange : public MathError {};
    class MathDevisionByZero : public MathError {};

}

#endif
