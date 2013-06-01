#ifndef LOCAL_ERRORS_H
#define LOCAL_ERRORS_H

#include <type_traits>
#include <stdexcept>

enum LocalErrors {
    ERROR_FRACTION_ALREADY_HAS_A_LEADER,
    ERROR_FRACTION_HAS_GOT_NO_LEADER,
    ERROR_FRACTION_ALREADY_HAS_A_UNION,
    ERROR_FRACTION_HAS_GOT_NO_UNION,
    ERROR_FRACTION_HUMAN_IS_NOT_LEADER,
    ERROR_ENTITY_ALREADY_HAS_POSITION,
    ERROR_ENTITY_HAS_GOT_NO_POSITION,
    ERROR_ENTITY_HAS_GOT_NO_OWNER
};

class LocalsException : std::exception
{
public:
    LocalsException(LocalErrors code);
    LocalErrors GetCode() const;
private:
    LocalErrors m_code;
};

inline LocalsException::LocalsException(LocalErrors code)
    : m_code(code)
{

}

inline LocalErrors LocalsException::GetCode() const
{
    return m_code;
}

typedef std::pair<LocalErrors, std::string> ErrorDesctiption;

static const ErrorDesctiption g_errors[] = {
    ErrorDesctiption(ERROR_FRACTION_ALREADY_HAS_A_LEADER, "Fraction already exists"),
    ErrorDesctiption(ERROR_FRACTION_HAS_GOT_NO_LEADER, "Fraction has got no leader"),
    ErrorDesctiption(ERROR_FRACTION_ALREADY_HAS_A_UNION, "Fraction already has an union"),
    ErrorDesctiption(ERROR_FRACTION_HAS_GOT_NO_UNION, "Fraction has got no union"),
    ErrorDesctiption(ERROR_FRACTION_HUMAN_IS_NOT_LEADER, "Human is not a leader"),
    ErrorDesctiption(ERROR_ENTITY_ALREADY_HAS_POSITION, "Entity already has position"),
    ErrorDesctiption(ERROR_ENTITY_HAS_GOT_NO_POSITION, "Entity has got no position"),
    ErrorDesctiption(ERROR_ENTITY_HAS_GOT_NO_OWNER, "Enttity has got no owner")
};

inline const std::string GetErrorDescription(LocalErrors e)
{
    int size = std::extent<decltype(g_errors), 0>::value;
    for (int i = 0; i != size; ++i)
    {
        if (g_errors[i].first == e)
            return g_errors[i].second;
    }
    return "Unknown error";
}

#endif // LOCAL_ERRORS_H
