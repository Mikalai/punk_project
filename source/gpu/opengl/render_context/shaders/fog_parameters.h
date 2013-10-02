#ifndef FOG_PARAMETERS_H
#define FOG_PARAMETERS_H

namespace Gpu
{
    struct FogShaderParameters
    {
        unsigned color;
        unsigned density;
        unsigned start;
        unsigned end;
        unsigned scale;
    };
}

#endif // FOG_PARAMETERS_H
