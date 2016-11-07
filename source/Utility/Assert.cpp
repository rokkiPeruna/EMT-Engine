#include <Utility/Assert.hpp>

namespace jej
{
    void _assertion(const bool p_expression, const std::string& p_file, const unsigned int p_line, const std::string& p_message)
    {
        if (expression)
            return;

        auto slashPos = file.find_last_of("/\\");

        std::string error = "File: " + file.substr(slashPos == std::string::npos ? 0 : slashPos + 1u);
        error += "\nLine: " + std::to_string(line);
        error += "\n\n" + p_message;

#if defined(_WIN32)

        MessageBox(GetDesktopWindow(), /*EngineObject::GetInstance().GetWindowRef()._getHandle(),*/ error.c_str(), "Assertion failed!", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

#if defined(JEJ_DEBUG_MODE)

        DebugBreak();

#endif

#elif defined(ANDROID)

        __android_log_assert(0, "jej", error.c_str());

#endif

        std::exit(EXIT_FAILURE);

    }

}