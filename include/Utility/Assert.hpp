#ifndef JEJ_ASSERT_HPP
#define JEJ_ASSERT_HPP

#include <Core/Settings.hpp>

#include <string>

namespace jej
{

    //Macros for _assertion

#ifdef JEJ_ENABLE_ASSERTS
    //Expresson is boolean, Message is string
#define JEJ_ASSERT(expression, message) ::jej::_assertion((expression), __FILE__, __LINE__, (message))
#define JEJ_ASSERT_EVAL(expression, message) JEJ_ASSERT((expression), (message))

#else

#define JEJ_ASSERT(expression, message)
#define JEJ_ASSERT_EVAL(expression, message) (expression)

#endif

    //Actual assert function
    void _assertion(const bool p_expression, const std::string& p_file, const unsigned int p_line, const std::string& p_message);

}

#endif