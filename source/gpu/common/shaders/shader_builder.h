#ifndef SHADER_BUILDER_H
#define SHADER_BUILDER_H

#include <vector>
#include "shader_type.h"
#include "shader_uniform_table.h"
#include "shader_var_table.h"

namespace Gpu
{
    class ShaderBuilder
    {
    public:
        ShaderBuilder();

        void Version(int value);
        int Version() const;

        void AddUniform(ShaderUniformTable value);
        void AddInputVariable(ShaderVarTable value);
        void AddOutputVaruable(ShaderVarTable value);

        const std::string ToString();

    private:
        int m_version;
        std::vector<ShaderUniformTable> m_uniforms;
        std::vector<ShaderVarTable> m_input;
        std::vector<ShaderVarTable> m_output;
    };
}

#endif // SHADER_BUILDER_H
