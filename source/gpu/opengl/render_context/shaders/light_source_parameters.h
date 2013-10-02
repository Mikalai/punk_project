#ifndef LIGHT_SOURCE_PARAMETERS_H
#define LIGHT_SOURCE_PARAMETERS_H

namespace Gpu
{
    struct LightSourceShaderParameters
    {
        unsigned enabled;
        unsigned direction;
        unsigned position;
        unsigned diffuse_color;
        unsigned specular_color;
        unsigned ambient_color;
        unsigned attenuation_constant;
        unsigned attenuation_linear;
        unsigned attenuation_quadric;
        unsigned spot;
        unsigned type;
        unsigned attenuation_model;
    };
}

#endif // LIGHT_SOURCE_PARAMETERS_H
