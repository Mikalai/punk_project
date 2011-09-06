#include <math.h>
#include "math.h"
#include "functions.h"

namespace Math
{
    float radians(float degrees)
    {
        return PI / 180.0f * degrees;
    }
    float degrees(float radians)
    {
        return 180.0f / PI * radians;
    }
    float sin(float angle)
    {
        return sinf(angle);
    }
    float cos(float angle)
    {
        return cosf(angle);
    }
    float tan(float angle)
    {
        return tanf(angle);
    }
    float asin(float x)
    {
        return asinf(x);
    }
    float acos(float x)
    {
        return acosf(x);
    }
    float atan(float x)
    {
        return atanf(x);
    }
    float sinh(float x)
    {
        return sinhf(x);
    }
    float cosh(float x)
    {
        return coshf(x);
    }
    float tanh(float x)
    {
        return tanhf(x);
    }
    float asinh(float x)
    {
        return 1.0f / sinhf(x);
    }
    float acosh(float x)
    {
        return 1.0f / coshf(x);
    }
    float atanh(float x)
    {
        return 1.0f / tanhf(x);
    }
    float pow(float x, float y)
    {
        return powf(x, y);
    }
    float exp(float x)
    {
        return expf(x);
    }
    float log(float x)
    {
        return logf(x);
    }
    float sqrt(float x)
    {
        return sqrtf(x);
    }
    float exp2(float x)
    {
        return expf(x*logf(2.0f));
    }
    float log2(float x)
    {
        return logf(x)/logf(2.0f);
    }
    float inversesqrt(float x)
    {
        return 1.0f/sqrtf(x);
    }
    float abs(float x)
    {
        if (x < 0)
            return -x;
        return x;
    }
    float sign(float x)
    {
        return x < 0 ? -1.0f : 1.0f;
    }
    float floor(float x)
    {
        return float(int(x-0.5f));
    }
    float trunc(float x)
    {
        return float(int(x));
    }
    float round(float x)
    {
        return float(int(x+0.5f));
    }
    float roundEven(float x)
    {
        return round(x);
    }
    float ceil(float x)
    {
        return ceilf(x);
    }
    float fract(float x)
    {
        return x - floor(x);
    }
    float mod(float x, float y)
    {
        return x - y*floor(x/y);
    }
    float clamp(float x, float minVal, float maxVal)
    {
        return min(max(x, minVal), maxVal);
    }
    float step(float edge, float x)
    {
        if (x < edge)
            return 0.0f;
        return 1.0f;
    }
    float smoothstep(float edge0, float edge1, float x)
    {
        float t = clamp((x-edge0)/(edge1-edge0), 0.0f, 1.0f);
        return t*t*(3-2*t);
    }
}
