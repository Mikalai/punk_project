//#ifndef SHADER_FUNCTION_H
//#define SHADER_FUNCTION_H

//#include <string>
//#include <vector>
//#include "shader_data_type.h"
//#include "shader_uniform_table.h"
//#include "shader_var_table.h"

//namespace Gpu
//{
//    enum class ShaderFunctionParameterType { ParameterIn, ParameterOut, ParameterInOut };

//    const std::string AsString(ShaderFunctionParameterType value);

//    struct FunctionParameter
//    {
//        ShaderFunctionParameterType m_direction;
//        ShaderDataType m_type;
//        int m_dimension;
//        std::string m_name;
//        FunctionParameter(const std::string& name, ShaderDataType type, ShaderFunctionParameterType dir, int dimension);

//        const std::string ToString();
//    };

//    class ShaderFunction
//    {
//    public:
//        ShaderFunction();
//        virtual ~ShaderFunction();

//        void AddParameter(const FunctionParameter& value);
//        void SetReturnType(ShaderDataType value);
//        void SetName(const std::string& value);

//        const std::string ToString();

//        void AddBodyText(const std::string& value);

//    private:
//        std::vector<ShaderUniformTable> m_uniform_dep;
//        std::vector<ShaderVarTable> m_var_dep;
//        std::vector<FunctionParameter> m_params;
//        ShaderDataType m_return;
//        std::string m_body;
//        std::string m_name;
//    };
//}

//#endif // SHADER_FUNCTION_H
