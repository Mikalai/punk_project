//#include <sstream>
//#include <stdexcept>
//#include "shader_function.h"

//namespace Gpu
//{
//    const std::string AsString(ShaderFunctionParameterType value)
//    {
//        switch (value)
//        {
//        case ShaderFunctionParameterType::ParameterIn:
//            return "in";
//        case ShaderFunctionParameterType::ParameterInOut:
//            return "inout";
//        case ShaderFunctionParameterType::ParameterOut:
//            return "out";
//        }
//        throw std::runtime_error("Bad parameter direction");
//    }

//    FunctionParameter::FunctionParameter(const std::string &name, ShaderDataType type, ShaderFunctionParameterType dir, int dimension)
//        : m_name(name)
//        , m_type(type)
//        , m_direction(dir)
//        , m_dimension(dimension)
//    {}

//    const std::string FunctionParameter::ToString()
//    {
//        std::stringstream stream;
//        stream << AsString(m_direction) << ' ' << AsString(m_type) << ' ' << m_name;
//        if (m_dimension > 0)
//            stream << '[' << m_dimension << ']';
//        return stream.str();
//    }

//    ShaderFunction::ShaderFunction()
//        : m_return(ShaderDataType::_void)
//    {
//    }

//    ShaderFunction::~ShaderFunction()
//    {}

//    void ShaderFunction::AddParameter(const FunctionParameter& value)
//    {
//        m_params.push_back(value);
//    }

//    void ShaderFunction::SetReturnType(ShaderDataType value)
//    {
//        m_return = value;
//    }

//    void ShaderFunction::SetName(const std::string& value)
//    {
//        m_name = value;
//    }

//    const std::string ShaderFunction::ToString()
//    {
//        std::stringstream stream;
//        stream << m_return << ' ' << m_name << '(';
//        for (size_t i = 0, max_i = m_params.size(); i != max_i; ++i)
//        {
//            stream << m_params[i].ToString();
//            if (i != max_i - 1)
//                stream << ',';
//        }
//        stream << ')' << std::endl;
//        stream << '{'
//    }

//    void AddBodyText(const std::string& value);
//}
