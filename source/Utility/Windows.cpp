
#include <Utility/Windows.hpp>

namespace jej
{

    std::string getWinError()
    {
        DWORD lasError = GetLastError();
        LPSTR buffer = nullptr;

        const size_t size = FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            lasError,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&buffer,
            0,
            NULL
            );

        std::string message(buffer, size);
        LocalFree(buffer);
        SetLastError(0);

        return message;
    }

}



//If Windows build is used instead of console

#include <cstdlib>

extern int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    return main(__argc, __argv);
}
