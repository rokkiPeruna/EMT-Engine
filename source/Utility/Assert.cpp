#include <Utility/Assert.hpp>
#include <cstdlib>

namespace jej
{
    void _assertion(const bool p_expression, const std::string& p_file, const unsigned int p_line, const std::string& p_message)
    {
        //Assertion success: continue program
        if (p_expression)
            return;

        //Parse error message
        auto slashPos = p_file.find_last_of("/\\");

        //TODO: Android problems with to_string
#ifdef _WIN32
        std::string error = "File: " + p_file.substr(slashPos == std::string::npos ? 0 : slashPos + 1);
        error += "\nLine: " + std::to_string(p_line);
        error += "\n\n" + p_message;
#endif

#if defined _WIN32 //Windows log
#include <Windows.h>
        ;

        std::wstring tempMessage = std::wstring(error.begin(), error.end());
        LPCWSTR fullMessage = tempMessage.c_str();

        MessageBox(GetDesktopWindow(), /*EngineObject::GetInstance().GetWindowRef()._getHandle(),*/ fullMessage, L"Assertion failed!", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

#if defined(JEJ_DEBUG_MODE) //Breakpoint when debugging

        DebugBreak();

#endif

#elif defined __ANDROID__ //Android log
        //#include <android_native_app_glue.h>
        //       ;
        //        __android_log_assert(0, "jej", error.c_str());



        //Assertion failure: terminate program
        //        std::exit(EXIT_FAILURE);
#endif
    }

}