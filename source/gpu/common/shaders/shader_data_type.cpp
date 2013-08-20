//#include <stdexcept>
//#include "shader_data_type.h"

//namespace Gpu
//{
//    const std::string AsString(ShaderDataType value)
//    {
//        switch(value)
//        {
//        case ShaderDataType::_void:
//            return "void";
//        case ShaderDataType::_bool:
//            return "bool";
//        case ShaderDataType::_int:
//            return "int";
//        case ShaderDataType::_uint:
//            return "uint";
//        case ShaderDataType::_float:
//            return "float";
//        case ShaderDataType::_vec2:
//            return "vec2";
//        case ShaderDataType::_vec3:
//            return "vec3";
//        case ShaderDataType::_vec4:
//            return "vec4";
//        case ShaderDataType:: _bvec2:
//            return "bvec2";
//        case ShaderDataType::_bvec3:
//            return "bvec3";
//        case ShaderDataType::_bvec4:
//            return "bvec4";
//        case ShaderDataType::_ivec2:
//            return "ivec2";
//        case ShaderDataType::_ivec3:
//            return "ivec3";
//        case ShaderDataType::_ivec4:
//            return "ivec4";
//        case ShaderDataType::_uvec2:
//            return "uvec2";
//        case ShaderDataType::_uvec3:
//            return "uvec3";
//        case ShaderDataType::_uvec4:
//            return "uvec4";
//        case ShaderDataType::_mat2:
//            return "mat2";
//        case ShaderDataType::_mat3:
//            return "mat3";
//        case ShaderDataType:: _mat4:
//            return "mat4";
//        case ShaderDataType::_mat2x2:
//            return "mat2x2";
//        case ShaderDataType::_mat2x3:
//            return "mat2x3";
//        case ShaderDataType::_mat2x4:
//            return "mat2x4";
//        case ShaderDataType::_mat3x2:
//            return "mat3x2";
//        case ShaderDataType::_mat3x3:
//            return "mat3x3";
//        case ShaderDataType::_mat3x4:
//            return "mat3x4";
//        case ShaderDataType::_mat4x2:
//            return "mat4x2";
//        case ShaderDataType::_mat4x3:
//            return "mat4x3";
//        case ShaderDataType::_mat4x4:
//            return "mat4x4";
//        case ShaderDataType::_sampler1d:
//            return "sampler1D";
//        case ShaderDataType::_sampler2d:
//            return "sampler2D";
//        case ShaderDataType::_sampler3d:
//            return "sampler3D";
//        case ShaderDataType::_samplerCube:
//            return "samplerCube";
//        case ShaderDataType::_sampler2dRect:
//            return "sampler2DRect";
//        case ShaderDataType::_sampler1dShadow:
//            return "sampler1DShadow";
//        case ShaderDataType::_sampler2dShadow:
//            return "sampler2DShadow";
//        case ShaderDataType::_sampler1dArray:
//            return "sampler1DArray";
//        case ShaderDataType::_sampler2dArray:
//            return "sampler2DArray";
//        case ShaderDataType::_sampler1dArrayShadow:
//            return "sampler1DArrayShadow";
//        case ShaderDataType::_sampler2dArrayShadow:
//            return "sampler2DArrayShadow";
//        case ShaderDataType::_samplerBuffer:
//            return "samplerBuffer";
//        case ShaderDataType::_sampler2DMS:
//            return "sampler2DMS";
//        case ShaderDataType::_sampler2DMSArray:
//            return "sampler2DMSArray";
//        case ShaderDataType::_isampler1d:
//            return "isampler1D";
//        case ShaderDataType::_isampler2d:
//            return "isampler2D";
//        case ShaderDataType::_isampler3d:
//            return "isampler3D";
//        case ShaderDataType::_isamplerCube:
//            return "isamplerCube";
//        case ShaderDataType::_isampler2dRect:
//            return "isampler2DRect";
//        case ShaderDataType::_isampler1dArray:
//            return "isampler1DArray";
//        case ShaderDataType::_isampler2dArray:
//            return "isampler2DArray";
//        case ShaderDataType::_isamplerBuffer:
//            return "isamplerBuffer";
//        case ShaderDataType::_isampler2DMS:
//            return "isampler2DMS";
//        case ShaderDataType::_isampler2DMSArray:
//            return "isampler2DMSArray";
//        case ShaderDataType::_usampler1d:
//            return "usampler1D";
//        case ShaderDataType::_usampler2d:
//            return "usampler2D";
//        case ShaderDataType::_usampler3d:
//            return "usampler3D";
//        case ShaderDataType::_usamplerCube:
//            return "usamplerCube";
//        case ShaderDataType::_usampler2dRect:
//            return "usampler2DRect";
//        case ShaderDataType::_usampler1dArray:
//            return "usampler1DArray";
//        case ShaderDataType::_usampler2dArray:
//            return "usampler2DArray";
//        case ShaderDataType::_usamplerBuffer:
//            return "usamplerBuffer";
//        case ShaderDataType::_usampler2DMS:
//            return "usampler2DMS";
//        case ShaderDataType::_usampler2DMSArray:
//            return "usampler2DMSArray";
//        }
//        throw std::runtime_error("Bad data type");
//    }
//}
