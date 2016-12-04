#ifndef JEJ_WINDOWS_UTILITY_HPP
#define JEJ_WINDOWS_UTILITY_HPP

#ifdef _WIN32

#include <string>
#include <Windows.h>

namespace jej
{

    //Parses windows GetLastError() to string
    std::string getWinError();

}

#endif

#endif