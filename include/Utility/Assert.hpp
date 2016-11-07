#ifndef JEJ_ASSERT_HPP
#define JEJ_ASSERT_HPP

#include <Windows.h>
#include <string>

#define ENABLE_ASSERTS

#ifdef _DEBUG
#define JEJ_DEBUG_MODE
#endif

namespace jej
{

#ifdef ENABLE_ASSERTS

#define JEJ_ASSERT(expression, message) ::jej::assertion((expression), __FILE__, __LINE__, (message))
#define JEJ_ASSERT_EVAL(expression, message) JEJ_ASSERT((expression), (message))

#else

#define JEJ_ASSERT(expression, message)
#define JEJ_ASSERT_EVAL(expression, message) (expression)

#endif

	void _assertion(const bool p_expression, const std::string& p_file, const unsigned int p_line, const std::string& p_message);

}

#endif