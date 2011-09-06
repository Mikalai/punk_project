#ifndef _H_MATH_FUNCTIONS
#define _H_MATH_FUNCTIONS

namespace Math
{
#undef min
#undef max

    //
    //	trigonometric functions
    //

    extern float radians(float degrees);
    extern float degrees(float radians);
    extern float sin(float angle);
    extern float cos(float angle);
    extern float tan(float angle);
    extern float asin(float x);
    extern float acos(float x);
    extern float atan(float x, float y);
    extern float atan(float x_over_y);
    extern float sinh(float x);
    extern float cosh(float x);
    extern float tanh(float x);
    extern float asinh(float x);
    extern float acosh(float x);
    extern float atanh(float x);

    //
    //	exponential functions
    //
    extern float pow(float x, float y);
    extern float exp(float x);
    extern float log(float x);
    extern float exp2(float x);
    extern float log2(float x);
    extern float sqrt(float x);
    extern float inversesqrt(float x);

    //
    //	common functions
    //
    extern float abs(float x);
    extern float sign(float x);
    extern float floor(float x);
    extern float trunc(float x);
    extern float round(float x);
    extern float roundEven(float x);
    extern float ceil(float x);
    extern float fract(float x);
    extern float mod(float x, float y);
    extern float clamp(float x, float min, float max);
    extern float step(float edge, float x);
    extern float smoothstep(float edge0, float edge1, float x);

    template<class T>
    inline T min(T x, T y)
    {
        return x < y ? x : y;
    }

    template<class T>
    inline T max(T x, T y)
    {
        return x > y ? x : y;
    }

    template<class T>
    inline T refract(T I, T N, float eta)
    {
        float k = 1.0f - eta*eta*(1.0f - N.Dot(I) * N.Dot(I));
        if (k < 0.0f)
            return T(0.0f);
        else
            return eta*I-(eta*N.Dot(I)+sqrt(k))*N;
    }

    template<class T>
    inline T reflect(T I, T N)
    {
        return I - N.Dot(N, I) * N;
    }

    template<class T>
    inline T faceforward(T N, T I, T Nref)
    {
        if (Nref.Dot(I) < 0)
            return N;
        return -N;
    }
    template<class T>
    inline T mix(T x, T y, float a)
    {
        return x*(1-a)+y*a;
    }
}
#endif
